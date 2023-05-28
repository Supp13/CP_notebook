#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;
const int N = 100000, x = 0, y = 1;
int pos[2][N], Y[N], X[(int)(1e6+1)];
int main(){
    int n, m, q; scanf("%d %d %d", &n, &m, &q);
    for(int i = 0; i<n; ++i) scanf("%d", pos[x]+i);
    for(int i = 0, s; i<n; ++i){
        scanf("%d", &s); X[pos[x][i]] = s;
    }
    for(int i = 0; i<m; ++i) scanf("%d", pos[y]+i);
    for(int i = 0; i<m; ++i){
        scanf("%d", Y+i); if(i) Y[i] += Y[i-1];
    }
    for(int i = 1; i<=(int)1e6; ++i) X[i] += X[i-1];
    for(int a, b, k; q--; ){
        scanf("%d %d %d", &a, &b, &k);
        int l = -1e9, h = 1e9, ans = INT_MAX;
        while(l<=h){
            int P = l + ((h-l)>>1);
            int low = 0, high = m-1, j = -1;
            while(low<=high){
                int M = low + ((high-low)>>1);
                if(pos[y][M]*a+b <= P) j = M, low = M+1;
                else high = M-1;
            }
            int yy = (j>=0 && j<m)? Y[j] : 0;
            int xx = (P>=1 && P<=(int)1e6)? X[P] : 0;
            if(P > 1e6) xx = X[(int)1e6];
            int T = xx + yy;
            if(T < k) l = P+1;
            else if(T >= k) ans = min(ans, P), h = P-1;
        }
        printf("%d\n", ans);
    }
}
