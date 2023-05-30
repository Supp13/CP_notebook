#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 4e5;
struct info{int l, r, ind;}; 
int vec[N<<1], m, cnt = -1, n, ans[N], seg[N<<3];
info A[N];
int pos(int x){return upper_bound(vec, vec+m, x)-vec-1;}
int l, r, val, I;
int query(int ind, int low, int high){
    if(low>r || high<l) return 0;
    if(l<=low && high<=r) return seg[ind];
    int mid = low + ((high-low)>>1);
    return max(query(ind<<1, low, mid), query(ind<<1|1, mid+1, high));
}
void update(int ind, int low, int high){
    if(low == high){seg[ind] = max(seg[ind], val); return;}
    int mid = low + ((high-low)>>1);
    if(I<=mid) update(ind<<1, low, mid);
    else update(ind<<1|1, mid+1, high);
    seg[ind] = max(seg[ind<<1], seg[ind<<1|1]);
}
bool cmp(info&a1, info&a2){
    if(a1.r == a2.r) return a2.l < a1.l;
    return a1.r < a2.r;
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i<n; ++i){
        int l, r; scanf("%d %d", &l, &r); --l; --r;
        vec[++cnt] = l; vec[++cnt] = r;
        A[i] = info{l, r, i};
    }
    sort(vec, vec+n+n);
    m = unique(vec, vec+n+n) - vec;
    for(int i = 0; i<n; ++i) A[i].l = pos(A[i].l), A[i].r = pos(A[i].r);
    sort(A, A+n, cmp); int maxi = 0;
    for(int i = 0, j; i<n; ++i){
        j = A[i].ind; l = A[i].l; r = A[i].r; I = l;
        ans[j] = query(1, 0, m-1) + 1; maxi = max(ans[j], maxi); val = ans[j];
        update(1, 0, m-1);
    }
    printf("%d\n", maxi);
    for(int i = 0; i<n; ++i) printf("%d ", ans[i]);
}   
