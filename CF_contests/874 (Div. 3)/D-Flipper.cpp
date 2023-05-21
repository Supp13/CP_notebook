#include <bits/stdc++.h>
using namespace std;
const int N = 2000;
int n, a[N];
vector<int> f(int l, int r){
    //[r+1, n-1] U [r, l] U [0, l-1]
    vector<int>ret;
    for(int i = r+1; i<n; ++i) ret.push_back(a[i]);
    for(int i = r; i>=l; --i) ret.push_back(a[i]);
    for(int i = 0; i<l; ++i) ret.push_back(a[i]);
    return ret;
}
void solve(){
    scanf("%d", &n);
    for(int i = 0; i<n; ++i) scanf("%d", a+i);
    if(n == 1){
        puts("1"); return;
    }else if(n == 2){
       swap(a[0], a[1]); printf("%d %d\n", a[0], a[1]); return;
    }
    int k; vector<int>ans(n, 0);
    if(a[0] == n) k = find(a+1, a+n, n-1) - a;
    else k = find(a, a+n, n) - a;
    for(int l = 0; l<k; ++l) ans = max(ans, f(l, k-1));
    if(k == n-1) ans = max(ans, f(k, k));
    for(int x: ans) printf("%d ", x); puts("");
}
int main(){
    int t; scanf("%d", &t);
    while(t--) solve();
}