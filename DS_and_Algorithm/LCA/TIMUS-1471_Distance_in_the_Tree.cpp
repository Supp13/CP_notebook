#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;
using pii = pair<int,int>;
const int N = 50000;
vector<pii> adj[N];
int dp[N];
void dfs(int u, int p = 0, int w = 0){
    if(u) dp[u] = dp[p] + w;
    for(pii x: adj[u]){
        int w = x.first, v = x.second;
        if(v^p) dfs(v, u, w);
    }
}
struct ST{
    int n, LOG; vector<vector<int>>st;
    void build(vector<int>&a){
        n = a.size(), LOG = log2(n) + 1;
        st.resize(n);
        for(int i = 0; i<n; ++i) st[i].resize(LOG), st[i][0] = a[i];
        for(int j = 1; j<LOG; ++j){
            for(int i = 0; i+(1<<j)-1<n; ++i)
                st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
        }
    }
    int query(int l, int r){
        int len = r-l+1, j = 31 - __builtin_clz(len);
        return min(st[l][j], st[r-(1<<j)+1][j]);
    }
};
vector<int>euler;
int T[N], timer = 0, re_index[N], turn_back[N], cnt = -1;
void dfs_euler(int u, int p = 0){
    euler.push_back(u); timer++;
    if(re_index[u] == -1){
        re_index[u] = ++cnt;
        T[re_index[u]] = timer-1;
        turn_back[re_index[u]] = u;
    }
    for(pii x: adj[u]){
        int w = x.first, v = x.second;
        if(v == p) continue;
        dfs_euler(v, u);
        euler.push_back(u); timer++;
    } 
}   
ST st; 
void prep(){
    memset(re_index, -1, sizeof(re_index));
    dfs_euler(0);
    for(int&x: euler) x = re_index[x];
    st.build(euler);
}
int get_lca(int u, int v){
    u = re_index[u]; v = re_index[v];
    return turn_back[st.query(min(T[u], T[v]), max(T[u], T[v]))];
}
int main(){
    int n; scanf("%d", &n);
    for(int i = 0, u, v, w; i<n-1; ++i){
        scanf("%d %d %d", &u, &v, &w); 
        adj[u].push_back({w, v}); adj[v].push_back({w, u});
    }
    dfs(0);
    prep();
    int q; scanf("%d", &q);
    for(int u, v; q--; ){
        scanf("%d %d", &u, &v);
        int lca = get_lca(u, v);
        printf("%d\n", dp[u] + dp[v] - dp[lca] - dp[lca]);
    }
}
