//https://cses.fi/problemset/task/2081
// N*Log^2N, will give TLE

#include<bits/stdc++.h>
using namespace std;
 
#define endl "\n"
#define MAX 200005
 
typedef long long ll;
 
vector<int> adj[MAX];
int sz[MAX];
int mn_dist[MAX];
bool is_removed[MAX];
int n, k1, k2, mx_depth;
ll ans, st[1 << 19];
 
void update(int idx, int val) {
    st[idx += n] += val;
    for (idx /= 2; idx; idx /= 2) st[idx] = st[2 * idx] + st[2 * idx + 1];
}
 
ll query(int lo, int hi) {
    ll ra = 0, rb = 0;
    for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
        if (lo & 1) ra = ra + st[lo++];
        if (hi & 1) rb = rb + st[--hi];
    }
    return ra + rb;
}
 
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
    if(depth > k2) return;
    mx_depth = max(mx_depth, depth);
    if(f) update(depth, 1);
    else {
        ans += query(max(0, k1 - depth), k2 - depth);
        // cout << depth << " " << query(max(0, k1 - depth), k2 - depth) << endl;
    }
    for(auto v : adj[u]) {
        if(v == p || is_removed[v]) continue;
        get_cnts(v, u, f, depth + 1);
    }
}
 
void build_centroid_decomposition(int u = 1) {
    int c = get_centroid(u, get_size(u));
 
    mx_depth = 0;
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        get_cnts(v, c, 0);
        get_cnts(v, c, 1);
    }
    for(int d = 1; d <= mx_depth; d++)
        update(d, -query(d, d));
 
    is_removed[c] = 1;
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        build_centroid_decomposition(v);
    }
}
 
void solve() {
    cin >> n >> k1 >> k2;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    update(0, 1);
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
