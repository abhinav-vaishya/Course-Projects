import java.io.*;				
import java.util.*;				
import java.net.*;				
import java.awt.*;				
import java.rmi.*; 


public class Client 
{ 
	public static void main(String args[]) 
	{ 
		try{ 

			if(args.length != 2)  
			{
                System.out.println("<Error> Use this format: java Client <server-ip> <server-port>"); 
                System.exit(0);
			}

			String server_ip = args[0];            
			Integer server_port = Integer.parseInt(args[1]);

            mst connection = (mst)Naming.lookup("rmi://" + server_ip + ":" + server_port + "/mst_finder"); 
		
			BufferedReader buffer = new BufferedReader(new InputStreamReader(System.in));
			String readline = null, graph_name = null, n1 = null, n2 = null, wt = null;          
			while(true){
				try{
                    readline=buffer.readLine();
                    if(readline == null) break;
					if(readline.length() == 0)
                        continue;
                        
					StringTokenizer tokens = new StringTokenizer(readline);
                    String command = tokens.nextToken();
                    
					if(command.equals("add_edge")){ 								
						if(tokens.countTokens() != 4){
							System.out.println("Usage: add_edge graph_name node1 node2 weight");  
							continue;
						 }
						graph_name = tokens.nextToken();
						n1 = tokens.nextToken();                    
                        n2 = tokens.nextToken();
                        wt = tokens.nextToken();
                        int node1 = Integer.parseInt(n1);                    
                        int node2 = Integer.parseInt(n2);                    
                        int weight = Integer.parseInt(wt);  
						connection.add_edge(graph_name,node1,node2,weight);	
					}

					else if(command.equals("get_mst")){    					
						if(tokens.countTokens() != 1){
							System.out.println("<Error> Use this format: get_mst graph_name"); 
							continue;
						}
						graph_name = tokens.nextToken();
						System.out.print(connection.get_mst(graph_name) + "\n"); 
                    }

					else if(command.equals("add_graph")){    					
                        if(tokens.countTokens() != 2){
							System.out.println("<Error> Use this format: add_graph graph_name n"); 
							continue;
						}
                        graph_name = tokens.nextToken();
                        n1 = tokens.nextToken();
                        int n = Integer.parseInt(n1); 
                        connection.add_graph(graph_name,n); 
                    }

                    else{
                        System.out.println("No such command exists");
                        continue;
                    }

				} catch(Exception ae) { System.out.println(ae);} 
            }

		} catch(Exception ae) { System.out.println(ae);}   
	}
}