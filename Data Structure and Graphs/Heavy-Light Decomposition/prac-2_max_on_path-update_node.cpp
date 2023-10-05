//https://cses.fi/problemset/task/2134

#include <bits/stdc++.h>
using namespace std;

#define MAX 200005

vector<int> adj[MAX];
int sz[MAX], par[MAX], dep[MAX], val[MAX], id[MAX], tp[MAX], ct;
int tree[2*MAX], arr[MAX], N;

int merge(int x, int y) {
    return max(x, y);
}
void update(int idx, int val) {
    tree[idx += N] = val;
    for (idx >>= 1; idx; idx >>= 1) tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
}
 
int query(int lo, int hi) {
    int ra = 0, rb = 0;
    for (lo += N, hi += N + 1; lo < hi; lo >>= 1, hi >>= 1) {
        if (lo & 1) ra = max(ra, tree[lo++]);
        if (hi & 1) rb = max(rb, tree[--hi]);
    }
    return max(ra, rb);
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
int pathQuery(int x, int y) {
    int ret = INT_MIN;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        ret = max(ret, query(id[tp[x]], id[x]));
        x = par[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret = max(ret, query(id[x], id[y]));
    return ret;
}
void updateNode(int u, int val) {
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

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 2; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    init_hld(n);

    while (q--) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            updateNode(s, x);
        } else {
            int a, b;
            scanf("%d%d", &a, &b);
            int res = pathQuery(a, b);
            printf("%d ", res);
        }
    }
}
