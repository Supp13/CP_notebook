#include <cstdio>
#include <cstdint>
#include <vector>
#include <queue>
#define int int32_t
using namespace std;
const int inf = 1e9;
vector<pair<int,int>> adj[1<<19];
bool vis[1<<19];
int d[1<<19];
int main(){
    int n, s; scanf("%d %d", &n, &s);
    vector<int>vec;
    for(int i = 0, w; i<n; ++i){
        scanf("%d", &w);
        int poison = 0, antidote = 0;
        for(int j = 0, p; j<s; ++j){
            scanf("%d", &p);
            if(p == -1) poison |= (1<<j);
            else if(p == 1) antidote |= (1<<j);
        }
        adj[poison].push_back({w, antidote});
        vec.push_back(poison);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
    for(int mask = 1; mask < (1<<s); ++mask) d[mask] = inf;
    pq.push({d[0] = 0, 0});
    while(!pq.empty()){
        int u = pq.top().second; pq.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(pair<int,int> x: adj[u]){
            int w = x.first, v = x.second;
            if(!vis[v] && d[u] + w < d[v]) pq.push({d[v] = d[u] + w, v});
        }
        for(int j = 0; j<s; ++j){
            if(u>>j&1){
                int v = u ^ (1<<j);
                if(!vis[v] && d[u] < d[v]) pq.push({d[v] = d[u], v});
            }
        }
    }
    int ans = 0;
    for(int poi: vec) if(d[poi] ^ inf) ans = max(ans, d[poi]);
    printf("%d", ans);
}
