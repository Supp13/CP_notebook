//https://www.spoj.com/problems/LCASQ/
//LCA using euler tour + re indexing + sparse table RMQ
//O(N)-dfs + O(NlogN) preprecess (sparse table) + O(1)/query
#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
const int N = 10000;
int n, t = -1, ind[N], turn_back[N], time = 0, T[N];
vector<int> adj[N], euler;
struct ST{
    vector<vector<int>>st; int sz, LOG;
    ST(vector<int>&a){
        sz = a.size(); st.resize(sz); LOG = log2(sz) + 1;
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
void dfs(int u, int p=0){
    euler.push_back(u); time++; 
    if(ind[u] == -1){
        ind[u] = ++t;
        turn_back[t] = u;
        T[ind[u]] = time-1;
    }
    for(int v: adj[u]){
        if(v^p){
            dfs(v, u);
            euler.push_back(u);
            time++;
        }
    }
}
int main(){ 
    scanf("%d", &n); memset(ind, -1, sizeof(ind));
    for(int u = 0, m; u<n; ++u){
        scanf("%d", &m);
        for(int v; m--; ){
            scanf("%d", &v); adj[u].push_back(v);
        }
    }
    dfs(0);
    for(int&x: euler) x = ind[x];
    ST st(euler);
    int q; scanf("%d", &q);
    for(int u, v; q--; ){
        scanf("%d %d", &u, &v);
        u = ind[u]; v = ind[v];
        int lca = st.query(min(T[u], T[v]), max(T[u], T[v]));
        lca = turn_back[lca];
        printf("%d\n", lca);
    }   
}
