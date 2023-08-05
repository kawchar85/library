/**
 https://vjudge.net/contest/572359#problem/I

 M[i][j] => the number of edges connecting vertex i to vertex j
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
                    ans.v[i][j] = (ans.v[i][j] + v[i][k] * a.v[k][j] % MOD) % MOD;
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

vector<ll> specialMul (vector<ll> v, const matrix &a) {
    vector<ll> ans(v.size());
    ll tmp;
    for(int j = 0; j < a.m; j++) {
        for(int k = 0; k < a.m; k++) {
            // ans[j] = (ans[j] + v[k] * a.v[k][j] % MOD) % MOD;
            tmp = v[k] * a.v[k][j];
            if(tmp >= MOD) tmp %= MOD;
            tmp += ans[j];
            if(tmp >= MOD) tmp %= MOD;
            ans[j] = tmp;
        } 
    }
    return ans;
}
matrix M[30];
void preCal(matrix a) {
    M[0] = a;
    for(int i = 1; i < 30; i++) {
        // M[i] = a.pow(1<<i);
        M[i] = M[i - 1] * M[i - 1];
    }
}

void solve() {
    ll n, m, q, k, x, y;
    cin >> n >> m >> q;

    matrix a(n, n);
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        x--; y--;
        a.v[x][y]++;
    }
    preCal(a);

    matrix unit(n, n); unit.make_unit();
    while(q--) {
        cin >> x >> y >> k;
        x--; y--;
        vector<ll> ans = unit.v[x];
        for(int j = 0; j < 30; j++) {
            if(k & (1 << j)) {
                ans = specialMul(ans, M[j]);
            }
        } 

        cout << ans[y] << endl;
    }
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
