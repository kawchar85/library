//https://toph.co/p/linear-programming


#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll sumsq(ll n) {
  return n / 2 * ((n - 1) | 1);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
ll floor_sum(ll a, ll d, ll m, ll n) {
  if(d < 0) { //if d<0, reversing the series
    a = a + (n - 1) * d; d = -d;
  }
  ll res = d / m * sumsq(n) + a / m * n;
  d %= m; a %= m;
  if (!d) return res;
  ll to = (n * d + a) / m;
  return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}

// number of integer solutions to ax + by <= c s.t. x, y >= 0
// number of nonnegative integer lattice points under or on the line ax + by = c
ll lattice_cnt(ll a, ll b, ll c) { // log(a)
  if (a == 0 or b == 0) {
    // infinite solutions
    return -1;
  }
  ll terms = 1 + c / b;
  return terms + floor_sum(c, -b, a , terms);
}
int32_t main() {
  int t; cin >> t;
  while(t--) {
    ll n, a, b; cin >> n >> a >> b;
    cout << lattice_cnt(a, b, n) << endl;  
  }
  
  return 0;
}
