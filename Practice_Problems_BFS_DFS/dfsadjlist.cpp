#include <iostream>
#include <vector>
using namespace std;

void dfsVisit(int u, const vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& ans) {
    visited[u] = true;
    ans.push_back(u);

    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfsVisit(v, adjList, visited, ans);
        }
    }
}

vector<int> dfs(const vector<vector<int>>& adjList, int start) {
    int n = adjList.size();
    vector<bool> visited(n, false);
    vector<int> ans;
    dfsVisit(start, adjList, visited, ans);
    return ans;
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> adjList(n);

    cout << "Enter " << m << " edges (from to):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        // For undirected graph, also do: adjList[v].push_back(u);
    }

    int start;
    cout << "Enter start vertex for DFS: ";
    cin >> start;

    vector<int> dfsResult = dfs(adjList, start);
    cout << "DFS traversal: ";
    for (int v : dfsResult)
        cout << v << " ";
    cout << endl;

    return 0;
}