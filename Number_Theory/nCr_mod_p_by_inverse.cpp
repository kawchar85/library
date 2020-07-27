#include<bits/stdc++.h>
#define ll long long
#define MAX 100005
using namespace std;

ll fact[MAX];

///(n^p)%MOD
ll BigMod(ll n, ll p, ll MOD)
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

/** Modular Multiplicative Inverse
    Using Euler's Theorem
    a^(phi(m)) = 1 (mod m)
    a^(m-1) = 1 (mod m)
    a^(m-2) = a^(-1) (mod m)
*/
ll inv(ll n, ll MOD)
{
    return BigMod(n,MOD-2,MOD);
}

/// O(n*Lg(r))
ll nCr(ll n, ll r, ll MOD)
{
    if(r>n) return 0;
    fact[0]=1;
    for(ll i=1; i<=n; i++)
        fact[i]=(i*fact[i-1])%MOD;
    return (fact[n]*(inv(fact[r],MOD)*(inv(fact[n-r],MOD))%MOD))%MOD;
}

int main()
{
    ll n,r,p;
    while(cin>>n>>r>>p)
        cout<<nCr(n,r,p)<<endl;
}
