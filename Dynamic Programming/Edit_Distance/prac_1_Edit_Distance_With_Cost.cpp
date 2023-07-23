/**
 * https://vjudge.net/problem/Gym-100341D
 * */

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define MOD 1000000007
#define MAX 3003

typedef long long ll;
ll dp[MAX][MAX][2], b, in, d, c;
string s, t, ans;
vector<int> skip;

ll solve(int i, int j, int f) {
    if(i == s.size() && j == t.size()) return 0;
    if(i == s.size()) return in * (t.size() - j);
    if(j == t.size()) return min(b, d * ((ll)s.size() - i));

    ll x, y, z, w;
    if(~dp[i][j][f]) return dp[i][j][f];

    w = b * (1 - f) + solve(i+1, j, 1);
    x = in + solve(i, j+1, 0);
    y = d + solve(i+1, j, 0);
    if(s[i] == t[j])
        z = c + solve(i+1, j+1, 0);
    else z = INT_MAX;

    return dp[i][j][f] = min({w, x, y, z});
}

void print(int i, int j, int f) {
    if(i == s.size() && j == t.size()) return;
    if(i == s.size()) {
        int x = t.size() - j;
        for(int k = 0; k < x; k++)
            ans += "I";
        return;
    }

    if(j == t.size()) {
        int x = s.size() - i;

        if(b < 1LL * x * d) {
            for(int k = i; k < s.size(); k++)
                skip.push_back(k+1);
        }
        else {
            for(int k = 0; k < x; k++)
            ans += "D";
        }
        return;
    }

    ll x, y, z, w;
    w = b * (1 - f) + solve(i+1, j, 1);
    x = in + solve(i, j+1, 0);
    y = d + solve(i+1, j, 0);
    if(s[i] == t[j])
        z = c + solve(i+1, j+1, 0);
    else z = INT_MAX;

    if(solve(i, j, f) == w) {
        skip.push_back(i+1);
        print(i+1, j, 1);
    } else if(solve(i, j, f) == x) {
        ans += "I";
        print(i, j+1, 0);
    } else if(solve(i, j, f) == y) {
        ans += "D";
        print(i+1, j, 0);
    } else if(solve(i, j, f) == z) {
        ans += "C";
        print(i+1, j+1, 0);
    }

    return;
}
void solve() {
    cin >> b >> in >> d >> c >> s >> t;
    clean(dp, -1);

    cout << solve(0, 0, 0) << endl;
    print(0, 0, 0);
    vector< pair<int, int> > seg;
    int last = -1, l = -1, r = -1;

    for(auto x : skip) {
        if(x != last + 1) {
            if(last != -1)
                seg.push_back({l, r});
            l = r = x;
        } else {
            r = x;
        }
        last = x;
    }
    if(skip.size() ) {
        seg.push_back({l, r});
    }

    cout << seg.size() << endl;
    for(auto p : seg)
        cout << p.first << " " << p.second << endl;

    cout << ans << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;
    // freopen("block.in","r",stdin);
    // freopen("block.out","w",stdout);

    //cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
