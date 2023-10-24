//https://codeforces.com/gym/104619/problem/F

#include<bits/stdc++.h>
using namespace std;

struct OnlineBridge {
  // 1 indexed
  vector<int> par, dsu_2ecc, dsu_cc, dsu_cc_size;
  int bridges, lca_it;
  vector<int> last_visit;
  OnlineBridge() {}
  OnlineBridge(int n) {
    dsu_2ecc.resize(n + 1);
    dsu_cc.resize(n + 1); 
    par.resize(n + 1); 
    dsu_cc_size.resize(n + 1);
    lca_it = 0;
    last_visit.assign(n + 1, 0);
    for (int i=0; i<= n; ++i) {
        dsu_2ecc[i] = i;
        dsu_cc[i] = i;
        dsu_cc_size[i] = 1;
        par[i] = -1;
    }
    bridges = 0;
  }
  int find_2ecc(int u) {
    if (u == -1) return -1;
    return dsu_2ecc[u] == u ? u : dsu_2ecc[u] = find_2ecc(dsu_2ecc[u]);
  }
  int find_cc(int u) {
    u = find_2ecc(u);
    return dsu_cc[u] == u ? u : dsu_cc[u] = find_cc(dsu_cc[u]);
  }
  void make_root(int u) {
    u = find_2ecc(u);
    int root = u;
    int child = -1;
    while (u != -1) {
      int p = find_2ecc(par[u]);
      par[u] = child;
      dsu_cc[u] = root;
      child = u;
      u = p;
    }
    int previous_root = child;
    dsu_cc_size[root] = dsu_cc_size[previous_root];
  }
  void merge_path (int u, int v) {
    ++lca_it;
    vector<int> path_u, path_v;
    int lca = -1;
    while (lca == -1) {
      if (u != -1) {
        u = find_2ecc(u);
        path_u.push_back(u);
        if (last_visit[u] == lca_it){
          lca = u;
          break;
        }
        last_visit[u] = lca_it;
        u = par[u];
      }
      if (v != -1) {
        v = find_2ecc(v);
        path_v.push_back(v);
        if (last_visit[v] == lca_it){
          lca = v;
          break;
        }
        last_visit[v] = lca_it;
        v = par[v];
      }
    }
    for (int x : path_u) {
      dsu_2ecc[x] = lca;
      if (x == lca) break;
      --bridges;
    }
    for (int x : path_v) {
      dsu_2ecc[x] = lca;
      if (x == lca) break;
      --bridges;
    }
  }
  void add_edge(int u, int v) {
    int x = u, y = v;
    u = find_2ecc(u);
    v = find_2ecc(v);
    if (u == v) return;
    int comp_u = find_cc(u);
    int comp_v = find_cc(v);

    if (comp_u != comp_v) {
      ++bridges;
      if (dsu_cc_size[comp_u] > dsu_cc_size[comp_v]) {
        swap(u, v);
        swap(comp_u, comp_v);
      }
      make_root(u);
      par[u] = dsu_cc[u] = v;
      dsu_cc_size[comp_v] += dsu_cc_size[u];
    }
    else {
      merge_path(u, v);
    }
  }
}online_bridge;

int main() {
  int n, m, q; cin >> n >> m >> q;
  online_bridge = OnlineBridge(n);
  set< pair<int, int> > edge;
  vector< pair<int, int> > query;
  for(int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    if(x > y) swap(x, y);
    edge.insert({x, y});
  }
  while (q--) {
    int u, v; cin >> u >> v;
    if(u > v) swap(u, v);
    edge.erase({u, v});
    query.push_back({u, v});
  }
  for(auto [u, v] : edge) {
    online_bridge.add_edge(u, v);
  }
  vector<int> ans;
  ans.push_back(online_bridge.bridges);
  while(query.size()) {
    auto [u, v] = query.back();
    query.pop_back();
    online_bridge.add_edge(u, v);
    ans.push_back(online_bridge.bridges);
  }
  for(int i = ans.size() - 2; i >= 0; i--) {
    cout << ans[i] << "\n";
  }
  return 0;
}
