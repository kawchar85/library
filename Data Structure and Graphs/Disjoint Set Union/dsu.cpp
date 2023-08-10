#include<bits/stdc++.h>
using namespace std;

#define MAX 200005

int par[MAX],sz[MAX];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        par[i] = i; sz[i] = 1;
    }
}
int find(int u) {
    if(par[u] == u) return u;
    return par[u] = find(par[u]);
}
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    if(sz[u] < sz[v]) swap(u,v);
    par[v] = u;
    sz[u] += sz[v];
}

int32_t main() {
    int n, m;
    cin >> n >> m;
    init(n);
    while(m--){
        int t, x, y;
        cin >> t >> x >> y;
        if(t == 1)
            merge(x, y);
        else if(find(x) == find(y)) {
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;
        }
    }
    return 0;
}
