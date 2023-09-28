//https://cses.fi/problemset/task/1688

#include<bits/stdc++.h>
using namespace std;
#define LOG 21
#define MAX 2000006

vector<int> adj[MAX];
int dep[MAX], LCA[MAX][LOG+1];

void DFS(int v, int p) {
    LCA[v][0] = p;
    for(auto x : adj[v]) {
        if(x == p) continue;
        dep[x] = dep[v] + 1;
        DFS(x, v);
    }
}

//0(NlogN)
void init(int N, int root = 1) {
    memset(LCA, -1, sizeof LCA);
    dep[root] = 0;
    DFS(root, -1);
    for(int j = 1; j <= LOG; j++) {
        for(int i = 1; i <= N; i++) {
            if(~LCA[i][j-1]) {
                int p = LCA[i][j-1];
                LCA[i][j] = LCA[p][j-1];
            }
        }
    }
}
int kth(int u, int k) {
    int p = u;
    for(int i = 0; i <= LOG; i++) {
        if(k & (1 << i)) {
            if(~p) p = LCA[p][i];
        }
    }
    return p;
}
//0(logN)
int find_lca(int a, int b) {
    if(dep[a] > dep[b])   swap(a,b);
    int d = dep[b] - dep[a];
    while(d > 0) {
        int j = log2(d);
        b = LCA[b][j]; 
        d -= (1 << j);
    }
    if(a == b) return a;
    for(int j = LOG; ~j; j--) {
        if(~LCA[a][j] && (LCA[a][j] != LCA[b][j])) {
            a = LCA[a][j];
            b = LCA[b][j];
        }
    }
    return LCA[a][0];
}
int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[find_lca(a, b)];
}

int RootedLCA(int r, int u, int v) {
    int ur = find_lca(u,r);
    int rv = find_lca(r,v);
    int uv = find_lca(u,v);
    if(ur == rv) return uv;
    if(rv == uv) return ur;
    if(uv == ur) return rv;
    return -1;
}
void add_edge(int u, int p) {
    LCA[u][0] = p; dep[u] = 1 + dep[p];
    for(int i = 1; i <= LOG; i++)
        LCA[u][i] = LCA[LCA[u][i - 1]][i - 1]; // check -1
}
int main() {
    int n, m;
    cin >> n >> m;
 
    for(int i = 2; i <= n; i++) {
        int p; 
        cin >> p;
        adj[p].push_back(i);
    }

    init(n);
 
    while(m--) {
        int u, v;
        cin >> u >> v;
        cout<< find_lca(u, v) <<endl;
    }

    return 0;
}
