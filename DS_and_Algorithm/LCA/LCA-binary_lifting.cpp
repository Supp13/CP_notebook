//https://www.spoj.com/problems/LCASQ/
//LCA using binary lifting
//NlogN preprocess + logN / query
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
const int N = 10000;
vector<int> adj[N];
int n, depth[N], up[N][14], LOG;
void dfs(int u, int p=0){
    if(u) depth[u] = depth[p] + 1;
    up[u][0] = p;
    for(int j = 1; j<LOG; ++j) up[u][j] = up[up[u][j-1]][j-1];
    for(int v: adj[u]) if(v^p) dfs(v, u);
}
int get_lca(int u, int v){
    if(u == v) return u;
    if(depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for(int j = LOG-1; j>=0; --j) if((diff>>j)&1) u = up[u][j];
    if(u == v) return u;
    for(int j = LOG-1; j>=0; --j){
        if(up[u][j] ^ up[v][j]) u = up[u][j], v = up[v][j];
    }
    return up[u][0];
}
int main(){
    scanf("%d", &n); LOG = log2(n) + 1;
    for(int u = 0, m; u<n; ++u){
        scanf("%d", &m);
        for(int v; m--; ) scanf("%d", &v), adj[u].push_back(v);
    }
    dfs(0); int q; scanf("%d", &q);
    for(int u, v; q--; ){
        scanf("%d %d", &u, &v); printf("%d\n", get_lca(u, v));
    }
}
