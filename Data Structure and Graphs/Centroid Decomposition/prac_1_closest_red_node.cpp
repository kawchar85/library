//https://codeforces.com/contest/342/problem/E

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 200005
#define maxN 17

typedef long long ll;

set<int> adj[MAX];
int sz[MAX], par[MAX], ans[MAX];
int lvl[MAX], LCA[MAX][maxN+1];

void DFS(int v, int p) {
    LCA[v][0] = p;
    for(auto x : adj[v]) {
        if(x == p) continue;
        lvl[x] = lvl[v] + 1;
        DFS(x, v);
    }
}

//0(NlogN)
void init(int N) {
    memset(LCA, -1, sizeof LCA);
    lvl[1] = 0;
    DFS(1, -1);
    for(int j = 1; j <= maxN; j++) {
        for(int i = 1; i <= N; i++) {
            if(~LCA[i][j-1]) {
                int p = LCA[i][j-1];
                LCA[i][j] = LCA[p][j-1];
            }
        }
    }
}
//0(logN)
int find_lca(int a, int b) {
    if(lvl[a] > lvl[b])   swap(a,b);
    int d = lvl[b] - lvl[a];
    while(d > 0) {
        int j = log2(d);
        b = LCA[b][j]; 
        d -= (1 << j);
    }
    if(a == b) return a;
    for(int j = maxN; ~j; j--) {
        if(~LCA[a][j] && (LCA[a][j] != LCA[b][j])) {
            a = LCA[a][j];
            b = LCA[b][j];
        }
    }
    return LCA[a][0];
}
int dist(int a, int b) {
    return lvl[a] + lvl[b] - 2 * lvl[find_lca(a, b)];
}

//Centroid Decomposition
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
    par[c] = p;
    auto tmp = adj[c];
    for(auto v : tmp) {
      adj[c].erase(v);
      adj[v].erase(c);
      build(v, c);
    }
}
void modify(int u) {
    ans[u] = 0;
    for(int v = u; v != -1; v = par[v]) {
        ans[v] = min(ans[v], dist(v, u));
    }
}
int query(int u) {
    int mn = INT_MAX;
    for(int v = u; v != -1; v = par[v]) 
        mn = min(mn, ans[v] + dist(u, v));
    return mn;
}
void solve() {
    int n, m;
    cin >> n >> m;
    clear(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    init(n);
    build();
    modify(1);
    while(m--) {
        int t, x; cin >> t >> x;
        if(t == 1) modify(x);
        else cout << query(x) << endl;
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
