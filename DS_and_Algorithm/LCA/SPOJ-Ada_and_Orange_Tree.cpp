#include <cstdio>
#include <cmath>
#include <bitset>
#include <vector>
using namespace std;
const int N = 450000; 
bitset<251> S[N];
vector<int> adj[N];
int up[N][19], LOG, depth[N];
void dfs(int u, int p){
    if(u^p) depth[u] = depth[p] + 1;
    up[u][0] = p;
    for(int j = 1; j<LOG; ++j) up[u][j] = up[up[u][j-1]][j-1];
    for(int v: adj[u]) if(v^p) dfs(v, u), S[u] |= S[v];
}
int get_lca(int u, int v){
    if(u == v) return u;
    if(depth[u] < depth[v]) swap(u, v);
    int k = depth[u] - depth[v];
    for(int j = LOG-1; j>=0; --j) if((k>>j)&1) u = up[u][j];
    if(u == v) return u;
    for(int j = LOG-1; j>=0; --j){
        if(up[u][j] ^ up[v][j]) u = up[u][j], v = up[v][j];
    }
    return up[u][0];
}
void test_case(int n = 1, int q = 1, int r = 0){
    scanf("%d %d %d", &n, &q, &r); LOG = log2(n) + 1;
    for(int i = 0; i<n; ++i) S[i].reset(), adj[i].clear();
    for(int i = 0, x; i<n; ++i) scanf("%d", &x), S[i].set(x);
    for(int i = 0, u, v; i<n-1; ++i){
        scanf("%d %d", &u, &v);
        adj[u].push_back(v); adj[v].push_back(u);
    }
    depth[r] = 0; dfs(r, r);
    for(int i = 0, u, v; q--; ){
        scanf("%d %d", &u, &v);
        printf("%d\n", (int)S[get_lca(u, v)].count());
    }
}
int main(){
    int t; scanf("%d", &t);
    while(t--) test_case();
}
