#include<bits/stdc++.h>
#define ll long long
using namespace std;

///O(r)
ll C(ll n, ll r)
{
    if(r>n) return 0;

    double fact=1.0;
    for(ll i=1; i<=r; ++i)
        fact=fact*(n-r+i)/i;

    return (ll)(fact+0.001);
}

int main()
{
    ll n,r;
    while(cin>>n>>r)
        cout<<C(n,r)<<endl;
}
