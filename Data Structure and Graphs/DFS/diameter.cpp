/**
    Tested on: https://codeforces.com/contest/1805/problem/D
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX 200005


vector<int> adj[MAX], dis[MAX], ans;

int d = -1, A = -1, B = -1; //length of diameter is d (A--->B)
pair<int,int> diameter(int u = 1, int p = -1) { //dis, node
    int mx1 = 0, mx2 = 0, n1 = u, n2 = u;
    for(int v : adj[u]) {
        if(v == p) continue;
        auto now = diameter(v, u);
        int dis = 1 + now.first;
        int who = now.second;
        if(dis >= mx1) {
            mx2 = mx1; n2 = n1;
            mx1 = dis; n1 = who;
        }
        else if(dis >= mx2) {
            mx2 = dis; n2 = who;
        }
    }
    
    if(d <= (mx1 + mx2)) {
        d = mx1 + mx2;
        A = n1; B = n2;
    }
    return {mx1, n1};
}

void dfs(int u, int p, int d) {
    dis[d].push_back(u);
    for(auto v : adj[u]) {
        if(v == p) continue;
        dfs(v, u, d + 1);
    }
}

void solve() {
    int n, x, y;
    set<int> comp;

    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    diameter();
    // cout << A << " --> " << B << " : " << d << endl;
    
    dfs(A, -1, 0);
    dfs(B, -1, 0);
    for(int i = 1; i <= n; i++) comp.insert(i);
    for(int k = n, cnt = 0; k > 0; k--) {
        if(k <= d) cnt = 1;
        for(auto u : dis[k]) {
            auto it = comp.find(u);
            if(it != comp.end())
                comp.erase(it);
        }
        ans.push_back(comp.size() + cnt);
    }

    while(ans.size()) {
        cout << ans.back() << " ";
        ans.pop_back();
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    //cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
