/*
  https://codeforces.com/gym/104400/problem/G
  How many array of length N+1 satisfying
  1. 0<= a[i] < 2^k
  2. a[0] = 0
  3. a[l-1] xor a[r] = x for given some (l,r,x)

  Find total disjoint components. We can assign
  any value to the parent of any component except
  the component containing a[0]. If we assign a
  value to parent, the value of other node is fixed.

  ans = (2^k)^(c-1)
*/
#include<bits/stdc++.h>
using namespace std;

#define MOD 998244353
#define MAX 1000002

typedef long long ll;

int par[MAX], sz[MAX], w[MAX];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
        w[i] = 0;
    }
}
pair<int, int> find_par(int v) {
    if(par[v] == v) {
        return {v, 0};
    }
    auto [who, wt] = find_par(par[v]);
    par[v] = who;
    w[v] ^= wt;
    return {who, w[v]};
}

int merge(int u, int v, int x) {
    auto p1 = find_par(u);
    auto p2 = find_par(v);
    u = p1.first; v = p2.first;

    int new_w = p1.second ^ p2.second ^ x;
    if(p1.first == p2.first) {
        if(new_w != 0) return -1; //violate
        return 0; // already connected
    } 
    if(sz[u] < sz[v]) swap(u, v);
    par[v] = u;
    w[v] = new_w;
    sz[u] += sz[v];
    return 1;
}


void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    init(n);
  
    for(int i = 0; i < m; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        if(merge(l-1, r, x) == -1) {
            cout << "0\n"; return;
        }
    }

    int component = 0;
    for(int i = 0; i <= n; i++) {
        if(find_par(i).first == i) {
            component++;
        }
    }
    component--; //0
    ll all = (1LL << k) % MOD, ans = 1;
    for(int i = 0; i < component; i++) {
        ans = (ans * all) % MOD;
    }
    cout << ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    //cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
