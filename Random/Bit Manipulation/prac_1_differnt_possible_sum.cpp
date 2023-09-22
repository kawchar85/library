/*
  how many different values [sum of some subset of coins] is he able to make (in given range)
  //https://vjudge.net/problem/SPOJ-ADACOINS
*/
#include<bits/stdc++.h>
using namespace std;

#define MAX 100005

int cum[MAX];
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> coins(n);
    for(int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    bitset<MAX> possible;
    possible.reset();
    possible[0] = 1;
    for(auto coin : coins) {
        auto new_poss = possible << coin;
        possible |= new_poss;
    }

    for(int i = 1; i < MAX; i++)
        cum[i] = cum[i - 1] + possible[i];

    while(q--) {
        int l, r; cin >> l >> r;

        // int len = r - l + 1;
        // auto tmp = possible >> l;
        // tmp = tmp << (MAX - len);
        // cout << tmp.count() << "\n";

        cout << cum[r] - cum[l - 1] << "\n";
    }
    return 0;
}
