#include<bits/stdc++.h>
using namespace std;
int sssp(vector<int> &tax, vector<vector<int>> &adj, int source,int n){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    vector<int> dist(n+1,INT_MAX);
    dist[source] = 0;
    pq.push({0,source});
    while(!pq.empty()){
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if(d>dist[u])
            continue;
        for(auto &v:adj[u]){
            if(dist[u]+tax[v]<dist[v]){
                dist[v] = dist[u] + tax[v];
                pq.push({dist[v],v});
            }
        }
    }
    return dist[n];
}
int main(){
    int n, m;
    cin >> n >> m;
    vector<int> tax(n+1);
    for(int i=1;i<=n;i++){
        cin >> tax[i];
    }
    vector<vector<int>> adj(n+1);
    while(m--){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << endl << sssp(tax,adj,1,n) << endl;
}