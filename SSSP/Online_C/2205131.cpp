#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
const int INF = INT_MAX;
void dijkstra(vector<vector<pair<int, int>>> &adj, vector<int> &dist, int source)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});
    dist[source] = 0;
    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto &p : adj[u])
        {
            if (dist[p.first] > dist[u] + p.second)
            {
                dist[p.first] = dist[u] + p.second;
                pq.push({dist[p.first], p.first});
            }
        }
    }
}
int main()
{
    int N, M, F;
    cin >> N >> M >> F;
    int C[N + 1];
    for (int i = 1; i <= N; i++)
    {
        cin >> C[i];
    }
    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    int K;
    cin >> K;
    vector<int> dist(N + 1, INF);
    dijkstra(adj, dist, 1);
    vector<pair<int, int>> lab;
    for (int i = 1; i <= N; i++)
    {
        lab.push_back({dist[i], C[i]});
    }
    sort(lab.begin(), lab.end());
    cout << endl;
    vector<int> stud(K, 0);
    int k = 0, j = 0;
    while (k < K)
    {
        if (j >= N && lab[j].second == 0)
        {
            stud[k] = -1;
            k++;
            continue;
        }
        if (lab[j].second == 0)
        {
            j++;
            continue;
        }
        stud[k] += (F + lab[j].first);
        lab[j].second--;
        k++;
    }
    for (int i = 0; i < K; i++)
    {
        cout << stud[i] << " ";
    }
}