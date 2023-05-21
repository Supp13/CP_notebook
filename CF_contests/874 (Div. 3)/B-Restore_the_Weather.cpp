#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+1;
int n, k, b[N], ans[N];
pair<int,int> a[N];
void solve(){
    scanf("%d %d", &n, &k);
    for(int i = 0, x;i<n; ++i){
        scanf("%d", &x); a[i].first = x; a[i].second = i;
    }
    for(int i = 0; i<n; ++i) scanf("%d", b+i);
    sort(a, a+n); sort(b, b+n);
    for(int i = 0; i<n; ++i) ans[a[i].second] = b[i];
    for(int i = 0; i<n; ++i) printf("%d ", ans[i]); puts("");
}
int main(){
    int t; scanf("%d", &t);
    while(t--) solve();
}