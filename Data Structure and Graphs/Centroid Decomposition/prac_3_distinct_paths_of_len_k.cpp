//https://cses.fi/problemset/task/2080/

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 200005

typedef long long ll;

vector<int> adj[MAX];
int sz[MAX];
int mn_dist[MAX];
bool is_removed[MAX];
int cnt[MAX];
int n, k, mx_depth;
ll ans;

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

void get_cnts(int u, int p, bool f, int depth = 1) {
    if(depth > k) return;
    mx_depth = max(mx_depth, depth);
    if(f) cnt[depth]++;
    else ans += cnt[k - depth];
    for(auto v : adj[u]) {
        if(v == p || is_removed[v]) continue;
        get_cnts(v, u, f, depth + 1);
    }
}

void build_centroid_decomposition(int u = 1) {
    int c = get_centroid(u, get_size(u));

    mx_depth = 0;
    cnt[0] = 1;
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        get_cnts(v, c, 0);
        get_cnts(v, c, 1);
    }
    fill(cnt + 1, cnt + mx_depth + 1, 0);

    is_removed[c] = 1;
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        build_centroid_decomposition(v);
    }
}

void solve() {
    cin >> n >> k;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    build_centroid_decomposition();
    cout << ans << endl;
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
