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
    // if(p == -1) {
    //     p = c;
    // }
    par[c] = p;
    auto tmp = adj[c];
    for(auto v : tmp) {
      adj[c].erase(v);
      adj[v].erase(c);
      build(v, c);
    }
}
int cost(int u, int v) {
    return 0;
}
void modify(int u) {
    for(int v = u; v != -1; v = par[v]) {
        ans[v] = min(ans[v], cost(v, u));
    }
}
int query(int u) {
    int mn = INT_MAX;
    for(int v = u; v != -1; v = par[v]) 
        mn = min(mn, ans[v] + cost(u, v));
    return mn;
}
