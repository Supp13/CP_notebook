#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 2e5, mod = 1e9+7;
int m, n, a[N], val[N], cnt; ll fq[N];
ll powr(ll A, int B){
	ll res = 1;
	while(B){
		if(B&1) res *= A, res%=mod;
		A *= A; A%=mod;
		B>>=1;
	}
	return res % mod;
}
ll inv(int x){return powr(x, mod-2);}
ll RangeMul(int l, int r){
	if(!l) return fq[r];
	ll t1 = fq[r], t2 = fq[l-1];
	if(!t2) return 0;
	return t1*inv(t2);
}
void solve(){
	scanf("%d %d", &n, &m); set<int>s;
	for(int i = 0; i<n; ++i) scanf("%d", a+i), s.insert(a[i]);
	cnt = 0; map<int,int>mp;
	for(int x: s){
		auto it = mp.find(x);
		if(it == mp.end()) mp[x] = cnt++;
	}
	memset(fq, 0, sizeof(fq));
	for(int i = 0; i<n; ++i){
		int T = mp[a[i]]; val[T] = a[i]; a[i] = T; 
		fq[a[i]]++;
	}
	for(int i = 1; i<cnt; ++i) fq[i] *= fq[i-1], fq[i]%=mod;
	ll ans = 0ll;
	for(int i = 0; i<cnt; ++i){
		if(i-m+1>=0 && val[i-m+1] == val[i]-m+1) ans += RangeMul(i-m+1, i), ans%=mod;
	}
	printf("%d\n", (ans%mod+mod)%mod);
}
int main(){
	int t; scanf("%d", &t); 
	while(t--) solve();	
}