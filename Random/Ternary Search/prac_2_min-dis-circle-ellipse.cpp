/*
https://toph.co/p/life-is-dark-and-full-of-error
*/

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define PI acos(-1.0)
typedef long long ll;

double cx, cy, r, h, k, a, b;

double F(double ang) {
    double x = a * cos(ang) + h;
    double y = b * sin(ang) + k;

    double d = (x - cx)*(x - cx) + (y - cy)*(y - cy);
    
    d = sqrt(d);
    d -= r;
    d = max(d, 0.0);
    return d;
}

double ternarySearch(double l, double r) {

    double tmp = (cx-h)*(cx-h)/(a*a) + (cy-k)*(cy-k)/(b*b) - 1.0;
    if(tmp < 1e-9) {
        // cout << "0.0000\n"; // circle=> inside ellipse
        return 0;
    }

    int cnt = 40;
    double m1, m2;
    while(cnt--) {
        m1 = l + (r - l) / 3.0;
        m2 = r - (r - l) / 3.0;

        auto f1 = F(m1);
        auto f2 = F(m2);

        if(f1 < f2) {
            r = m2;
        }
        else {
            l = m1;
        }
    }
    return F(l);
    // cout << fixed << setprecision(4) << F((l+r)/2.0) << endl;
}
    

void solve() {
    cin >> cx >> cy >> r >> h >> k >> a >> b;
    
    cout << fixed << setprecision(4) << min(ternarySearch(0, PI), ternarySearch(PI, 2*PI)) << endl;
}

int32_t main() {
    FAST

    int TC = 1;

    cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
