#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

ll BigMod(ll n, ll p)
{
    ll result=1;
    while(p>0)
    {
        if(p&1)
        {
            result*=n;
            if(result>MOD)
                result%=MOD;
        }
        p>>=1;
        n*=n;
        if(n>MOD)
            n%=MOD;
    }
    return result;
}

ll mod(ll n,ll p)
{
    ll temp;
    if(p==0)
        return 1;
     temp=mod(n,p/2);
     temp=(temp*temp)%MOD;
    if(p&1)
        temp=(temp*n)%MOD;
    return temp;
}

ll inv(ll n)
{
	return mod(n, MOD-2);
}

ll mul(ll x, ll y)
{
	return (((x%MOD)*(y%MOD))%MOD);
}

ll add(ll A, ll B)
{
	return (A%MOD + B%MOD )%MOD;
}

ll dvd(ll A, ll B)
{
    return mul(A, inv(B));
}

ll sub(ll A, ll B)
{
    return (A%MOD-B%MOD+MOD)%MOD;
}

int main()
{

}
