/**
    Tested on https://codeforces.com/contest/1731/problem/D
*/
#include<bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> st;

int merge(int a, int b, int c, int d) {
    return min({a, b, c, d});
}

//O(n*m*Log(max(n,m))
void buildSparseTable(vector<vector<int>> &arr, int n, int m) { //0-based
    int LOG = log2(max(n, m))+1;
    vector<vector<vector<int>>>().swap(st); //clear
    st.resize(n, vector<vector<int>>(m, vector<int>(LOG)));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            st[i][j][0] = arr[i][j];
        }
    }

    for(int k = 1; k < LOG; k++) {
        for(int i = 0; i + (1<<k) <= n; i++) {
            for(int j = 0; j + (1<<k) <= m; j++) {
                st[i][j][k] = merge(
                    st[i][j][k-1],
                    st[i+(1<<(k-1))][j][k-1],
                    st[i][j+(1<<(k-1))][k-1],
                    st[i+(1<<(k-1))][j+(1<<(k-1))][k-1]
                );
            }
        }
    }
}

//O(merge())
int query(int x1, int y1, int x2, int y2) { //0-based
    int k = log2(min(x2-x1+1, y2-y1+1))+1;
    return merge(
        st[x1][y1][k-1],
        st[x2-(1<<(k-1))+1][y1][k-1],
        st[x1][y2-(1<<(k-1))+1][k-1],
        st[x2-(1<<(k-1))+1][y2-(1<<(k-1))+1][k-1]
    );
}

bool check(int len, int n, int m) {
    for(int i = 0; i + len - 1 < n; i++) {
        for(int j = 0; j + len - 1 < m; j++) {
            int mn = query(i, j, i+len-1, j+len-1);
            if(mn >= len) return 1;
        }
    }

    return 0;
}

void solve() {
    int n, m, ans = 1;
    cin >> n >> m;

    vector<vector<int>> arr(n, vector<int>(m)); 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    buildSparseTable(arr, n, m);

    int l = 1, h = min(n, m), mid;
    while(l <= h) {
        mid = (l + h) / 2;
        if(check(mid, n, m)) {
            ans = mid;
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }

    cout << ans << "\n";
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
