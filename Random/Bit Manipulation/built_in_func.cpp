#include<bits/stdc++.h>
using namespace std;

int main()
{
    int x=7;
    long long y=7LL;
    cout<<__builtin_popcount(x)<<endl; ///count number of 1 in binary
    cout<<__builtin_popcountll(y)<<endl; ///count number of 1 in binary for ll
    cout<<__builtin_clz(x)<<endl; /// leading zeros
    cout<<__builtin_ctz(x+1)<<endl; /// trailing zeros
    x=38;
    cout<<(1<<__builtin_ctz(x))<<endl; ///the biggest power of 2 that is a divisor of x
}
