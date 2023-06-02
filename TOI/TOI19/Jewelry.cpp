//Special Thanks to Akash Singh
//orz orz orz
#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;
using pii = pair<int,int>;
const int N = 1e6+3;
char s[N];
vector<pair<int,int>>vec;
int st[N][20];
int maxi(int l, int r){
	int len = r-l+1, j = 31 - __builtin_clz(len);
	return max(st[l][j], st[r-(1<<j)+1][j]);
}
int main(){
	int n; scanf("%d %s", &n, s); s[n] = 'F'; s[n+1] = '\0';
	for(int i = 0, st = -1, cnt = 0; i<n+1; ++i){
		if(s[i] == 'T'){
			++cnt;
			if(st == -1) st = i;
		}else if(s[i] == 'F'){
			if(st ^ -1) vec.push_back({cnt, st}); 
			st = -1; cnt = 0;
		}
	}
	int m = vec.size(), LOG = 32 - __builtin_clz(m);
	for(int i = 0; i<m; ++i) st[i][0] = vec[i].first;
	for(int j = 1; j<LOG; ++j){
		for(int i = 0; i+(1<<j)-1<n; ++i)
			st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
	}
	ll ans = 0;
	for(int i = 0; i<m; ++i){
		int len = vec[i].first, starti = vec[i].second, endi = vec[i].second + len-1;
		for(int j = 1; j<=len; ++j){
			int l = 0, h = i-1, lb = -1;
			while(l<=h){
				int mid = l + ((h-l)>>1);
				int T = maxi(mid, i-1);
				if(T >= j) lb = mid, l = mid+1;
				else h = mid-1;
			}
			l = i+1; h = m-1; int rb = -1;
			while(l<=h){
				int mid = l + ((h-l)>>1);
				int T = maxi(i+1, mid);
				if(T >= j+1) rb = mid, h = mid-1;
				else l = mid+1;
			}
			ll left, right;
			if(lb ^ -1){
				int endlb = vec[lb].second + vec[lb].first - 1;
				left = (ll)abs(endlb - starti) + (ll)(j-1);
			}else{
				left = starti + 1;
			}
			if(rb ^ -1){
				int startrb = vec[rb].second;
				right = (ll)abs(endi - startrb) + (ll)j;
			}else{
				right = n - endi;
			}
			if(j < len){
				ans += left*(ll)j;
				ans += right*(ll)j;
			}else if(j == len){
				ans += left*right*(ll)j;
			}	
			if(j <= len-2){
				ans += (ll)j*(ll)(max(0, (len-2)-j+1));
			}
		}
	}
	printf("%lld", ans);
}
