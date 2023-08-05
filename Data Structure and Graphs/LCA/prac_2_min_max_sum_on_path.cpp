/*
  min & max sum on path
  https://codeforces.com/contest/1843/problem/F2
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MAX 200005
#define LG 20
typedef long long ll;

struct info {
    int sum, pref, suf, mx;
    info() {
        sum = pref = suf = mx = 0;
    }
    info(int x) {
        sum = x;
        pref = suf = mx = max(0, x);
    }
};
info reverse(info a) {
    swap(a.pref, a.suf);
    return a;
}
info merge(info a, info b) {
    info x;
    x.sum = a.sum + b.sum;
    x.pref = max(a.pref, a.sum + b.pref);
    x.suf = max(b.suf, b.sum + a.suf);
    x.mx = max({a.mx, b.mx, a.suf + b.pref});
    return x;
}

int par[MAX][LG], lvl[MAX];
info val[2][MAX][LG]; //0-> mx, 1-> -mn
int LCA(int x, int y) {
    if(lvl[x] > lvl[y]) swap(x, y);
    for(int j = LG - 1; j >= 0; j--) 
        if(lvl[x] + (1 << j) <= lvl[y]) y = par[y][j];
    if(x == y) return x;
    for(int j = LG - 1; j >= 0; j--) 
        if(par[x][j] != par[y][j]) x = par[x][j], y = par[y][j];
    return par[x][0];
}
info getVal(int type, int u, int d) {
    info ret(0);
    for(int j = 0; j < LG; j++) {
        if(d & (1 << j)) {
            ret = merge(ret, val[type][u][j]);
            u = par[u][j];
        }
    }
    return ret;
}

pair<int,int> get_min_max(int u, int v) {
    int lca = LCA(u, v);
    int mx = merge(getVal(0, u, lvl[u]-lvl[lca]+1), reverse(getVal(0, v, lvl[v]-lvl[lca]))).mx;
    int mn = -merge(getVal(1, u, lvl[u]-lvl[lca]+1), reverse(getVal(1, v, lvl[v]-lvl[lca]))).mx;
    return {mn, mx};
}

void solve() {
    int n = 2, m, u, v, x;
    char ch;

    for(int i = 0; i < LG; i++) {
        val[0][1][i] = info(1);
        val[1][1][i] = info(-1);
    }

    cin >> m;
    while(m--) {
        cin >> ch;
        if(ch == '+') {
            cin >> u >> x;
            lvl[n] = 1 + lvl[u];
            par[n][0] = u;
            val[0][n][0] = info(x);
            val[1][n][0] = info(-x);

            for(int j = 1; j < LG; j++) {
                par[n][j] = par[par[n][j - 1]][j - 1];
                val[0][n][j] = merge(val[0][n][j - 1], val[0][par[n][j - 1]][j - 1]);
                val[1][n][j] = merge(val[1][n][j - 1], val[1][par[n][j - 1]][j - 1]);
            } 

            n++;

        } else {
            cin >> u >> v >> x;
            auto [mn, mx] = get_min_max(u, v);
            if(mn <= x && x <= mx)
                cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
