/*
  https://codeforces.com/gym/104333/problem/F
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX 100005

int par[MAX], val[MAX];
multiset<int> s[MAX];
bool bad[MAX];

void init(int n) {
    for(int i = 0; i <= n; i++) {
        par[i] = i; s[i].insert(val[i]);
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
    if(s[u].size() < s[v].size()) swap(u, v);
    par[v] = u;
    for(auto x : s[v]) {
        s[u].insert(x);
    }
}
void update(int u, int x) { //set a[u] = x;
    int p = find(u);
    auto it = s[p].find(val[u]);
    s[p].erase(it);
    val[u] = x;
    s[p].insert(val[u]);
}
int getMax(int u) {
    u = find(u);
    return *s[u].rbegin();
}
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m, q;
    vector< pair<int, int> >edge;
    vector< array<int, 3> > qry; //t, x, y
    vector<int> ans;

    cin >> n >> m;

    for(int i = 1; i <= n; i++)
        cin >> val[i];
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        edge.push_back({x, y});
    }
    cin >> q;
    for(int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x;
        if(t == 1) {
            x--; bad[x] = 1;
        } else if(t == 2) {
            cin >> y;
            //use latest value for next
            //save old to update 
            swap(val[x], y);
        }
        qry.push_back({t, x, y});
    }

    init(n);
    for(int i = 0; i < m; i++) {
        if(!bad[i])
            merge(edge[i].first, edge[i].second);
    }
    while(qry.size()) {
        auto [t, x, y] = qry.back(); qry.pop_back();
        if(t == 1) {
            merge(edge[x].first, edge[x].second);
        } else if(t == 2) {
            update(x, y);
        } else {
            ans.push_back(getMax(x));
        }
    }

    while(ans.size()) {
        cout << ans.back() << "\n";
        ans.pop_back();
    }

    return 0;
}
