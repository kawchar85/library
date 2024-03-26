/**
    "If you have an apple and I have an apple and
    we exchange apples then you and I will still
    each have one apple. But if you have an idea
    and I have an idea and we exchange these
    ideas, then each of us will have two ideas."
                        -George Bernard Shaw
*/

//https://codeforces.com/contest/427/problem/C

#include<bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 300005

typedef long long ll;

vector<int> adj[MAX], adjR[MAX];
int cost[MAX];
bool vis[MAX];
vector<int> cur_scc, order;

void dfs(int u) {
    vis[u] = 1;
    for(int v : adj[u]) {
        if(!vis[v]) dfs(v);
    }
    order.push_back(u);
}

void find_scc(int u) {
    cur_scc.push_back(u);
    vis[u] = 1;
    for(int v : adjR[u]) {
        if(!vis[v]) find_scc(v);
    }
}

void solve() {
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    int m; cin >> m;
    while(m--) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adjR[y].push_back(x);
    }
    memset(vis, 0, sizeof vis);
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) dfs(i);
    }
    ll total = 0, way = 1;
    memset(vis, 0, sizeof vis);
    while(order.size()) {
        int u = order.back();
        order.pop_back();
        if(vis[u]) continue;
        cur_scc.clear();
        find_scc(u);

        int mn = INT_MAX, cnt = 0;
        for(auto u : cur_scc) {
            if(cost[u] < mn) {
                cnt = 0;
                mn = cost[u];
            }
            if(cost[u] == mn)
                cnt++;
        }
        total += mn;
         way = (way * cnt) % MOD;
    }
    cout << total << " " << way << "\n";
}
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    // cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
