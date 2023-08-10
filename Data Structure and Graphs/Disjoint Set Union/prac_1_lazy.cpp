/**
    https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/C
    add u x: add x point to each player of set that contain u

    maintain lazy value, just add x to parent of u.
    then, current point = initial point of u p[u] + lazy[find(u)].
    to merge v to u, p[v] += lazy[find(v)], p[v] -= lazy[find(u)].
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MOD 1000000007
#define MAX 300005

typedef long long ll;

ll par[MAX], sz[MAX], p[MAX], lazyTeam[MAX];
vector<ll> player[MAX];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
        player[i].push_back(i);
        lazyTeam[i] = 0;
        p[i] = 0;
    }
}
ll find(ll u) {
    if(par[u] == u) return u;
    return par[u] = find(par[u]);
}
void merge(ll u, ll v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    if(sz[u] < sz[v]) swap(u,v);
    for(auto x : player[v]){
        player[u].push_back(x);
        p[x] += lazyTeam[v];
        p[x] -= lazyTeam[u];
    }
    par[v] = u;
    sz[u] += sz[v];
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
            x = find(x);
            lazyTeam[x] += y;
        }
        else if(s[0] == 'j'){
            cin >> y;
            merge(x,y);
        }
        else {
            cout << p[x]+lazyTeam[find(x)] << endl;
        }
    }

    return 0;
}
