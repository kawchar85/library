//https://codeforces.com/contest/342/problem/E

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 100005

typedef long long ll;

vector<int> adj[MAX];
int sz[MAX];
int mn_dist[MAX];
bool is_removed[MAX];
vector< pair<int, int> > ancestors[MAX];

int get_size(int u, int p = -1) {
    sz[u] = 1;
    for(auto v : adj[u]) {
        if(v == p || is_removed[v]) continue;
        sz[u] += get_size(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int n, int p = -1) {
    for(auto v : adj[u]) {
        if(v == p || is_removed[v]) continue;
        if(sz[v] * 2 > n) return get_centroid(v, n, u);
    }
    return u;
}

void get_dists(int u, int centroid, int p = -1, int cur_dist = 1) {
    for(auto v : adj[u]) {
        if(v == p || is_removed[v]) continue;
        get_dists(v, centroid, u, cur_dist + 1);
    }
    ancestors[u].push_back({centroid, cur_dist});
}

void build_centroid_decomposition(int u = 1) {
    int c = get_centroid(u, get_size(u));

    //For all nodes in the subtree rooted at `c`, calculate their distances to the centroid
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        get_dists(v, c, c);
    }

    is_removed[c] = 1;
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        build_centroid_decomposition(v);
    }
}

void update(int u) {
    mn_dist[u] = 0;
    for(auto [p, dist] : ancestors[u])
        mn_dist[p] = min(mn_dist[p], dist);
}

int query(int u) {
    int ans = mn_dist[u];
    for(auto [p, dist] : ancestors[u]) {
        if (!dist) { continue; }
        ans = min(ans, mn_dist[p] + dist);
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    mn_dist[n] = 1e7;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        mn_dist[i] = 1e7;
    }

    build_centroid_decomposition();
    update(1);
    while(m--) {
        int t, x; cin >> t >> x;
        if(t == 1) update(x);
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
