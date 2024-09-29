import java.io.*;				
import java.util.*; 			
import java.net.*;				
import java.awt.* ;				
import java.nio.file.*; 		
import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*; 


public class Server { 
    public static void main(String args[]) { 
        try{ 
			if(args.length!=1){
                System.out.println("<Error> Use this format: java Server <port>"); 
                System.exit(0);
			}
			Integer port = Integer.parseInt(args[0]);

            mst_query obj = new mst_query(); 
  
            LocateRegistry.createRegistry(port); 

            Naming.rebind("rmi://0.0.0.0:"+ port.toString() + "/mst_finder",obj); 
        } 
        catch(Exception ae) { System.out.println(ae); } 
    } 
}