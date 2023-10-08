//https://vjudge.net/problem/Gym-102040F

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define MOD 1000000007
#define MAX 20004

typedef long long ll;

vector<int> adj[MAX];
int sz[MAX], par[MAX], dep[MAX], id[MAX], tp[MAX], ct;
int arr[MAX], N, lazy[3*MAX];

struct info {
    ll lazy, mx, cnt;
    info() {
        lazy = mx = cnt = 0LL;
    }
}tree[3*MAX];

void propagate(int node, int l, int r) {
    if(!tree[node].lazy) return;
    tree[node].mx += tree[node].lazy;
    if(l != r) {
        tree[2*node].lazy += tree[node].lazy;
        tree[2*node+1].lazy += tree[node].lazy;
    }
    tree[node].lazy = 0LL;
}

info merge(info x, info y){
    info ans;
    ans.lazy = 0;
    if(x.mx == y.mx) {
        ans.mx = x.mx;
        ans.cnt = x.cnt + y.cnt;
    } else if(x.mx > y.mx) {
        ans.mx = x.mx;
        ans.cnt = x.cnt;
    } else {
        ans.mx = y.mx;
        ans.cnt = y.cnt;
    }
    return ans;
}

void build(int node, int l, int r) {
    if(l == r) {
        tree[node].lazy = 0LL;
        tree[node].mx = arr[l];
        tree[node].cnt = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid + 1, r);
    tree[node] = merge(tree[node*2], tree[2*node+1]);
}

info query(int node,int l,int r,int i, int j) {
    propagate(node,l,r);
    if(i>r || j<l)
        return info();
    if(l>=i && j>=r)
        return tree[node];
    int mid = (l + r) / 2;
    auto x = query(node*2,l,mid,i,j);
    auto y = query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

void update(int node, int l, int r, int i, int j, int val) {
    propagate(node, l, r);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j) {
        tree[node].lazy += val;
        propagate(node,l,r);
        return;
    } 
    int mid = (l+r)/2;
    update(node*2,l,mid,i,j,val);
    update(node*2+1,mid+1,r,i,j,val);

    tree[node] = merge(tree[node*2], tree[node*2+1]);
}

void build(int n){
    N = n;
    build(1,0,N-1);
}
void update(int i, int j, int val){
    update(1,0,N-1,i,j,val);
}
int query(int k){
    auto res = query(1,0,N-1,0,N-1);
    if(res.mx == k) return res.cnt;
    return 0;
}

void dfs_sz(int u, int p) {
    sz[u] = 1;
    par[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        par[v] = u;
        dfs_sz(v, u);
        sz[u] += sz[v]; 
    }
}
void dfs_hld(int u, int p, int top) {
    id[u] = ct++;
    tp[u] = top;
    // arr[ id[u] ] = val[u];
    // cout << ct - 1 << " --> " << u << endl;
    int h_chi = -1, h_sz = -1;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (sz[v] > h_sz) {
            h_sz = sz[v];
            h_chi = v;
        }
    }
    if (h_chi == -1) return;
    dfs_hld(h_chi, u, top);
    for (int v : adj[u]) {
        if (v == p || v == h_chi) continue;
        dfs_hld(v, u, v);
    }
}
void updatePath(int x, int y, int add = 1) {
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        update(id[tp[x]], id[x], add);
        x = par[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(id[x], id[y], add);
}
void init_hld(int n) {
    ct = 0;
    dep[1] = 0;
    dfs_sz(1, 1);
    dfs_hld(1, 1, 1);
    build(ct);
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) {
        adj[i].clear();
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    init_hld(n);
    int q;
    scanf("%d", &q);
    while(q--) {
        int k;
        scanf("%d", &k);
        vector< pair<int, int> > paths;
        for(int i = 0; i < k; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            paths.push_back({u, v});
        }
        for(auto [u, v] : paths) {
            updatePath(u, v, 1);
        }
        printf("%d\n", query(k));
        for(auto [u, v] : paths) {
            updatePath(u, v, -1);
        }
    }
}

int32_t main() {
    int TC = 1;
    scanf("%d", &TC);
    for(int cs = 1; cs <= TC; cs++) {
        printf("Case %d:\n", cs);
        solve();
    }

    return 0;
}
