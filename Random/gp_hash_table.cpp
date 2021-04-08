#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash{
    int operator()(int x) const { return x ^ RANDOM; }
};
//gp_hash_table<key, int, chash> table;
gp_hash_table<int, int, chash> table;

/*
struct chash {
    int operator()(pii x) const { return x.first* 31 + x.second; }
};
gp_hash_table<pii, int, chash> table;
*/

int main()
{
    int n,i,x;
    n=10;

    for(i=0; i<=n; i++)
        table[i]=10*i;

    for(i=0; i<=n; i++)
        cout<<i<<" "<<table[i]<<endl;

    return 0;
}
