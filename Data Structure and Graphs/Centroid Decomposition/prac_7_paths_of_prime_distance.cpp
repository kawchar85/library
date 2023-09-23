//https://www.codechef.com/problems/PRIMEDST

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define endl "\n"
#define MOD 1000000007
#define MAX 50005
typedef long long ll;

bool siv[MAX];
vector<int> prime;

void sieve() {
    for(int i = 3; 1LL * i * i <= MAX; i += 2)
        if(!siv[i])
            for(int j = i * i; j < MAX; j += i + i)
                siv[j] = 1;
    prime.push_back(2);
    for(int i = 3; i < MAX; i += 2)
        if(!siv[i]) prime.push_back(i);
}

vector<int> adj[MAX];
int sz[MAX];
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
    if(depth >= MAX) return;
    mx_depth = max(mx_depth, depth);
    if(f) cnt[depth]++;
    else {
        for(auto p : prime) {
            if(p < depth) break;
            ans += cnt[p - depth];
        }
    }
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
    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build_centroid_decomposition();
    ll total = 1LL * n * (n - 1) / 2;
    long double p = 1.0 * ans / total;
    cout << fixed << setprecision(10) << p << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    sieve();
    reverse(ALL(prime));
    // cout << prime.size() << endl;

    int TC = 1;

    //cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
