/*
Grundy/Nimbers: smallest number jei state a jawa jabe nah
Problem: Divide pile in two unequal piles
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 10004

typedef long long ll;

int g[MAX];
int grundy(int n) {
    if(n < 3) return 0;
    if(~g[n]) return g[n];
    
    bool vis[n+10] = {};
    int x = 0;
    for(int i = 1; 2*i < n; i++) {
        x = grundy(i) ^ grundy(n - i);
        if(x < (n+10)) vis[x] = 1;
    }

    x = 0;
    while(vis[x]) 
        x++;
    return g[n] = x;
}
void solve() {
    int n, x, xorr = 0;

    cin >> n;
    while(n--) {
        cin >> x;
        xorr ^= grundy(x);
    }

    if(xorr) cout << "Alice\n";
    else cout << "Bob\n";

}

int32_t main() {
    FAST
    clean(g, -1);

    int TC = 1;

    cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
