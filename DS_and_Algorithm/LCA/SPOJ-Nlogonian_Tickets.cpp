#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
using pii = pair<int,int>;
const int N = 100000;
int n, up[N][20], maxi[N][20], LOG, depth[N];
vector<pii> adj[N];
void dfs(int u, int p = 0, int w = 0){
    if(u) depth[u] = depth[p] + 1;
    up[u][0] = p;
    maxi[u][0] = w;
    for(int j = 1; j<LOG; ++j){
        up[u][j] = up[up[u][j-1]][j-1];
        maxi[u][j] = max(maxi[u][j-1], maxi[up[u][j-1]][j-1]);
    }
    for(pii x: adj[u]){
        int w = x.first, v = x.second; if(v == p) continue;
        dfs(v, u, w);
    }
}
int get_max(int u, int v){
    if(u == v) return 0;
    int M = 0;
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int j = LOG-1; j>=0; --j){
        if(diff>>j&1) M = max(M, maxi[u][j]), u = up[u][j];
    }
    if(u == v) return M;
    for(int j = LOG-1; j>=0; --j){
        if(up[u][j] ^ up[v][j]){
            M = max({M, maxi[u][j], maxi[v][j]});
            v = up[v][j]; u = up[u][j];
        }
    }
    M = max({M, maxi[u][0], maxi[v][0]});
    return M;
}
int main(){
    while(true){
        scanf("%d", &n); if(!n) break; LOG = 31 - __builtin_clz(n) + 1;
        memset(up, 0, sizeof(up)); memset(maxi, 0, sizeof(maxi)); memset(depth, 0, sizeof(depth)); 
        for(int i = 0; i<n; ++i) adj[i].clear();
        for(int i = 0, u, v, w; i<n-1; ++i){
            scanf("%d %d %d", &u, &v, &w); --u; --v;
            adj[u].push_back({w, v}); adj[v].push_back({w, u});
        }
        dfs(0);
        int q; scanf("%d", &q);
        for(int u, v; q--; ){
            scanf("%d %d", &u, &v); --u; --v;
            printf("%d\n", get_max(u, v));
        }
    }
}
