#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct EdgeInfo {
    int u, v;
    string type;
};

enum Color { WHITE, GRAY, BLACK };

struct DFSResult {
    vector<EdgeInfo> edge_types;
    vector<int> dfs_order;
    bool has_cycle;
};

void dfs_visit(int u, const vector<vector<int>>& adj, vector<Color>& color,
               vector<int>& discovery, vector<int>& finish, int& time,
               vector<EdgeInfo>& edge_types, vector<int>& dfs_order,
               bool& has_cycle) {
    color[u] = GRAY;
    discovery[u] = ++time;
    dfs_order.push_back(u);

    for (int v : adj[u]) {
        if (color[v] == WHITE) {
            edge_types.push_back({u, v, "Tree"});
            dfs_visit(v, adj, color, discovery, finish, time, edge_types, dfs_order, has_cycle);
        } else if (color[v] == GRAY) {
            edge_types.push_back({u, v, "Back"});
            has_cycle = true;
        } else if (discovery[u] < discovery[v]) {            // color[v] == BLACK
            edge_types.push_back({u, v, "Forward"});
        } else {                                            // color[v] == BLACK
            edge_types.push_back({u, v, "Cross"});
        }
    }

    color[u] = BLACK;
    finish[u] = ++time;
}

DFSResult dfs(int n, const vector<vector<int>>& adj) {
    vector<Color> color(n, WHITE);
    vector<int> discovery(n), finish(n);
    vector<int> dfs_order;
    vector<EdgeInfo> edge_types;
    int time = 0;
    bool has_cycle = false;

    for (int u = 0; u < n; ++u) {
        if (color[u] == WHITE) {
            dfs_visit(u, adj, color, discovery, finish, time, edge_types, dfs_order, has_cycle);
        }
    }

    return {edge_types, dfs_order, has_cycle};
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v) where nodes are 0-indexed:\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    DFSResult result = dfs(n, adj);

    cout << "DFS Order: ";
    for (int v : result.dfs_order) {
        cout << v << " ";
    }
    cout << "\n\nEdge Classification:\n";
    for (const auto& e : result.edge_types) {
        cout << e.u << " -> " << e.v << " : " << e.type << '\n';
    }

    cout << "\nCycle Detected: " << (result.has_cycle ? "Yes" : "No") << '\n';

    return 0;
}