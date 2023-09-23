//https://codeforces.com/contest/1387/problem/B2
// sob path centroid diye jabe, center er sub-tree er size < n/2

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 200005

typedef long long ll;

vector<int> adj[MAX];
int sz[MAX], depth[MAX];
bool is_removed[MAX];

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

vector<int> order;
void dfs(int u, int p = -1) {
    order.push_back(u);
    for(auto v : adj[u]) {
        if(v == p) continue;
        depth[v] = 1 + depth[u];
        dfs(v, u);
    }
}
int ans[MAX];
void solve() {
    int n; 
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    get_size(1);
    int c = get_centroid(1, n);
    dfs(c);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += 2 * depth[i];
    }

    for(int i = 0; i < n; i++) {
        ans[order[i]] = order[(i + n / 2) % n];
    }
    cout << sum << endl;
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " \n"[i == n];
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
