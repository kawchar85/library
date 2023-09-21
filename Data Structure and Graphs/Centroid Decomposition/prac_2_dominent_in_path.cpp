//https://codeforces.com/contest/321/problem/C

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 200005

typedef long long ll;

set<int> adj[MAX];
int sz[MAX], par[MAX], ans[MAX];
void clear(int n) {
    for(int i = 1; i <= n; ++i) {
        adj[i].clear();
        ans[i] = 1e7;
    }
}
int dfs_sz(int u, int p) {
    sz[u] = 1;
    for(auto v : adj[u]) {
        if(v == p) continue;
        sz[u] += dfs_sz(v, u);
    }
    return sz[u];
}
int centroid(int u, int p, int n) {
    for(auto v : adj[u]) {
        if(v == p) continue;
        if(2 * sz[v] > n) return centroid(v, u, n);
    }
    return u;
}
void build(int u = 1, int p = -1) {
    int n = dfs_sz(u, p);
    int c = centroid(u, p, n);
    if(p == -1) {
        ans[c] = 0;
    } else {
        ans[c] = 1 + ans[p];
    }
    par[c] = p;
    auto tmp = adj[c];
    for(auto v : tmp) {
      adj[c].erase(v);
      adj[v].erase(c);
      build(v, c);
    }
}
void solve() {
    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    build();
    for(int i = 1; i <= n; i++) {
        cout << char('A' + ans[i]) << " \n"[i == n];
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    //cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
