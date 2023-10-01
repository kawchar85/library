//https://codeforces.com/contest/609/problem/E

#include<bits/stdc++.h>
using namespace std;
#define LOG 18
#define MAX 200005
#define ll long long
#define pll pair<ll, ll>

vector<pll> adj[MAX];
int dep[MAX], LCA[MAX][LOG+1], max_w[MAX][LOG+1];
int par[MAX];
ll ans[MAX];

struct Edge {
    ll id, u, v, w;
    Edge() {}
    Edge(ll i, ll x, ll y, ll z) {
        id = i; u = x; v = y; w = z;
    }
};
vector<Edge>E, tree;

void DFS(int u, int p) {
    LCA[u][0] = p;
    for(auto [v, w] : adj[u]) {
        if(v == p) continue;
        dep[v] = dep[u] + 1;
        max_w[v][0] = w;
        DFS(v, u);
    }
}

//0(NlogN)
void lca_init(int N, int root = 1) {
    for(int j = 1; j <= LOG; j++) {
        for(int i = 1; i <= N; i++) {
            LCA[i][j] = -1;
            max_w[i][j] = INT_MIN;
        }
    }

    max_w[root][0] = 0;
    dep[root] = 0;
    DFS(root, -1);
    for(int j = 1; j <= LOG; j++) {
        for(int i = 1; i <= N; i++) {
            if(~LCA[i][j-1]) {
                int p = LCA[i][j-1];
                LCA[i][j] = LCA[p][j-1];
                max_w[i][j]=max(max_w[i][j-1], max_w[p][j-1]);
            }
        }
    }
}
//0(logN)
int get_max_on_path(int a, int b) {
    if(dep[a] > dep[b])   swap(a,b);
    int d = dep[b] - dep[a];
    int mx = INT_MIN;
    while(d > 0) {
        int j = log2(d);
        mx = max(mx, max_w[b][j]);
        b = LCA[b][j]; 
        d -= (1 << j);
    }
    if(a == b) return mx;
    for(int j = LOG; ~j; j--) {
        if(~LCA[a][j] && (LCA[a][j] != LCA[b][j])) {
            mx = max(mx, max_w[a][j]);
            mx = max(mx, max_w[b][j]);
            a = LCA[a][j];
            b = LCA[b][j];
        }
    }
    mx = max(mx, max_w[a][0]);
    mx = max(mx, max_w[b][0]);
    return mx;
}

bool operator<(Edge a, Edge b) {
    return a.w < b.w;
}
int find_par(int x) {
    return par[x] == x? x : par[x] = find_par(par[x]);
}
ll MST(int n) {
    for(int i = 1; i <= n; i++)
        par[i] = i;
    sort(E.begin(), E.end());
    ll total = 0;
    for(auto now : E) {
        ll u = find_par(now.u);
        ll v = find_par(now.v);
        if(u == v) continue;
        par[u] = v;
        total += now.w;
        tree.push_back(now);
    }
    for(auto e : tree) {
        ans[e.id] = total;
    }
    return total;
}
int main() {
    int n, m;
    cin >> n >> m;
 
    for(int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        E.push_back(Edge(i, u, v, w));
    }

    ll cost = MST(n);
    for(auto [id, u, v, w] : tree) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        // cout << id << ": " << u << " --> " << v << " = " << w << endl;
    }
    lca_init(n);
    for(auto [id, u, v, w] : E) {
        if(ans[id]) continue;
        ans[id] = cost + w - get_max_on_path(u, v);
    }
    for(int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}
