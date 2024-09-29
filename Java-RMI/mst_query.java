import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*; 
import java.util.*; 

public class mst_query extends UnicastRemoteObject implements mst
{ 
    private Map<String, ArrayList<Integer[]>  > graphs = new HashMap<String, ArrayList<Integer[]> >();
    private Map<String, Integer> GraphName = new HashMap<>();
    private Map<String, Integer[]> pa = new HashMap<String, Integer[]>();

    mst_query() throws RemoteException { 
        super(); 
    } 


    @Override
    public void add_graph(String graph_name, Integer n) {
        GraphName.put(graph_name,n);
        ArrayList<Integer[]> edges = new ArrayList<Integer[]>();
        graphs.put(graph_name,edges);
        Integer[] par = new Integer[n+1];
        for(int i=1; i<=n; i++) {
            par[i]=i;
        }
        pa.put(graph_name,par);
    }

    @Override
    public void add_edge(String graph_name,Integer node1, Integer node2, Integer weight) throws RemoteException {
        Integer[] edge = new Integer[3];
        edge[0] = node1;
        edge[1] = node2;
        edge[2] = weight;
        graphs.get(graph_name).add(edge);
    }

    public void union(String graph_name, int u, int v) {
        int root_u = find(graph_name, u);
        int root_v = find(graph_name, v);
        if(root_u != root_v) {
            if(root_u<root_v) {
                pa.get(graph_name)[root_u]=root_v;
            }
            else {
                pa.get(graph_name)[root_v]=root_u;
            }
        }
    } 

    public int find(String graph_name, int u) {
        while(pa.get(graph_name)[u]!=u) {
            u = pa.get(graph_name)[u];
        }
        return u;
    }

    @Override
    public int get_mst(String graph_name) throws RemoteException {
        ArrayList<Integer[]> edges = graphs.get(graph_name);
        Collections.sort(edges, new Comparator<Integer[]>() {
            @Override
            public int compare(Integer[] a1, Integer[] a2){
                return  a1[2].compareTo(a2[2]);
            }
        });
        int n = edges.size();
        int nodes = GraphName.get(graph_name);
        int sum = 0;
        int edge_cnt = 0;
        for(int i=0; i<n; i++) {
            Integer[] edge = edges.get(i);
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            int root_u = find(graph_name,u);
            int root_v = find(graph_name,v);
            if(root_u != root_v) {
                union(graph_name, root_u, root_v);
                sum += w;
                edge_cnt++;
            }
        }
        for(int i=1; i<=nodes; i++) {
            pa.get(graph_name)[i]=i;
        }
        if(edge_cnt != nodes-1) {
            return -1;
        }
        else {
            return sum;
        }
    }
}
