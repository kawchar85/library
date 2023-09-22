//https://codeforces.com/contest/766/problem/E

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 200005

typedef long long ll;
#define getbit(n,i) ((n>>i)&1)

vector<int> adj[MAX];
int sz[MAX];
int val[MAX];
bool is_removed[MAX];
int cnt[2][MAX];
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

void get_cnts(int u, int p, bool f, int x_or) {
    int new_xor = x_or ^ val[u];
    
    for(int i = 0; i < 21; i ++){
        if(f) cnt[getbit(new_xor, i)][i]++;
        else ans += cnt[1 - getbit(new_xor, i)][i] * (1LL << i);
    }

    for(auto v : adj[u]) {
        if(v == p || is_removed[v]) continue;
        get_cnts(v, u, f, new_xor);
    }
}

void build_centroid_decomposition(int u = 1) {
    int c = get_centroid(u, get_size(u));

    for(int i = 0 ; i < 21 ; i ++) {
        cnt[0][i] = 1; // possible val = 0(0000...000)
        cnt[1][i] = 0;
    }
    ans += val[c];
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        get_cnts(v, c, 0, val[c]);
        get_cnts(v, c, 1, 0);
    }

    is_removed[c] = 1;
    for(auto v : adj[c]) {
        if(is_removed[v]) continue;
        build_centroid_decomposition(v);
    }
}

void solve() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> val[i];
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
