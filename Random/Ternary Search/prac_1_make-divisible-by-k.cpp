/*
https://toph.co/p/help-chokro
*/

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

vector<int> v;
int k;

ll F(int x) {
    ll sum = 0, tar = 1LL*x*k;

    for(auto val : v) {
        sum += abs(tar - val);
    }
    return sum;
}

void solve() {
    int n, x;

    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }

    ll mn = -1;
    int l = 0, r = 1000000, m1, m2;
    while(l <= r) {
        m1 = l + (r - l) / 3;
        m2 = r - (r - l) / 3;

        auto f1 = F(m1);
        auto f2 = F(m2);

        if(f1 == f2) {
            mn = f1;
        }

        if(f1 < f2) {
            r = m2 - 1;
        }
        else {
            l = m1 + 1;
        }
    }

    cout << mn << endl;
    
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
