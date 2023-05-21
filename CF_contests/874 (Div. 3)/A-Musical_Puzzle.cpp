#include <bits/stdc++.h>
using namespace std;
const int N = 51;
char s[N];
void solve(){
    int n; scanf("%d %s", &n, s);
    set<string> S;
    for(int i = 0; i+1<n; i++){
        string temp;
        temp += s[i]; temp += s[i+1];
        S.insert(temp);
    }
    printf("%d\n", (int)S.size());
}
int main(){
    int t; scanf("%d", &t);
    while(t--) solve();
}
