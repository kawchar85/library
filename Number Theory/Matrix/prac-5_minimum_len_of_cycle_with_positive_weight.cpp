/**
 https://codeforces.com/contest/147/problem/B

 min length of cycle with positive weight
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
    vector<vector<int>> v;
    matrix() {}
    matrix(int _n, int _m) {
        n = _n; m = _m;
        v.assign(n, vector<int>(m, -1000000000));
    }
    matrix(vector<vector<int>> _v) {
        n = _v.size(); 
        m = n ? _v[0].size() : 0;
        v = _v;
    }
    void make_unit() {
        assert(n == m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++){
                v[i][j] = (i != j) * -1000000000;
            }
    }
    matrix operator + (const matrix &a) {
        assert(n == a.n && m == a.m);
        matrix ans = matrix(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
            ans.v[i][j] = (v[i][j] + a.v[i][j]);
          }
        }
        return ans;
    }
    matrix operator - (const matrix &a) {
        assert(n == a.n && m == a.m);
        matrix ans = matrix(n, m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                ans.v[i][j] = (v[i][j] - a.v[i][j]);
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
                    //max--plus
                    ans.v[i][j] = max(ans.v[i][j], v[i][k] + a.v[k][j]);
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
    ll n, m, k, x, y, w1, w2, len = 0;
    cin >> n >> m;

    matrix a(n, n);
    a.make_unit();
    // a.print();
    for(int i = 0; i < m; i++) {
        cin >> x >> y >> w1 >> w2;
        x--; y--;
        a.v[x][y] = w1;
        a.v[y][x] = w2;
    }
    

    matrix ans;
    ll l = 1, r = n;
    while(l <= r) {
        m = (l + r) / 2;
        ans = a.pow(m);

        bool ok = 0;
        for(int i = 0; i < n; i++)
            ok |= ans.v[i][i] > 0;
        // ans.print();
        if(ok) {
            len = m;
            r = m - 1;
        } else l = m + 1;

        // cout << ok << " " << m << endl;
    } 
    
    cout << len << endl;
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
