#include<bits/stdc++.h>
using namespace std;
#define ll long long 



#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash {
    // any random-ish large odd number will do
    const uint64_t C = 2713661325311;
    const uint32_t RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    size_t operator()(uint64_t x) const {
        return __builtin_bswap64((x ^ RANDOM) * C);
    }
    size_t operator()(pair<uint64_t, uint64_t> x) const { 
        return x.first* 31 + x.second;
        //return __builtin_bswap64(((x.first* 31 + x.second) ^ RANDOM) * C);
    }
};
gp_hash_table<int,int, chash> freq;
gp_hash_table<ll, ll, chash> table;
gp_hash_table< pair<int,int>, ll, chash > test;

int main() {
    int n, i, x;
    n = 12;

    for(i = 0; i <= n; i++)
        table[i] = pow(10, i);

    for(i = 0; i <= n; i++)
        cout << i << " " << table[i] << endl;

    for(i = 0; i <= n; i++)
        test[{i, i}] = pow(10, i);

    for(i = 0; i <= n; i++)
        cout << "{" << i << "," << i << "} " << test[{i,i}] << endl;


    return 0;
}
