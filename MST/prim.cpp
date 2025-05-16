#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

int primMST(int V, vector<vector<pii>>& adj, int src, vector<int>& parent) {
    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    priority_queue<pii, vector<pii>, greater<>> pq;

    key[src] = 0;
    parent[src] = -1;
    pq.push({0, src});

    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalWeight += key[u];

        for (auto [v, weight] : adj[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
    return totalWeight;
}

void printMST(int V, const vector<int>& parent, const vector<vector<pii>>& adj) {
    cout << "Edges in MST:\n";
    for (int v = 0; v < V; ++v) {
        if (parent[v] != -1) {
            // Find weight from parent[v] to v
            for (auto [to, w] : adj[parent[v]]) {
                if (to == v) {
                    cout << parent[v] << " - " << v << " : " << w << '\n';
                    break;
                }
            }
        }
    }
}

int main() {
    int V, E, src;
    cin >> V >> E >> src;

    vector<vector<pii>> adj(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> parent(V, -1);
    int cost = primMST(V, adj, src, parent);

    printMST(V, parent, adj);
    cout << "Total Weight of MST: " << cost << '\n';

    return 0;
}