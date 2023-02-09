/**
 https://judge.yosupo.jp/problem/matrix_product
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 998244353
#define MAX 200005

typedef long long ll;

struct matrix {
    int n, m;
    vector<vector<int>> v;
    matrix() {}
    matrix(int _n, int _m) {
        n = _n; m = _m;
        v.assign(n, vector<int>(m, 0));
    }
    matrix(vector<vector<int>> _v) {
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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    matrix a(n, m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a.v[i][j];
        }
    }

    matrix b(m, k);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < k; j++) {
            cin >> b.v[i][j];
      }
    }
    matrix ans = a * b;
    ans.print();
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
