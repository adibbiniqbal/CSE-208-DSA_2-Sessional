#include <iostream>
#include <vector>
using namespace std;

void dfsVisit(int u, const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& ans) {
    visited[u] = true;
    ans.push_back(u);

    for (int v = 0; v < adjMatrix[u].size(); ++v) {
        if (adjMatrix[u][v] && !visited[v]) {
            dfsVisit(v, adjMatrix, visited, ans);
        }
    }
}

vector<int> dfs(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> ans;
    dfsVisit(start, adjMatrix, visited, ans);
    return ans;
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> adjMatrix(n, vector<int>(n, 0));

    cout << "Enter " << m << " edges (from to):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adjMatrix[u][v] = 1;
        // For undirected graph, also do: adjMatrix[v][u] = 1;
    }

    int start;
    cout << "Enter start vertex for DFS: ";
    cin >> start;

    vector<int> dfsResult = dfs(adjMatrix, start);
    cout << "DFS traversal: ";
    for (int v : dfsResult)
        cout << v << " ";
    cout << endl;

    return 0;
}