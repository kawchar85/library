/**
 https://vjudge.net/contest/572359#problem/F

 shortest path of length k
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;
#define int long long

const int inf = 2000000000000000005LL; 
const int threshold = 1000000000000000000LL;
struct matrix {
    int n, m;
    vector<vector<int>> v;
    matrix() {}
    matrix(int _n, int _m) {
        n = _n; m = _m;
        v.assign(n, vector<int>(m, inf));
    }
    matrix(vector<vector<int>> _v) {
        n = _v.size(); 
        m = n ? _v[0].size() : 0;
        v = _v;
    }
    void make_unit() {
        assert(n == m);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) {
                v[i][j] = (i != j) * inf;
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
                    //min--plus
                    ans.v[i][j] = min(ans.v[i][j],  min(inf, v[i][k] + a.v[k][j]));
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
    int n, m, k, x, y, w;
    cin >> n >> m >> k;

    matrix a(n, n);
    for(int i = 0; i < m; i++) {
        cin >> x >> y >> w;
        x--; y--;
        a.v[x][y] = w;
    }
    // a.print();
    

    matrix ans = a.pow(k);
    // ans.print();
    
    int mn = inf;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mn = min(mn, ans.v[i][j]);
    if(mn > threshold)
        cout << "IMPOSSIBLE\n";
    else cout << mn << "\n";
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
