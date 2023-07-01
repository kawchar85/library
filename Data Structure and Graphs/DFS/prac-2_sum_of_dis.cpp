/**
    https://cses.fi/problemset/task/1133/

    P: determine for each node the sum of the distances from the node to all other nodes.

    in[u]: sum of distances from u to each node in subtree rooted at u
    out[u]: sum of distances from u to each node excluding the subtree rooted at u
    
    in[u] = sum of in[child] + size[child]
    out[u] = contribution of par (out[par]) +
             contribution of edge u <--> par (n - size[par] + 1) +
             contribution of each siblings (in[sib] + 2 * size[sib] : u-->par-->sib 2 edge)

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
ll inSubTree[MAX], outSubTree[MAX], sz[MAX], N;

void dfs_in(int u = 1, int p = 0) {
    sz[u] = 1;
    inSubTree[u] = 0;
    for(int v : adj[u]) {
        if(v == p) continue;
        dfs_in(v, u);
        sz[u] += sz[v];
        inSubTree[u] += sz[v] + inSubTree[v];
    }
}
void dfs_out(int u = 1, int p = 0) {
    ll sum = 0;
    for(int v : adj[u]) {
        if(v == p) continue;
        // dfs_out(v, u);
        sum += inSubTree[v] + 2 * sz[v];
    }
    
    for(int v : adj[u]) {
        if(v == p) continue;
        outSubTree[v] = outSubTree[u] + (N - sz[u] + 1) + (sum - (inSubTree[v] + 2 * sz[v]));
        dfs_out(v, u);
    }

}

void solve() {
    int n, x, y;

    cin >> n;
    N = n;
    for(int i = 1; i < n; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs_in();
    dfs_out();

    for(int i = 1; i <= n; i++) {
        cout << inSubTree[i] + outSubTree[i] << " ";
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
