#include <cstdio>
#include <algorithm>
#define ll long long
const int mod = 1000000007, N = 300;
int qs[N], n, k, d;
ll dp[9][N][N];
ll sum(int l, int r){
    return (l)? qs[r]-qs[l-1] : qs[r];
}
int main(){
    scanf("%d %d %d", &n, &k, &d);
    for(int i = 0; i<n; ++i){
        scanf("%d", qs+i); if(i) qs[i] += qs[i-1];
    }
    for(int i = 0; i<n; ++i){
        for(int j = i; j<n; ++j) dp[k-1][i][j] = 1;
    }
    for(int lv = k-2; lv>=0; --lv){
        for(int i = n-1; i>=0; --i){
            for(int j = i+1; j<n; ++j){
                for(int k = i; k<j; ++k){
                    if(abs(sum(i, k) - sum(k+1, j)) <= d){
                        dp[lv][i][j] += (dp[lv+1][i][k]%mod * dp[lv+1][k+1][j]%mod)%mod;
                        dp[lv][i][j]%=mod;
                    }
                }
            }
        }
    }
    ll ans = dp[0][0][n-1];
    printf("%d", ans%mod);
}
