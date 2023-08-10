/*
  https://codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/D
*/
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
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m, k, x, y, t;
    string s;
    vector< pair<int, int> >edge;
    vector< pair<pair<int, int>, int> > q; //x,y,t 
    map<pair<int, int>, int> bad;
    stack<string> ans;

    cin >> n >> m >> k;

    init(n);

    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        if(x > y) swap(x, y);
        edge.push_back({x, y});
    }

    for(int i = 0; i < k; i++) {
        cin >> s >> x >> y;        
        if(x > y) swap(x, y);
        if(s[0] == 'a') t = 0;
        else t = 2, bad[{x,y}] = 1;
        
        q.push_back({{x, y}, t});
    }

    for(auto p : edge) {
        if(!bad[p])
            merge(p.first, p.second);
    }

    while(q.size()) {
        auto p = q.back(); q.pop_back();
        x = p.first.first;
        y = p.first.second;
        t = p.second;

        if(t == 0) {
            if(find(x) == find(y))
                ans.push("YES");
            else
                ans.push("NO");
        } else merge(x,y);
    }

    while(ans.size()) {
        cout << ans.top() << "\n";
        ans.pop();
    }

    return 0;
}
