/**
 * Jan25 CSE208 
 * Practice Session on BFS/DFS
 * 
 * 
 * Complete the following code by implementing the functions. Please be mindful of the corner cases. 
 * Run the provided input file. 
 * Be ready to explain the generated output to the evaluator.
 * 
 * 
 * The usage of any online tool and/or any GenAI is absolutely forbidden in this course 
 * unless otherwise mentioned. 
 * 
 * 
 * You may consider the following:
 *  
 * BFS(Graph, start_node):
    # Create a queue to store nodes to be explored
    # Create a set to track visited nodes
    
    # Start from the initial node and enqueue it

    # While the queue is not empty
        # Dequeue a node from the queue
        # Process the current node (e.g., print it or store it)
        # For each neighbor of the current node
            # If the neighbor has not been visited
                # Mark the neighbor as visited and enqueue it
 * 
 * 
 * DFS(Graph, current_node, visited):
    # Mark the current node as visited
    # Process the current node (e.g., print it or store it)
    
    # For each neighbor of the current node
        # If the neighbor has not been visited
            # Recursively call DFS on the neighbor
            DFS(Graph, neighbor, visited)
 *
 *
 *  **-**
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {

    int V;
    vector<vector<int>> adj;
    vector<int> col;

public:
    // You can use the code from previous practice session.
    Graph(int vertices);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    void printGraph();

    // Method to check if the graph is bipartite
    void checkBipartite(){
        // Write the necessary code here
    }
    void dfsvisit( int v, vector<int> &col,  bool &p){
    
        col[v] = 1;
        for(int i=0;i<V;i++){
            if(col[i]==0 && adj[v][i]==1){
                dfsvisit(i,col,p);
            }
            else if(col[i]==1 && adj[v][i]==1)
                p = false;
            }
        col[v] = 2;
    }
    void DFS(bool &p){
        for(int i=0;i<V;i++){
            if(col[i]==0)
                dfsvisit(i,col,p);
        }
    }
};
Graph::Graph(int vertices){
    V = vertices;
    adj.resize(V,vector<int>(V,0));
    col.resize(V,0);
}
void Graph::addEdge(int u,int v){
    adj[u][v] = 1;
}
void Graph::removeEdge(int u,int v){
    adj[u][v] = 0;
}
void Graph::printGraph(){
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
     // Write the necessary code here
    int V, e;
    cin >> V >> e;
    Graph G(V);
    while(e--){
        int u, v;
        cin >> u >> v;
        G.addEdge(u,v);
    }
    bool p = true;
    G.DFS(p);
    cout << (p ? "YES" : "NO") << endl;
}