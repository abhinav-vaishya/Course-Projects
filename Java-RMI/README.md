# Distributed Systems Assignment - 2 
Abhinav Vaishya (2018121003)


## Architecture
The java application uses RMI to invoke methods on an object running in another JVM.
The whole project comprises of 4 files:-
- Server
- Client
- MST Implementation and 
- An MST interface file.

## How to run?
- On one terminal, we will have the server, and the client on another terminal.
- Enter javac *.java on the server side.
- Enter java Server 8888 on the server side.
- Enter java Client 127.0.0.1 8888 on the client side.
- Enter the commands on the client side.

## MST Algorithm
Here, we are using kruskal algorithm (using Disjoint Set Union) to find the MST of a given graph.
We calculate MST on the fly whenever a client sends a request for MST.

## Results and Observations
- The server can handle request from multiple client. 
- Any client can work with any graph.
- The server can handle large size requests from the client.
