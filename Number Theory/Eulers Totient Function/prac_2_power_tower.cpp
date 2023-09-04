//https://vjudge.net/problem/Kattis-exponial
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

ll spMod(ll a, ll m) {
    if(a < m) return a;
    return m + a % m;
}

ll BigMod(ll a, ll p, ll M=MOD){
    if(!p) return spMod(1, M);
    ll x = BigMod(a, p/2, M);
    x = spMod(x * x, M);
    if(p&1) x = spMod(x * a, M);
    return x;
}

ll phi(ll n) {
    ll result = n;
    for(ll i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if(n > 1) result -= result / n;
    return result;
}

ll powerTower(ll n, ll m) {
    if(m == 1) return 0;
    if(n == 1) return 1;
    return BigMod(n, powerTower(n - 1, phi(m)), m);
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n, m;

    cin >> n >> m;
    cout << powerTower(n, m) % m << endl;

    return 0;
}
