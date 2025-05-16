#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

struct Edge
{
    int u, v, weight;
};

// Bellman-Ford Algorithm
bool bellmanFord(int V, int src, const vector<Edge> &edges, vector<int> &dist, vector<int> &parent)
{
    dist.assign(V, INF);
    parent.assign(V, -1);
    dist[src] = 0;

    // Relax edges V-1 times
    for (int i = 0; i < V - 1; ++i)
    {
        for (const Edge &e : edges)
        {
            if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v])
            {
                dist[e.v] = dist[e.u] + e.weight;
                parent[e.v] = e.u;
            }
        }
    }

    // Check for negative weight cycles
    for (const Edge &e : edges)
    {
        if (dist[e.u] != INF && dist[e.u] + e.weight < dist[e.v])
        {
            return false; // Negative cycle detected
        }
    }

    return true;
}

// Path Reconstruction
vector<int> getPath(int target, const vector<int> &parent)
{
    vector<int> path;
    for (int v = target; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    vector<int> dist, parent;
    if (!bellmanFord(V, source, edges, dist, parent))
    {
        cout << "Negative weight cycle detected!\n";
        return 0;
    }

    cout << "\nShortest distances from source " << source << ":\n";
    for (int i = 0; i < V; ++i)
    {
        cout << "To " << i << ": " << (dist[i] == INF ? -1 : dist[i]) << endl;
    }

    int target;
    cout << "\nEnter target vertex to get path: ";
    cin >> target;

    if (dist[target] == INF)
    {
        cout << "No path exists.\n";
    }
    else
    {
        vector<int> path = getPath(target, parent);
        cout << "Path: ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}