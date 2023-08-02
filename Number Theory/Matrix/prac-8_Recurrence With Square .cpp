/**
 https://vjudge.net/contest/572359#problem/G

for i >= n
a(i) = c1*a(i-1) + ... + cn*a(i-n) + F(i-1) + G(i-1) + K(i-1) + p + q + r
F(i) = F(i-1) + q
G(i) = G(i-1) + K(i-1) + r
K(i) = K(i-1) + 2r

*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

struct matrix {
    int n, m;
    vector<vector<ll>> v;
    matrix() {}
    matrix(int _n, int _m) {
        n = _n; m = _m;
        v.assign(n, vector<ll>(m, 0));
    }
    matrix(vector<vector<ll>> _v) {
        n = _v.size(); 
        m = n ? _v[0].size() : 0;
        v = _v;
    }
    void make_unit() {
        assert(n == m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                v[i][j] = (i==j);
    }
    matrix operator + (const matrix &a) {
        assert(n == a.n && m == a.m);
        matrix ans = matrix(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
            ans.v[i][j] = (v[i][j] + a.v[i][j]) % MOD;
          }
        }
        return ans;
    }
    matrix operator - (const matrix &a) {
        assert(n == a.n && m == a.m);
        matrix ans = matrix(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans.v[i][j] = (v[i][j] - a.v[i][j] + MOD) % MOD;
            }
        }
        return ans;
    }
    matrix operator * (const matrix &a) {
        assert(m == a.n);
        matrix ans = matrix(n, a.m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < a.m; j++) {
                for(int k = 0; k < m; k++) {
                    ans.v[i][j] = (ans.v[i][j] + 1LL * v[i][k] * a.v[k][j] % MOD) % MOD;
                }
            }
        }
        return ans;
    }

    matrix pow(long long k) {
        assert(n == m);
        matrix ans(n, n), t = v;
        ans.make_unit();
        while(k) {
            if(k&1) ans = ans * t;
            t = t * t;
            k >>= 1;
        }
        return ans;
    }

    void print() {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                cout << v[i][j] << " \n"[j+1 == m];
    }

    matrix& operator += (const matrix& b) { return *this = (*this) + b; }
    matrix& operator -= (const matrix& b) { return *this = (*this) - b; }
    matrix& operator *= (const matrix& b) { return *this = (*this) * b; }
    bool operator == (const matrix& b) { return v == b.v; }
    bool operator != (const matrix& b) { return v != b.v; }
};

ll p, q, r;
ll F(ll n) {
    return (n * q) % MOD;
}
ll G(ll n) {
    return (r * n * n) % MOD;
}
ll K(ll n) {
    return (2 * n * r) % MOD;
}
void solve() {
    ll n, k, x;
    vector<ll> v;

    cin >> n >> k;

    ll N = n + 6;
    matrix a(N, N), init(N, 1);
    for(int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }
    for(int i = 0; i < n; i++) {
        cin >> x;
        a.v[0][i] = x;
    }
    cin >> p >> q >> r;

    if(k < n) {
        cout << v[k] << endl;
        return;
    }

    a.v[0][n] = 1;
    a.v[0][n+1] = 1;
    a.v[0][n+2] = 1;
    a.v[0][n+3] = 1;
    a.v[0][n+4] = 1;
    a.v[0][n+5] = 1;

    for(int i = 1; i < n; i++) {
        a.v[i][i-1] = 1;
    }

    a.v[n][n] = 1;
    a.v[n][n+4] = 1;

    a.v[n+1][n+1] = 1;
    a.v[n+1][n+2] = 1;
    a.v[n+1][n+5] = 1;

    a.v[n+2][n+2] = 1;
    a.v[n+2][n+5] = 2;

    a.v[n+3][n+3] = 1;
    a.v[n+4][n+4] = 1;
    a.v[n+5][n+5] = 1;

    // a.print();

    matrix ans = a.pow(k - n + 1);

    for(int i = 0; i < n; i++) {
        init.v[i][0] = v[n - i - 1];
    }
    init.v[n][0] = F(n - 1);
    init.v[n+1][0] = G(n - 1);
    init.v[n+2][0] = K(n - 1);
    init.v[n+3][0] = p;
    init.v[n+4][0] = q;
    init.v[n+5][0] = r;

    ans = ans * init;
    cout << ans.v[0][0] << endl;
}

int32_t main() {
    FAST

    int TC = 1;

    //cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
