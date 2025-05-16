#include<bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;
void floydwarshell(vector<vector<int>> &dist){
    int v = dist.size();
    for(int k=0;k<v;k++){
        for(int i=0;i<v;i++){
            for(int j=0;j<v;j++){
                if(dist[i][k]!=INF && dist[k][j]!=INF && dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
    }
}
int main(){
    int V, E;
    cin >> V >> E;
    vector<vector<int>> dist(V+1,vector<int>(V+1,INF));
    for(int i=0;i<V+1;i++)
        dist[i][i] = 0;
    while(E--){
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = dist[v][u] = w;
    }
    int th;
    cin >> th;
    floydwarshell(dist);
    vector<pair<int,int>> cities;
    int mincnt = V+1;
    for(int i=1;i<V+1;i++){
        int cnt = 0;
        for(int j=1;j<V+1;j++){
            if(i!=j && dist[i][j]<=th){
                cnt++;
            }
        }
        cities.push_back({i,cnt});
        mincnt = min(mincnt,cnt);
    }
    for(int i=0;i<cities.size();i++){
        if(cities[i].second==mincnt)
            cout << cities[i].first << " ";
    }
    
}