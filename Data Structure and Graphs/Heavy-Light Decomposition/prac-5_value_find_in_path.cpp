//https://vjudge.net/problem/SPOJ-GOT
 
#include <bits/stdc++.h>
using namespace std;
 
#define MAX 100005
#define ll long long

vector<int> adj[MAX];
int sz[MAX], par[MAX], dep[MAX], val[MAX], id[MAX], tp[MAX], ct;
vector<int> posNum[MAX];
void update(int idx, int num) {
    posNum[num].push_back(idx);
}
int query(int l, int r, int num) {
    return upper_bound(posNum[num].begin(), posNum[num].end(), r) - lower_bound(posNum[num].begin(), posNum[num].end(), l);
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
    update(id[u], val[u]);
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
bool pathQuery(int x, int y, int c) {
    bool ret = 0;
    while (tp[x] != tp[y]) {
        if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
        ret = ret | query(id[tp[x]], id[x], c);
        x = par[tp[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ret = ret | query(id[x], id[y], c);
    return ret;
}
void init_hld(int n) {
    ct = 1;
    dep[1] = 0;
    dfs_sz(1, 1);
    dfs_hld(1, 1, 1);
    // build(ct);
}
void solve(int n) {
    int m;
    scanf("%d", &m);
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
        posNum[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    for (int i = 2; i <= n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    init_hld(n);
    while (m--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(!pathQuery(a, b, c)) printf("Not");
        printf("Find\n");
    }
    puts("");
}
int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        solve(n);
    }
}
