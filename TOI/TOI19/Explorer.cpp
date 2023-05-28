#include <cstdio>
#include <vector>
#define ll long long
using namespace std;
const int N = 500000, mod = 1000000007;
vector<int> adj[N]; 
bool vis[N]; ll dp[N], fact[N];
void dfs(int u, int p = -1){
    int numChild = 0;
    for(int v: adj[u]){
        if(v == p) continue; dfs(v, u); ++numChild;
        dp[u] = (dp[u] * dp[v])%mod;
    }
    dp[u] = (dp[u] * fact[numChild])%mod;
}
int main(){
    int n; scanf("%d", &n);
    int curr, prev, r;
    for(int i = 0; i<2*n-1; ++i){
        scanf("%d", &curr); --curr;
        if(!vis[curr]){
            vis[curr] = true;
            if(i) adj[prev].push_back(curr);
            else r = curr;
        }
        prev = curr;
    }
    dp[0] = dp[1] = fact[0] = fact[1] = 1;
    for(int i = 2; i<N; ++i) dp[i] = 1, fact[i] = (fact[i-1] * i)%mod;
    dfs(r); printf("%d", dp[r]%mod);
}
