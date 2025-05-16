#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int INF = INT_MAX;
struct Edge
{
    int u, v, w;
};
bool bellmanFord(int V, const vector<Edge> &edges, int src, vector<int> &dist)
{
    dist.assign(V, INF);
    dist[src] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (int j = 0; j < edges.size(); j++)
    {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            return false; // negative cycle
        }
    }
    return true;
}

void dijkstra(int V, const vector<vector<pair<int, int>>> &adj, int src,
                                    vector<int> &dist, vector<int> &parent)
{
    dist.assign(V, INF);
    parent.assign(V, -1);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u])
            continue;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

vector<int> getPath(int u, int v, const vector<vector<int>> &parentMatrix)
{
    vector<int> path;
    if (u == v)
    {
        path.push_back(u);
        return path;
    }
    if (parentMatrix[u][v] == -1)
        return path;
    while (v != -1)
    {
        path.insert(path.begin(), v);
        if (v == u)
            break;
        v = parentMatrix[u][v];
    }
    return path;
}

bool johnson(int V, const vector<vector<int>> &adjMatrix,
        vector<vector<int>> &distMatrix, vector<vector<int>> &parentMatrix)
{
    vector<Edge> edges;
    // Convert matrix to edge list
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (adjMatrix[u][v] != INF)
            {
                Edge e;
                e.u = u;
                e.v = v;
                e.w = adjMatrix[u][v];
                edges.push_back(e);
            }
        }
    }
    // Add new vertex s = V with 0-weight edges to all vertices
    for (int v = 0; v < V; v++)
    {
        Edge e;
        e.u = V;
        e.v = v;
        e.w = 0;
        edges.push_back(e);
    }
    vector<int> h;
    if (!bellmanFord(V + 1, edges, V, h))
    {
        return false;
    }
    // Reweight edges and build new adjacency list
    vector<vector<pair<int, int>>> newAdj(V);
    for (int u = 0; u < V; u++)
    {
        for (int v = 0; v < V; v++)
        {
            if (adjMatrix[u][v] != INF)
            {
                int w = adjMatrix[u][v] + h[u] - h[v];
                newAdj[u].push_back(make_pair(v, w));
            }
        }
    }
    // Run Dijkstra from each node
    distMatrix.assign(V, vector<int>(V, INF));
    parentMatrix.assign(V, vector<int>(V, -1));
    for (int u = 0; u < V; u++)
    {
        vector<int> dist, parent;
        dijkstra(V, newAdj, u, dist, parent);
        for (int v = 0; v < V; v++)
        {
            if (dist[v] != INF)
            {
                distMatrix[u][v] = dist[v] - h[u] + h[v];
            }
            parentMatrix[u][v] = parent[v];
        }
    }
    return true;
}

