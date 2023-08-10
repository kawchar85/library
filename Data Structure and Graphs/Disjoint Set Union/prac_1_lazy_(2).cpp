/**
    https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C
    add u x: add x point to each player of set that contain u
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MOD 1000000007
#define MAX 300005

typedef long long ll;

ll par[MAX], sz[MAX], point[MAX];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
        point[i] = 0;
    }
}
pair<ll,ll> find(ll u) { // {par, point}
    if(par[u] == u) return {u, point[u]};
    auto p = find(par[u]);
    par[u] = p.first;
    point[u] += p.second;
    p = {par[u], point[u]};
    point[u] -= point[par[u]]; //next find e auto add hobe
    return p;
}

void merge(ll u, ll v) {
    u = find(u).first;
    v = find(v).first;
    if(u == v) return;
    if(sz[u] < sz[v]) swap(u,v);
    par[v] = u;
    sz[u] += sz[v];
    point[v] -= point[par[v]]; //extra add hoye jabe
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    init(n);
    while(m--) {
        string s; int x, y;
        cin >> s >> x;
        if(s[0] == 'a') {
            cin >> y;
            x = find(x).first;
            point[x] += y;
        }
        else if(s[0] == 'j'){
            cin >> y;
            merge(x,y);
        }
        else {
            cout << find(x).second << endl;
        }
    }

    return 0;
}
