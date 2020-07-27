#include<bits/stdc++.h>
#define ll long long
using namespace std;

/**
 nCr=n!/(r!*(n-r)!)
 time & space O(n)
 upto 19!
 for N<20
*/
ll C(ll n, ll r)
{
    if(r>n) return 0;
    ll fact[n+1];
    fact[0]=1;
    for(ll i=1; i<=n; i++)
        fact[i]=i*fact[i-1];
    return fact[n]/fact[r]/fact[n-r];
}

int main()
{
    ll n,r;
    while(cin>>n>>r)
        cout<<C(n,r)<<endl;
}
