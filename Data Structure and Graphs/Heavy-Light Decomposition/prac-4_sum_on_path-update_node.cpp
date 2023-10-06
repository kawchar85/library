//https://vjudge.net/problem/LightOJ-1348
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAX 40004
#define ll long long
vector<int> adj[MAX];
int sz[MAX], par[MAX], dep[MAX], val[MAX], id[MAX], tp[MAX], ct;
ll tree[2*MAX], N;
 
ll merge(ll x, ll y) {
    return x + y;
}
void update(int idx, ll val) {
    tree[idx += N] = val;
    for (idx >>= 1; idx; idx >>= 1) tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
}
 
ll query(int lo, int hi) {
    ll ra = 0, rb = 0;
    for (lo += N, hi += N + 1; lo < hi; lo >>= 1, hi >>= 1) {
        if (lo & 1) ra = merge(ra, tree[lo++]);
        if (hi & 1) rb = merge(rb, tree[--hi]);
    }
    return merge(ra, rb);
}
void dfs_sz(int u, int p) {
    sz[u] = 1;
    par[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs_sz(v, u);
        sz[u] += sz[v]; 
    }
}
void dfs_hld(int u, int p, int top) {
    id[u] = ct++;
    tp[u] = top;
    // arr[ id[u] ] = val[u];
    update(id[u], val[u]);
    int h_chi = -1, h_sz = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (sz[v] > h_sz) {
            h_sz = sz[v];
            h_chi = v;
        }
    }
    if (h_chi == -1) return;
    dfs_hld(h_chi, u, top);
    for (int v : adj[u]) {
        if (v == p || v == h_chi) continue;
        dfs_hld(v, u, v);
    }
}
ll pathQuery(int x, int y) {
    ll ret = 0;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        ret = merge(ret, query(id[tp[x]], id[x]));
        x = par[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret = merge(ret, query(id[x], id[y]));
    return ret;
}
void updateNode(int u, ll val) {
    update(id[u], val);
}
void init_hld(int n) {
    ct = 1;
    N = n;
    dep[1] = 0;
    dfs_sz(1, 1);
    dfs_hld(1, 1, 1);
    // build(ct);
}
void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        adj[i].clear();
    }
    for (int i = 2; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a++, b++;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    init_hld(n);
    int q;
    scanf("%d", &q);
    while (q--) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            updateNode(s + 1, x);
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            a++; b++;
            ll res = pathQuery(a, b);
            printf("%lld\n", res);
        }
    }
}
int main() {
    int t, cs = 1; cin >> t;
    while(t--) {
        printf("Case %d:\n", cs++);
        solve();
    }
}
