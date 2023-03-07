/*
https://toph.co/p/help-chokro
*/

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);

typedef long long ll;

ll F(int x) {
    return 100 + x*x;
}

void ternarySearch() {
    ll mn = INT_MAX;
    int l = -1000, r = 1000, m1, m2;
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
        ternarySearch();
    }

    return 0;
}
