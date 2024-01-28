//tested on : https://codeforces.com/contest/1925/problem/E

#include<bits/stdc++.h>
#define MAX 300005
#define ll long long
using namespace std;

int n;
struct info{
    ll val, a, d; // arithmetic progression a, a + d, a + 2 * d, ...
    info() {
        val = a = d = 0;
    }
}tree[4*MAX];

void propagate(int node, int l, int r) {
    if(tree[node].a == 0 && tree[node].d == 0) return;
    tree[node].val += (2 * tree[node].a + (r - l) * tree[node].d) * (r - l + 1) / 2; // (2a + (n-1)d)*n/2

    if(l != r) {
        tree[2*node].a += tree[node].a;
        tree[2*node].d += tree[node].d;

        tree[2*node+1].a += tree[node].a + (((l + r) >> 1) - l + 1) * tree[node].d; // mid+1 th term: a+(n-1)d
        tree[2*node+1].d += tree[node].d;
    }
    tree[node].a = tree[node].d = 0;
}

ll merge(ll x, ll y) {
    return x+y;
}

void build(int node = 1, int l = 1, int r = n) {
    if(l == r) {
        tree[node] = info();
        return;
    }
    int mid = (l + r) / 2;
    build(node*2, l, mid);
    build(node*2+1, mid+1, r);
    tree[node].val = merge(tree[node*2].val, tree[2*node+1].val);
} 

ll query(int i, int j, int node = 1, int l = 1, int r = n) {
    propagate(node, l, r);
    if(i>r || j<l) return 0LL;
    if(l>=i && r<=j) return tree[node].val;
    int mid = (l + r) / 2;
    auto x = query(i, j, node*2, l, mid);
    auto y = query(i, j, node*2+1, mid+1, r);
    return merge(x, y);
}

void update(int i, int j, ll a, ll d, int node = 1, int l = 1, int r = n){
    propagate(node, l, r);
    if(i>r || j<l) return;
    if(l>=i && r<=j) {
        tree[node].a += a + (l - i) * d;
        tree[node].d += d;
        propagate(node, l, r);
        return;
    } 
    int mid = (l + r) / 2;
    update(i, j, a, d, node*2, l, mid);
    update(i, j, a, d, node*2+1,mid+1,r);

    tree[node].val=merge(tree[node*2].val, tree[node*2+1].val);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  // n = 10;
  // build();
  // update(2, 7, 10, 2);
  // update(5, 9, 10, 4);
  // for(int i = 1; i <= 10; i++) {
  //     cout << query(i, i) << "\n";
  // }

  int m, q;
  cin >> n >> m >> q;
  build();
  vector<int> x(m), v(m);
  for(auto &i : x) cin >> i;
  for(auto &i : v) cin >> i;

  vector< pair<int, int > > harb;
  set< pair<int, int > > harb_s;
  for(int i = 0; i < m; i++) {
    harb.push_back({x[i], v[i]});
    harb_s.insert({x[i], v[i]});
  }
  sort(harb.begin(), harb.end());
  int last = harb[0].second;
  for(int i = 1; i< m; i++) {
    int cur_idx = harb[i].first;
    int last_idx = harb[i - 1].first;
    int l = last_idx + 1, r = cur_idx - 1;
    update(l, r, 1LL * (cur_idx - l) * last, -last);
    last = harb[i].second;
  }

  while(q--) {
    int tp, a, b; cin >> tp >> a >> b;
    if(tp == 1) {
      auto it = harb_s.lower_bound({a, b});
      auto [nxt_x, nxt_v] = *it;
      it--;
      auto [pre_x, pre_v] = *it;
      
      update(pre_x + 1, nxt_x - 1, -1LL * (nxt_x - pre_x - 1) * pre_v, pre_v);
      harb_s.insert({a, b});

      update(pre_x + 1, a - 1, 1LL * (a - pre_x - 1) * pre_v, -pre_v);
      update(a + 1, nxt_x - 1, 1LL * (nxt_x - a - 1) * b, -b);
    } else {
      cout << query(a, b) << "\n";
    }
  }
}
