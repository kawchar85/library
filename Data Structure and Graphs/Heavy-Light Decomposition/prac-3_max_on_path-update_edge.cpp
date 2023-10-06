//https://vjudge.net/problem/SPOJ-QTREE

#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
#define ll long long
vector<array<int, 3>> adj[MAX];
int sz[MAX], par[MAX], dep[MAX], val[MAX], id[MAX], tp[MAX], ct;
ll tree[3*MAX], N, arr[MAX];
int edgeToNode[MAX];

void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node] = max(tree[node*2], tree[2*node+1]);
}
ll query(int node, int l, int r, int i, int j) {
    if(i > r || j < l) return INT_MIN;
    if(l >= i && r <= j) return tree[node];
    int mid = (l + r) / 2;
    ll x = query(node*2, l, mid, i, j);
    ll y = query(node*2+1, mid+1, r, i, j);
    return max(x, y);
}
void update(int node, int l, int r, int pos, int val) {
    if(pos > r || pos < l) return;
    if(l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) update(node*2, l, mid, pos, val);
    else update(node*2+1, mid+1, r, pos, val);
    tree[node] = max(tree[node*2], tree[2*node+1]);
}

void build(int n) {
    N = n; 
    build(1, 0, N-1);
}
void update(int pos, ll val){ //a[pos] = val
    update(1, 0, N-1, pos, val);
}
ll query(int x, int y){
    return query(1, 0, N-1, x, y);
}

void dfs_sz(int u, int p, ll cur_w = 0) {
    sz[u] = 1;
    par[u] = p;
    val[u] = cur_w;
    for (auto [i, v, w] : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        par[v] = u;
        edgeToNode[i] = v;
        dfs_sz(v, u, w);
        sz[u] += sz[v]; 
    }
}
void dfs_hld(int u, int p, int top) {
    id[u] = ct++;
    tp[u] = top;
    arr[id[u]] = val[u];
    // update(id[u], val[u]);
    int h_chi = -1, h_sz = -1;
    for (auto [i, v, w] : adj[u]) {
        if (v == p) continue;
        if (sz[v] > h_sz) {
            h_sz = sz[v];
            h_chi = v;
        }
    }
    if (h_chi == -1) return;
    dfs_hld(h_chi, u, top);
    for (auto [i, v, w] : adj[u]) {
        if (v == p || v == h_chi) continue;
        dfs_hld(v, u, v);
    }
}
ll pathQuery(int x, int y) {
    ll ret = 0;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        ret = max(ret, query(id[tp[x]], id[x]));
        x = par[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret = max(ret, query(id[x] + 1, id[y])); // +1 for a voiding value of previous edge
    return ret;
}
void updateEdge(int u, ll val) {
    update(id[edgeToNode[u]], val);
}
void init_hld(int n) {
    ct = 0;
    N = n;
    dep[1] = 0;
    dfs_sz(1, 1);
    dfs_hld(1, 1, 1);
    build(ct);
}
void solve() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
        val[i] = 0;
        arr[i] = 0;
    }
    for (int i = 2; i <= n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({i-1, b, c});
        adj[b].push_back({i-1, a, c});
    }
    init_hld(n);

    while (true) {
        char t[10];
        scanf("%s", t);
        if (t[0] == 'C') {
            int s, x;
            scanf("%d %d", &s, &x);
            updateEdge(s, x);
        } else if (t[0] == 'Q'){
            int a, b;
            scanf("%d %d", &a, &b);
            ll res = pathQuery(a, b);
            printf("%lld\n", res);
        } else return;
    }
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        solve();
    }
}
