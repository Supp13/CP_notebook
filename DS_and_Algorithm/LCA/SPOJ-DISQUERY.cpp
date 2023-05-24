#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
const int N = 100000;
using pii = pair<int,int>;
vector<pii> adj[N];
int up[N][20], mini[N][20], maxi[N][20], LOG, depth[N];
void dfs(int u, int p = 0, int w = 0){
    if(u) depth[u] = depth[p] + 1;
    mini[u][0] = maxi[u][0] = w;
    up[u][0] = p;
    for(int j = 1; j<LOG; ++j){
        up[u][j] = up[up[u][j-1]][j-1];
        maxi[u][j] = max(maxi[u][j-1], maxi[up[u][j-1]][j-1]);
        mini[u][j] = min(mini[u][j-1], mini[up[u][j-1]][j-1]);
    }
    for(pii x: adj[u]){
        if(x.second^p){
            int w = x.first, v = x.second; dfs(v, u, w);
        }
    }
}
pii b_lifting(int u, int v){
    if(u == v) return make_pair(0, 0);
    if(depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    pii M = make_pair(INT_MAX, INT_MIN);
    for(int j = LOG-1; j>=0; --j){
        if((k>>j)&1){
            M.first = min(M.first, mini[u][j]);
            M.second = max(M.second, maxi[u][j]);
            u = up[u][j];
        }
    }
    if(u == v) return M;
    for(int j = LOG-1; j>=0; --j){
        if(up[u][j] ^ up[v][j]){
            M.first = min({M.first, mini[u][j], mini[v][j]});
            M.second = max({M.second, maxi[u][j], maxi[v][j]});
            u = up[u][j]; v = up[v][j];
        }
    }
    M.first = min({M.first, mini[u][0], mini[v][0]});
    M.second = max({M.second, maxi[u][0], maxi[v][0]});
    return M;
}
int main(){
    int n; scanf("%d", &n); LOG = log2(n) + 1;
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<LOG; ++j){
            maxi[i][j] = INT_MIN; mini[i][j] = INT_MAX;
        }
    }
    for(int i = 0, u, v, w; i<n-1; ++i){
        scanf("%d %d %d", &u, &v, &w); --u; --v;
        adj[u].push_back({w, v}); adj[v].push_back({w, u});
    }
    dfs(0);
    int q; scanf("%d", &q);
    for(int u, v; q--; ){
        scanf("%d %d", &u, &v); --u; --v;
        pii ans = b_lifting(u, v);
        printf("%d %d\n", ans.first, ans.second);
    }
}
