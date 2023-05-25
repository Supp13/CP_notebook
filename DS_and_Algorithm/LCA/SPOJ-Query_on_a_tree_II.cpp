#include <cstdio>
#include <vector>
using namespace std;
using pii = pair<int,int>;
const int N = 10000;
char oper[5]; int n, LOG, up[N][14], depth[N], d[N];
vector<vector<pii>>adj;
//***
struct ST{
    vector<vector<int>>st; int sz, LOG;
    void build(vector<int>&a){
        sz = a.size(); st.resize(sz); LOG = 31 -  __builtin_clz(sz) + 1;
        for(int i = 0; i<sz; ++i) st[i].resize(LOG), st[i][0] = a[i];
        for(int j = 1; j<LOG; ++j){
            for(int i = 0; i+(1<<j)-1<sz; ++i)
                st[i][j] = min(st[i][j-1], st[i+(1<<(j-1))][j-1]);
        }
    }
    int query(int l, int r){
        int len = r-l+1, j = 31 - __builtin_clz(len);
        return min(st[l][j], st[r-(1<<j)+1][j]);
    }
};
struct LCA{
    vector<int>euler, T, re_ind, new_to_old; int t = 0, ind = -1, n;
    ST st;
    LCA(vector<vector<pii>>&adj){
        n = adj.size();
        T.resize(n); re_ind.resize(n); new_to_old.resize(n);
        fill(re_ind.begin(), re_ind.end(), -1);
        dfs_euler(0);
        for(int&x: euler) x = re_ind[x];
        st.build(euler);
    }
    void dfs_euler(int u, int p=0){
        euler.push_back(u); t++;
        if(re_ind[u] == -1){ 
            re_ind[u] = ++ind;
            T[re_ind[u]] = t-1;
            new_to_old[ind] = u;
        }
        for(pii x: adj[u]){
            int v = x.second;
            if(v == p) continue;
            dfs_euler(v, u);
            euler.push_back(u); t++;
        }
    }
    int query(int u, int v){
        u = re_ind[u]; v = re_ind[v];
        int lca = st.query(min(T[u], T[v]), max(T[u], T[v]));
        return new_to_old[lca];
    }
};
////

void dfs(int u = 0, int p = 0){
    up[u][0] = p;
    if(u) depth[u] = depth[p] + 1;
    for(int j = 1; j<LOG; ++j) up[u][j] = up[up[u][j-1]][j-1];
    for(pii x: adj[u]){ 
        int w = x.first, v = x.second; if(v == p) continue;
        d[v] = d[u] + w; dfs(v, u); 
    }
}
int get_dist(int u, int v, LCA&L){
    int lca = L.query(u, v);
    return d[u] + d[v] - d[lca] - d[lca];
}
int kth_ancestor(int u, int k){
    for(int j = LOG-1; j>=0; --j) if(k>>j&1) u = up[u][j];
    return u;
}
int kth_node(int u, int v, int k, LCA&L){
    --k;
    int lca = L.query(u, v);
    if(depth[u] - k >= depth[lca]) return kth_ancestor(u, k);
    int first_part = depth[u] - depth[lca];
    int second_part = k - first_part;
    int jump = depth[v] - depth[lca] - second_part;
    return kth_ancestor(v, jump);
}
void test_case(){
    scanf("%d", &n); LOG = 31 - __builtin_clz(n) + 1;
    adj.clear();
    adj.resize(n);
    for(int i = 0, u, v, w; i<n-1; ++i){
        scanf("%d %d %d", &u, &v, &w); --u; --v;
        adj[u].push_back({w, v}); adj[v].push_back({w, u});
    }
    LCA L(adj);
    depth[0] = d[0] = 0; dfs();
    while(true){
        scanf("%s", oper);
        if(oper[1] == 'O') break;
        else if(oper[0] == 'D'){
            int u, v; scanf("%d %d", &u, &v); --u; --v;
            printf("%d\n", get_dist(u, v, L));
        }else if(oper[0] == 'K'){
            int u, v, k; scanf("%d %d %d", &u, &v, &k); --u; --v;
            printf("%d\n", kth_node(u, v, k, L) + 1);
        }   
    }

}
int main(){
    int tc; scanf("%d", &tc);
    while(tc--) test_case();
}
