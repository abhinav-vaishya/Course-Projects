import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*; 

public interface mst extends Remote 
{ 
    void add_graph(String graph_name, Integer n) throws RemoteException;
    int get_mst(String graph_name) throws RemoteException;
    void add_edge(String graph_name,Integer node1, Integer node2, Integer weight) throws RemoteException;
}