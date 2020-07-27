#include<bits/stdc++.h>
#define ll long long
using namespace std;

///O(log10(min(A,B)))
ll gcd(ll a, ll b)
{
    if(a==0)
        return b;
    return gcd(b%a,a);
}

ll lcm(ll a, ll b)
{
    return (a/gcd(a,b))*b;
}

int main()
{
    ll a,b;
    while(cin>>a>>b)
    cout<<"Gcd="<<gcd(a,b)<<" Lcm="<<lcm(a,b)<<endl;
    return 0;
}
