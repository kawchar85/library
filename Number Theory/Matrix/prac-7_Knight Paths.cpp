/**
 https://vjudge.net/contest/572359#problem/E
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 4294967296
#define MAX 200005

typedef long long ll;
int xk[]={1,1,2,2,-1,-1,-2,-2}; int yk[]={2,-2,1,-1,2,-2,1,-1};
#define valid(x, y) (x >= 0 && x < 8 && y >= 0 && y < 8)

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
                    ans.v[i][j] = (ans.v[i][j] +  (__int128)v[i][k] * a.v[k][j] % MOD) % MOD;
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
    ll n, m, k, x, y;
    cin >> k;

    matrix a(65, 65);
    a.v[64][64] = 1;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int node1 = i * 8 + j;
            for(int d = 0; d < 8; d++) {
                x = i + xk[d];
                y = j + yk[d];
                int node2 = x * 8 + y;
                if(valid(x, y))
                    a.v[node1][node2] = 1;
            }
            a.v[node1][64] = 1;
        }
    }
    
    // a.print();

    matrix ans = a.pow(k+1);
    cout << ans.v[0][64] << endl;

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
