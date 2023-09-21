/*
https://oj.uz/problem/view/IOI11_race

You are given a weight tree with N nodes, indexed from 1 to N.
Find the minimum number of edges used in a path with length K or
print “-1” if the path doesn’t exist.

1≤N≤2×10^5,1≤wi,j∈N≤10^6,1≤K≤10^6
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
typedef long long ll;

vector<pair<int, int>> adj[MAX];
bool is_removed[MAX];
int n, k, ans, sz[MAX], cnt[1000006];

int get_size(int u, int p = -1) {
    sz[u] = 1;
    for(auto [v, w] : adj[u]) {
        if(v == p || is_removed[v]) continue;
        sz[u] += get_size(v, u);
    }
    return sz[u];
}

int get_centroid(int u, int n, int p = -1) {
    for(auto [v, w] : adj[u]) {
        if(v == p || is_removed[v]) continue;
        if(sz[v] * 2 > n) return get_centroid(v, n, u);
    }
    return u;
}

void get_cnts(int sum, int u, int p, bool f, int depth = 1) {
    if(sum > k) return;
    if(f) cnt[sum] = min(cnt[sum], depth);
    else ans = min(ans, depth + cnt[k - sum]);
    for(auto [v, w] : adj[u]) {
        if(v == p || is_removed[v]) continue;
        get_cnts(sum + w, v, u, f, depth + 1);
    }
}

void del(int sum, int u, int p = -1) {
    if(sum > k) return;
    cnt[sum] = 2e7;
    for(auto [v, w] : adj[u]) {
        if(v == p || is_removed[v]) continue;
        del(sum + w, v, u);
    }
}

void build_centroid_decomposition(int u = 0) {
    int c = get_centroid(u, get_size(u));

    cnt[0] = 0;
    for(auto [v, w] : adj[c]) {
        if(is_removed[v]) continue;
        get_cnts(w, v, c, 0);
        get_cnts(w, v, c, 1);
    }
    for(auto [v, w] : adj[c]) {
        if(is_removed[v]) continue;
        del(w, v, c);
    }

    is_removed[c] = 1;
    for(auto [v, w] : adj[c]) {
        if(is_removed[v]) continue;
        build_centroid_decomposition(v);
    }
}

int best_path(int N, int K, int h[][2], int l[]) {
    n = N;
    k = K;
    for(int i = 0; i < n; i++) {
        adj[i].clear();
        is_removed[i] = 0;
        sz[i] = 0;
    }
    for(int i = 0; i < 1000006; i++) {
        cnt[i] = 2e7;
    }
    for(int i = 0, u, v; i < n - 1; ++i) {
        u = h[i][0];
        v = h[i][1];
        adj[u].push_back(make_pair(v, l[i]));
        adj[v].push_back(make_pair(u, l[i]));
    }
    ans = 2e7;
    build_centroid_decomposition();
    if(ans > 1e7) ans = -1;
    return ans;
}
int main() {

}
