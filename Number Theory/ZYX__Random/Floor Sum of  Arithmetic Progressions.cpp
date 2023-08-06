/*
  https://atcoder.jp/contests/practice2/tasks/practice2_c
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"

typedef long long ll;

ll sumsq(ll n) {
  return n / 2 * ((n - 1) | 1);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
ll floor_sum(ll a, ll d, ll m, ll n) {
  ll res = d / m * sumsq(n) + a / m * n;
  d %= m; a %= m;
  if (!d) return res;
  ll to = (n * d + a) / m;
  return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) % m}
ll mod_sum(ll a, ll d, ll m, ll n) {
  a = ((a % m) + m) % m;
  d = ((d % m) + m) % m;
  return n * a + d * sumsq(n) - m * floor_sum(a, d, m, n);
}

void solve() {
    ll n, m, a, d;
    cin >> n >> m >> d >> a;
    cout << floor_sum(a, d, m , n) << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
