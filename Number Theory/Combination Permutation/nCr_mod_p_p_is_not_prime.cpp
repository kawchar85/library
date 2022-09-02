//https://www.hackerrank.com/challenges/ncr/problem

#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long 
#define MAX 142857
#define MOD 1000000007

const int N = 142858; //need primes <=M (nCr%M)
int spf[N];
vector<int> primes;

void sieve(){
  for(int i = 2; i < N; i++){
    if(spf[i] == 0) spf[i] = i, primes.push_back(i);
    int sz = primes.size();
    for(int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++)
      spf[i * primes[j]] = primes[j];
  }
}

int BigMod(ll n, ll k, const int mod){
  int ans = 1 % mod; n %= mod; if(n < 0) n += mod;
  while(k){
    if(k & 1) ans = (1LL * ans * n) % mod;
    n = n * n % mod;
    k >>= 1;
  }
  return ans;
}

ll e_gcd(ll a, ll b, ll &x, ll &y){
  if(b == 0){
    x = 1; y = 0;
    return a;
  }
  ll x1, y1;
  ll d = e_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

ll inverse(ll a, ll m){
  ll x, y;
  ll g = e_gcd(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}

// returns n! % mod without taking all the multiple factors of p into account that appear in the factorial
// mod = multiple of p
// O(mod * log(n))
int factmod(ll n, int p, const int mod){
  vector<int> f(mod + 1);
  f[0] = 1 % mod;
  for(int i = 1; i <= mod; i++){
    if (i % p) f[i] = 1LL * f[i - 1] * i % mod;
    else f[i] = f[i - 1];
  }
  int ans = 1 % mod;
  while (n > 1) {
    ans = 1LL * ans * f[n % mod] % mod;
    ans = 1LL * ans * BigMod(f[mod], n / mod, mod) % mod;
    n /= p;
  }
  return ans; 
}
ll multiplicity(ll n, int p){
  ll ans = 0;
  while (n) {
    n /= p;
    ans += n;
  }
  return ans;
}

// C(n, r) modulo p^k
// O(p^k log n)
int ncr(ll n, ll r, int p, int k){
  if(n < r || r < 0) return 0;
  int mod = 1;
  for (int i = 0; i < k; i++) {
    mod *= p;
  }
  ll t = multiplicity(n, p) - multiplicity(r, p) - multiplicity(n - r, p);
  if(t >= k) return 0;
  int ans = 1LL * factmod(n, p, mod) * inverse(factmod(r, p, mod), mod) % mod * inverse(factmod(n - r, p, mod), mod) % mod;
  ans = 1LL * ans * BigMod(p, t, mod) % mod;
  return ans;
}
pair<ll, ll> CRT(ll a1, ll m1, ll a2, ll m2) {
  ll p, q;
  ll g = e_gcd(m1, m2, p, q);
  if(a1 % g != a2 % g) return make_pair(0, -1);
  ll m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

// O(m log(n) log(m))
int ncr(ll n, ll r, int m) {
  if(n < r || r < 0) return 0;
  pair<ll, ll> ans({0, 1});
  while (m > 1) {
    int p = spf[m], k = 0, cur = 1;
    while (m % p == 0) {
      m /= p; cur *= p;
      ++k;
    }
    ans = CRT(ans.first, ans.second, ncr(n, r, p, k), cur);
  }
  return ans.first;
}

int32_t main() {
  FAST
  sieve();

  int t; 
  cin >> t;
  while(t--){
    ll n, r, m; 
    cin >> n >> r;
    m = 142857;
    cout << ncr(n, r, m) << endl;
  }
  return 0;
}
