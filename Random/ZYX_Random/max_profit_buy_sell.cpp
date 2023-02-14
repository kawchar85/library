/**
    https://codeforces.com/contest/865/problem/D
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

void solve() {
    int n, x;
    ll sum = 0;
    priority_queue<int> q;

    cin >> n;

    q.push(INT_MIN+1);
    for(int i = 0; i < n; i++) {
        cin >> x;

        if( -q.top() < x) { // ajker theke previous day te lower price chilo
            sum -= -q.top(); //buy
            q.pop();
            sum += x; // sell

            q.push(-x); //for swap with another day
            q.push(-x); //reuse; swap korle ei day te pore buy possible
        }
        else {
            q.push(-x); //avail for use/buy
        }
    }

    cout << sum << endl;
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
