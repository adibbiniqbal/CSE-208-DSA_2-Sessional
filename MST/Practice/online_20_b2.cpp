#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

int primMST(int V, vector<vector<pii>> &adj, int src)
{
    vector<int> key(V, 0);
    vector<bool> inMST(V, false);
    priority_queue<pii> pq;

    key[src] = 1;
    pq.push({1, src});

    int totalWeight = 1;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;
        inMST[u] = true;
        totalWeight *= key[u];

        for (auto [v, weight] : adj[u])
        {
            if (!inMST[v] && weight > key[v])
            {
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }
    return totalWeight;
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<pii>> adj(V);
    for (int i = 0; i < E; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> parent(V, -1);
    int cost = primMST(V, adj, 0);
    cout << cost << '\n';

    return 0;
}
