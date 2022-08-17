#include<bits/stdc++.h>
#define ll long long
using namespace std;

///how many times prime p occurs in N!.

ll factPrimePower(ll n, ll p)
{
    ll cnt=0,x=n;
    while(x)
    {
        cnt+=x/p;
        x/=p;
    }
    return cnt;
}
ll factPrimePower2(ll n, ll p)
{
	ll cnt=0LL,d=p;
	ll x=1LL;
	while(x)
	{
		x=n/d;
		cnt+=x;
		d*=p;
	}
	return cnt;
}

int main()
{
    ll n=10,p=2;
    cout<<factPrimePower2(n,p)<<endl;
}
