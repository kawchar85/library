//https://vjudge.net/problem/HackerRank-subtrees-and-paths

#include <bits/stdc++.h>
using namespace std;

#define MAX 200005
#define ll int

vector<int> adj[MAX];
int sz[MAX], par[MAX], dep[MAX], val[MAX], id[MAX], tp[MAX], ct;
int tree[3*MAX], arr[MAX], N, lazy[3*MAX];


void propagate(int node, int l, int r)
{
    tree[node] += lazy[node];
    if(l!=r)
    {
        lazy[2*node]+=lazy[node];
        lazy[2*node+1]+=lazy[node];
    }
    lazy[node]=0;
}

int merge(int x, int y) {
    return max(x, y);
}
void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node] = merge(tree[node*2], tree[2*node+1]);
}
int query(int node, int l, int r, int i, int j) {
    propagate(node,l,r);
    if(i > r || j < l) return INT_MIN/10;
    if(l >= i && r <= j) return tree[node];
    int mid = (l + r) / 2;
    int x = query(node*2, l, mid, i, j);
    int y = query(node*2+1, mid+1, r, i, j);
    return merge(x, y);
}
void update(int node, int l, int r, int pos, int val) {
    propagate(node,l,r);
    if(pos > r || pos < l) return;
    if(l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid) update(node*2, l, mid, pos, val);
    else update(node*2+1, mid+1, r, pos, val);
    tree[node] = merge(tree[node*2], tree[2*node+1]);
}
void update(int node,int l,int r,int i,int j,ll val) {
    propagate(node,l,r);
    if(i>r || j<l) return;
    if(l>=i && r<=j)
    {
        lazy[node]+=val;
        propagate(node,l,r);
        return;
    } 
    int mid=(l+r)/2;
    update(node*2,l,mid,i,j,val);
    update(node*2+1,mid+1,r,i,j,val);

    tree[node]=merge(tree[node*2],tree[node*2+1]);
}
void build(int n) {
    N = n; //build(1, 0, N-1);
}
void update(int pos, int val){ //a[pos] = val
    update(1, 0, N-1, pos, val);
}
void update(int i, int j, ll val){ //add val to arr[i...j]
     update(1,0,N-1,i,j,val);
}
int query(int x, int y){
    return query(1, 0, N-1, x, y);
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
    arr[ id[u] ] = val[u];
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
int pathQuery(int x, int y) {
    int ret = INT_MIN;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        ret = merge(ret, query(id[tp[x]], id[x]));
        x = par[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret = merge(ret, query(id[x], id[y]));
    return ret;
}
void updateNode(int u, int val) {
    update(id[u], val);
}
void updateSubTree(int u, int val) {
    update(id[u], id[u]+sz[u]-1, val);
}
void init_hld(int n) {
    ct = 0;
    dep[1] = 0;
    dfs_sz(1, 1);
    dfs_hld(1, 1, 1);
    build(ct);
}

int main() {
    int n, q;
    scanf("%d", &n);
    //for (int i = 1; i <= n; i++) scanf("%d", &val[i]);
    for (int i = 2; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    init_hld(n);

    scanf("%d", &q);
    while (q--) {
        char t[5];
        scanf("%s", t);
        if (t[0] == 'a') {
            int s, x;
            scanf("%d%d", &s, &x);
            updateSubTree(s, x);
        } else {
            int a, b;
            scanf("%d%d", &a, &b);
            int res = pathQuery(a, b);
            printf("%d\n", res);
        }
    }
}
