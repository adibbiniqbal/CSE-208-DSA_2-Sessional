#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = INT_MAX;

void floydWarshall(int V, vector<vector<int>> &dist, vector<vector<int>> &parent, vector<int> &cap)
{
    // Floyd-Warshall main loop
    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j] &&
                    cap[k] != -1 ) 
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

int main(){
    int N, M, K;
    cin >> N >> M >> K;
    vector<int> cap(N+1);
    for(int i=1;i<=N;i++)
        cin >> cap[i];
    vector<vector<int>> adj(N+1,vector<int>(N+1,INF));
    vector<vector<int>> parent(N+1,vector<int>(N+1,-1));
    for(int i=0;i<=N;i++)
        adj[i][i] = 0;
    for(int i=0;i<M;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = w;
        parent[u][v] = u;
        parent[v][u] = v;
    }
    int Q;
    cin >> Q;
    floydWarshall(N+1,adj,parent,cap);
    while(Q--){
        int u;
        cin >> u;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
        for(int i=1;i<=N;i++){
            if(cap[i]>0){
                pq.push({adj[u][i],cap[i]});
            }
        }
        int k = 0;
        while(!pq.empty() && k<K){
            auto [cost,capacity] = pq.top();
            pq.pop();
            while(capacity-- && k<K){
                cout << cost << ' ';
                k++;
            }
        }
        while(k<K){
            cout << -1 << ' ';
            k++;
        }
        cout << endl;
    }
}