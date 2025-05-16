#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int INF = INT_MAX;

void floydWarshallWithParent(int V, const vector<vector<int>> &adjMatrix,
                                            vector<vector<int>> &dist, vector<vector<int>> &parent)
{
    dist.assign(V, vector<int>(V, INF));
    parent.assign(V, vector<int>(V, -1));

    // Initialization
    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            if (i == j)
            {
                dist[i][j] = 0;
                parent[i][j] = i;
            }
            else if (adjMatrix[i][j] != INF)
            {
                dist[i][j] = adjMatrix[i][j];
                parent[i][j] = i;
            }
        }
    }

    // Floyd-Warshall main loop
    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }

    // Negative cycle detection
    for (int i = 0; i < V; ++i)
    {
        if (dist[i][i] < 0)
        {
            cout << "\nNegative weight cycle detected involving vertex " << i << ".\n";
            return;
        }
    }
}

vector<int> getPathFromParent(int u, int v, const vector<vector<int>> &parent)
{
    if (parent[u][v] == -1)
        return {};
    vector<int> path;
    while (v != u)
    {
        path.push_back(v);
        v = parent[u][v];
        if (v == -1)
            return {};
    }
    path.push_back(u);
    reverse(path.begin(), path.end());
    return path;
}

void printMatrix(const vector<vector<int>> &mat)
{
    for (const auto &row : mat)
    {
        for (int val : row)
            cout << (val == INF ? "INF" : to_string(val)) << "\t";
        cout << "\n";
    }
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adjMatrix(V, vector<int>(V, INF));
    for (int i = 0; i < V; ++i)
        adjMatrix[i][i] = 0;

    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjMatrix[u][v] = w;
    }

    vector<vector<int>> dist, parent;
    floydWarshallWithParent(V, adjMatrix, dist, parent);

    cout << "\nShortest Distance Matrix:\n";
    printMatrix(dist);

    int u, v;
    cout << "\nEnter source and destination to get shortest path (0-indexed): ";
    cin >> u >> v;

    vector<int> path = getPathFromParent(u, v, parent);
    if (path.empty())
    {
        cout << "No path exists from " << u << " to " << v << ".\n";
    }
    else
    {
        cout << "Shortest path from " << u << " to " << v << ": ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}