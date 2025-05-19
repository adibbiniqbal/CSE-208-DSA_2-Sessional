#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> dfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    vector<int> ans;
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            ans.push_back(node);

            // Push neighbors in reverse order to mimic recursive DFS order
            for (int i = adj[node].size() - 1; i >= 0; --i) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
    
    return ans;
}

int main() {
    int n = 6; // Number of vertices
    vector<vector<int>> adj(n);

    // Sample undirected graph
    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0};
    adj[3] = {1};
    adj[4] = {1, 5};
    adj[5] = {4};

    vector<bool> visited(n, false);
    vector<int> ans = dfs(0, adj, visited);

    // Output result
    cout << "DFS traversal: ";
    for (int node : ans) {
        cout << node << " ";
    }

    return 0;
}