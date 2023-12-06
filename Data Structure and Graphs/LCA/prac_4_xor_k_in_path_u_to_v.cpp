//https://codeforces.com/contest/1902/problem/F

#include<bits/stdc++.h>
using namespace std;

#define MAX 200005
#define mx_lvl 21

typedef int ll;

struct XorBasis{
    vector<ll> basis;
    void add(ll x){
        for(auto &i : basis) x=min(x,x^i);
        if(!x) return;
        for(auto &i : basis) if((i^x)<i) i^=x;
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }
    int size() {
        return basis.size();
    }
    bool possible(ll x){
        for(auto &i: basis) x=min(x, x^i);
        return !x;
    }
};
vector<int> adj[MAX];
int lvl[MAX], val[MAX];
int LCA[MAX][mx_lvl+1];
XorBasis table[MAX][mx_lvl+1];

XorBasis merge(XorBasis x, XorBasis y){
    if(x.size() < y.size())
        swap(x.basis, y.basis);
    for(auto cur : y.basis)
        x.add(cur);
    return x;
}

void DFS(int u, int p) {
    LCA[u][0] = p;
    for(auto v : adj[u]) {
        if(v == p) continue;
        lvl[v] = 1 + lvl[u];
        table[v][0].add(val[u]);
        DFS(v, u);
    }
}

void init(int N) {
    for(int j = 1; j <= mx_lvl; j++) {
        for(int i = 1; i <= N; i++) {
            LCA[i][j] = -1;
        }
    }
    DFS(1, -1);
    for(int j = 1; j <= mx_lvl; j++) {
        for(int i = 1; i <= N; i++) {
            if(~LCA[i][j-1]) {
                int p = LCA[i][j-1];
                LCA[i][j] = LCA[p][j-1];
                table[i][j] = merge(table[i][j-1], table[p][j-1]);
            }
        }
    }

}

bool check(int a, int b, int k) {
    if(lvl[a] > lvl[b])   swap(a,b);
    int d = lvl[b]-lvl[a];
    XorBasis ret;
    ret.add(val[a]);
    ret.add(val[b]);
    while(d > 0) {
        int j = log2(d);
        ret = merge(ret, table[b][j]);
        b = LCA[b][j];
        d -= (1<<j);
    }
    if(a==b) return ret.possible(k);

    for(int j = mx_lvl; ~j; j--) {
        if(~LCA[a][j] && (LCA[a][j]!=LCA[b][j])) {
            ret = merge(ret, table[a][j]);
            ret = merge(ret, table[b][j]);
            a = LCA[a][j];
            b = LCA[b][j];
        }
    }
    ret = merge(ret, table[a][0]);
    ret = merge(ret, table[b][0]);

    return ret.possible(k);
}
void solve() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    init(n);
    int q; cin >> q;
    while(q--) {
        int x, y, k;
        cin >> x >> y >> k;
        if(check(x, y, k)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
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
