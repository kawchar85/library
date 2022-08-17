
/***
    Given an array of n numbers. 0<=ai<=MAX.
    Count the GCD of sub-array of size K.

    grp[x] = total sub-array of size K with GCD x.
*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MAX 100000 //1e5
#define MOD 1000000007

ll fact[MAX+5],grp[MAX+5];

ll bigmod(ll n,ll p)
{
    ll temp;
    if(p==0)
        return 1;
    temp=bigmod(n,p/2);
    temp=(temp*temp)%MOD;
    if(p&1)
        temp=(temp*n)%MOD;
    return temp;
}

ll inv(ll n)
{
	return bigmod(n, MOD-2);
}
ll nCr(ll n, ll r)
{
    if(r>n) return 0;
    return ((fact[n]*inv(fact[r]))%MOD*inv(fact[n-r]))%MOD;
}

int main()
{

	fact[0]=1;
	for(ll i=1;i<=MAX;i++) fact[i]=(fact[i-1]*i)%MOD;

	ll n,k,x,sq;
	cin>>n>>k;

	for(ll i=1; i<=n; i++)
	{
		cin>>x;
		sq=sqrt(x);
		for(ll j=1; j<=sq; j++)
        {
			if(x%j==0)
			{
				grp[j]++;
				if(j*j!=x) grp[x/j]++;
			}
		}
	}

	for(ll i=1;i<=MAX;i++)
    {
        grp[i]=nCr(grp[i], k);
	}

	for(ll i=MAX;i>=1;i--)
    {
		for(ll j=i+i;j<=MAX;j+=i)
		{
			grp[i]=(grp[i]-grp[j]+MOD)%MOD;
		}
	}



	ll lmt;
	cin>>lmt;
	for(ll i=0; i<=lmt; i++)
        cout<<i<<" "<<grp[i]<<endl;

	return 0;
}

/**
5 3
2 3 2 6 8
10
*/
