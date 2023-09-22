/*
  https://codeforces.com/contest/1194/problem/E
*/
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll nC2(int n) {
    return (1LL * n * (n - 1)) / 2LL;
}

bool inRange(int x, pair<int, int> p) {
    return p.first <= x && x <= p.second;
}

int32_t main() {
    vector< pair<int, pair<int,int> > > vert, hori;

    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);

        if(y1 == y2) hori.push_back({y1, {x1, x2}});
        else if(x1 == x2) vert.push_back({x1, {y1, y2}});
    }

    if(vert.size() > hori.size()) swap(vert, hori);

    bitset<5003> intersect[vert.size() + 3];
    for(int i = 0; i < vert.size(); i++) {
        for(int j = 0; j < hori.size(); j++) {
            intersect[i][j] = inRange(vert[i].first, hori[j].second) && inRange(hori[j].first, vert[i].second);
        }
    }

    ll ans = 0;
    for(int i = 0; i < vert.size(); i++) {
        for(int j = i + 1; j < vert.size(); j++) {
            ans += nC2((intersect[i]&intersect[j]).count());
        }
    }

    cout << ans << endl;
    return 0;
}
