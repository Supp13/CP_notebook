#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, mini, a[N]; vector<int> vec[2];
int main(){
    int t; scanf("%d", &t);
    while(t--){
        vec[0].clear(); vec[1].clear();
        scanf("%d", &n); mini = INT_MAX;
        for(int i = 0, x; i<n; ++i){
            scanf("%d", &x);
            vec[x&1].push_back(x);
            if(x&1) mini = min(mini, x);
        }
        if((int)vec[0].size() == n || (int)vec[1].size() == n){puts("YES"); continue;}
        bool check1 = true, check2 = true;
        for(int x: vec[0]) if(x <= mini){check1 = false; break;}
        for(int x: vec[1]) if(x <= mini){check2 = false; break;}
        (check1 || check1)? puts("YES") : puts("NO");
    }
}   