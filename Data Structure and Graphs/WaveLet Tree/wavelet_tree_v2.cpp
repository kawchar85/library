/*
    author: steinum
*/
#include<bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define x first
#define y second
int n;
struct wavelet_tree {
    static const int unfound = INT_MIN;
    static const int maxn = 1e5 + 5;
    static const int mlog = 20;
    typedef int Int;
    typedef long long Long;
    Int s[maxn], tree[mlog][maxn];
    int L[mlog][maxn];
    Long ls[mlog][maxn], sl;

    Int & operator[](int x) {return tree[0][x];}

    void build(int l = 1, int r = n, int d = 0) {
        if (l == r)return;
        int m = (l + r) >> 1, cnt = 0, lc = l, rc = m + 1, ec = 0;
        for (int i = l; i <= r; i++)if (tree[d][i] < s[m])cnt++;
        for (int i = l; i <= r; i++) {
            if ( (tree[d][i] < s[m]) || (tree[d][i] == s[m] && ec < (m - l + 1 - cnt) ) ) {
                tree[d + 1][lc++] = tree[d][i];
                ls[d + 1][i] = ls[d + 1][i - 1] + tree[d][i];
                if (tree[d][i] == s[m])ec++;
            } else {
                tree[d + 1][rc++] = tree[d][i];
                ls[d + 1][i] = ls[d + 1][i - 1];
            } L[d][i] = L[d][l - 1] + lc - l;
        } build(l, m, d + 1); build(m + 1, r, d + 1);
    }
    void init(Int *arr, int n) {
        for (int i = 1; i <= n; i++)tree[0][i] = arr[i];
        init(n);
    }
    void init(int n) {
        for (int i = 1; i <= n; i++)s[i] = tree[0][i], ls[0][i] = ls[0][i - 1] + s[i];
        sort(s + 1, s + 1 + n); build();
    }
    Long sum(pii a, int d = 0) {return ls[d][a.y] - ls[d][a.x - 1];}
    int cn(pii a, int d) {return L[d][a.y] - L[d][a.x - 1];}
    pii left(pii a, int d, int l) {return {l + cn({l, a.x - 1}, d), l - 1 + cn({l, a.y}, d)};}
    pii right(pii a, int d, int r) {return {a.x + cn({a.x, r}, d), a.y + cn({a.y + 1, r}, d)};}

    Int kth(int x, int y, int k, int l = 1, int r = n, int d = 0) {
        if (y - x + 1 < k || x > y)return unfound;
        if (l == r) {
            sl += tree[d][l];
            return tree[d][l];
        } int cnt = cn({x, y}, d), m = (l + r) >> 1, nx, ny;
        if (cnt >= k) {
            tie(nx, ny) = left({x, y}, d, l);
            return kth(nx, ny, k, l, m, d + 1);
        } else {
            sl += sum({x, y}, d + 1);
            tie(nx, ny) = right({x, y}, d, r);
            return kth(nx, ny, k - cnt, m + 1, r, d + 1);
        }
    }

    int leq(int x, int y, Int k, int l = 1, int r = n, int d = 0) {
        if (x > y)return 0;
        if (l == r) {
            if (l > y || l < x)return 0; // is it important?
            sl += tree[d][l] * (tree[d][l] <= k);
            return tree[d][l] <= k;
        } int cnt = cn({x, y}, d), m = (l + r) >> 1, nx, ny;
        if (s[m] <= k) {
            sl += sum({x, y}, d + 1);
            tie(nx, ny) = right({x, y}, d, r);
            return cnt + leq(nx, ny, k, m + 1, r, d + 1);
        } else {
            tie(nx, ny) = left({x, y}, d, l);
            return leq(nx, ny, k, l, m, d + 1);
        }
    }

    Int rmin(int x, int y, int l = 1, int r = n, int d = 0) {return kth(x, y, 1, l, r, d);}
    Int rmax(int x, int y, int l = 1, int r = n, int d = 0) {return kth(x, y, y - x + 1, l, r, d);}
    Int floor(int x, int y, Int k, int l = 1, int r = n, int d = 0) {
        if (x > y)return INT_MIN;
        if (l == r) {
            if (l > y || l < x)return INT_MIN;
            return (tree[d][l] <= k ? tree[d][l] : INT_MIN);
        } Int ans = INT_MIN; int m = (l + r) >> 1, nx, ny;
        if (s[m] <= k) {
            tie(nx, ny) = right({x, y}, d, r);
            ans = max(ans, floor(nx, ny, k, m + 1, r, d + 1));
            if (ans == INT_MIN) {
                tie(nx, ny) = left({x, y}, d, l);
                auto an = rmax(nx, ny, l, m, d + 1);
                if (an != unfound)ans = max(ans, an);
            }
        } else {
            tie(nx, ny) = left({x, y}, d, l);
            ans = max(ans, floor(nx, ny, k, l, m, d + 1));
        } return ans;
    }
    Int ceil(int x, int y, Int k, int l = 1, int r = n, int d = 0) {
        if (l == r) {
            if (l > y || l < x)return INT_MAX;
            return (tree[d][l] >= k ? tree[d][l] : INT_MAX);
        } Int ans = INT_MAX; int m = (l + r) >> 1, nx, ny;
        if (s[m] >= k) {
            tie(nx, ny) = left({x, y}, d, l);
            ans = min(ans, ceil(nx, ny, k, l, m, d + 1));
            if (ans == INT_MAX) {
                tie(nx, ny) = right({x, y}, d, r);
                auto an = rmin(nx, ny, m + 1, r, d + 1);
                if (an != unfound)ans = min(ans, an);
            }
        } else {
            tie(nx, ny) = right({x, y}, d, r);
            ans = min(ans, ceil(nx, ny, k, m + 1, r, d + 1));
        } return ans;
    }
} wvt; 

int32_t main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> wvt[i];
    }
    wvt.init(n);

    cout << wvt.kth(5, 7, 2) << endl;
    cout << wvt.sl << endl;

    wvt.sl = 0;
    cout << wvt.leq(5, 7, 70) << endl;
    cout << wvt.sl << endl;

    cout << wvt.floor(5, 7, 55) << endl;
 
    return 0;
}
