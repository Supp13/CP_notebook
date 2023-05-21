#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
vector<int> adj[N]; bitset<N>vis;
bool check;
void dfs(int u, int p=-1){
	vis[u] = true;
	for(int v: adj[u]){
		if(!vis[v]) dfs(v, u);
		else if(v ^ p) check = true;
	}
}
void solve(){
	int n, open = 0, close = 0; scanf("%d", &n);
	for(int i = 0; i<n; ++i) adj[i].clear(); vis.reset();
	for(int u = 0, v; u<n; ++u){
		scanf("%d", &v); --v;
		adj[u].push_back(v); adj[v].push_back(u);
	}
	for(int i = 0; i<n; ++i){
		sort(adj[i].begin(), adj[i].end());
		adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());
	}
	for(int i = 0; i<n; ++i){
		if(!vis[i]){
			check = false; dfs(i); open += !check; close += check;
		}
	}
	printf("%d %d\n", close + (open>=1), close + open);
}
int main(){
	int t; scanf("%d", &t);
	while(t--) solve();
}