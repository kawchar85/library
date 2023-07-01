/**
    https://cses.fi/problemset/task/1132/

    P: determine for each node the maximum distance to another node
*/

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

vector<int> adj[MAX];
int dis[2][MAX];
bool vis[MAX];

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

void bfs(int t, int s) {
    dis[t][s] = 0;
    vis[s] = 1;
    queue< int> q;
    q.push(s);

    while(q.size()) {
        s = q.front();
        q.pop();

        for(auto u : adj[s]) {
            if(!vis[u]) {
                vis[u] = 1;
                dis[t][u] = 1 + dis[t][s];
                q.push(u);
            }
        }
    }
}

void solve() {
    int n, x, y;

    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    diameter();
    //max dis node will be one of diameter_end
    bfs(0, A);
    clean(vis, 0);
    bfs(1, B);

    for(int i = 1; i <= n; i++) {
        cout << max(dis[0][i], dis[1][i]) << " ";
    }
}

int32_t main() {
    FAST

    // int TC = 1;

    //cin>>TC;

    // for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    // }

    return 0;
}
