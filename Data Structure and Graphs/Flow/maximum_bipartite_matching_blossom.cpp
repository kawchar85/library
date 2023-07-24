/*
    https://vjudge.net/problem/Gym-100341H

*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define MOD 1000000007
#define MAX 202

typedef long long ll;

//O(N^3)
const int N = 2e3 + 9;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct Blossom {
  int vis[N], par[N], orig[N], match[N], aux[N], t;
  int n;
  bool ad[N];
  vector<int> g[N];
  queue<int> Q;
  Blossom() {}
  Blossom(int _n) {
    n = _n;
    t = 0;
    for (int i = 0; i <= _n; ++i) {
      g[i].clear();
      match[i] = aux[i] = par[i] = vis[i] = aux[i] = ad[i] = orig[i] = 0;
    }
  }
  void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }
  void augment(int u, int v) {
    int pv = v, nv;
    do {
      pv = par[v];
      nv = match[pv];
      match[v] = pv;
      match[pv] = v;
      v = nv;
    } while (u != pv);
  }
  int lca(int v, int w) {
    ++t;
    while (true) {
      if (v) {
        if (aux[v] == t) return v;
        aux[v] = t;
        v = orig[par[match[v]]];
      }
      swap(v, w);
    }
  }
  void blossom(int v, int w, int a) {
    while (orig[v] != a) {
      par[v] = w;
      w = match[v];
      ad[v] = true;
      if (vis[w] == 1) Q.push(w), vis[w] = 0;
      orig[v] = orig[w] = a;
      v = par[w];
    }
  }
  //it finds an augmented path starting from u
  bool bfs(int u) {
    fill(vis + 1, vis + n + 1, -1);
    iota(orig + 1, orig + n + 1, 1);
    Q = queue<int> ();
    Q.push(u);
    vis[u] = 0;
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      ad[v] = true;
      for (int x : g[v]) {
        if (vis[x] == -1) {
          par[x] = v;
          vis[x] = 1;
          if (!match[x]) return augment(u, x), true;
          Q.push(match[x]);
          vis[match[x]] = 0;
        } else if (vis[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return false;
  }
  int maximum_matching() {
    int ans = 0;
    vector<int> p(n - 1);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rnd);
    for (int i = 1; i <= n; i++) shuffle(g[i].begin(), g[i].end(), rnd);
    for (auto u : p) {
      if (!match[u]) {
        for(auto v : g[u]) {
          if (!match[v]) {
            match[u] = v, match[v] = u;
            ++ans;
            break;
          }
        }
      }
    }
    for(int i = 1; i <= n; ++i) if (!match[i] && bfs(i)) ++ans;
    return ans;
  }
} M;

bool like[MAX][MAX];
void solve() {
    int n, k, x, ans;
    cin >> n;
    M = Blossom (n);
    for(int i = 1; i <= n; i++) {
        cin >> k;
        for(int j = 0; j < k; j++) {
            cin >> x;
            like[i][x] = 1;
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(like[i][j] && like[j][i]) {
                M.add_edge(i, j);
            }
        }
    }

    ans = M.maximum_matching();
    // for(int i = 1; i <= n; i++)
    //     cout << i << " " << M.match[i] << endl;

    if(2 * ans == n) cout << "YES\n";
    else cout << "NO\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;
    freopen("perfect.in","r",stdin);
    freopen("perfect.out","w",stdout);

    //cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
