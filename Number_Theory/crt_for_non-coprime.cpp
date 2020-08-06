/**
    A CRT solver which works even when moduli are not pairwise coprime
    Call CRT(k) to get {x, N} pair, where x is the unique solution modulo N.
    Assumptions:
        1. LCM of all mods will fit into long long.
*/

#include<bits/stdc++.h>
#define ll long long
#define pll pair<ll,ll> 
using namespace std;

//#define __int128 ll

ll r[15],p[15];

ll EGCD(ll a, ll b, ll &x, ll &y)
{
    if(a==0)
    {
        x=0; y=1;
        return b;
    }
    ll x1,y1;
    ll d = EGCD(b%a, a, x1, y1);
    x = y1 - (b/a)*x1;
    y = x1;
    return d;
}

//O(n*Log L) L=LCM(p1,p2,....)
pll CRT(ll n)
{
    ll r1,r2,p1,p2,x,y,ans,g,mod;
    r1=r[0],p1=p[0];
    for(int i=1; i<n; i++)
    {
        r2=r[i],p2=p[i];

        g=__gcd(p1,p2);
        if(r1%g != r2%g) return {-1, -1}; //no solution

        EGCD(p1/g, p2/g, x, y);
        mod=p1/g*p2;
        ans=((__int128)r1*(p2/g)%mod*y%mod+(__int128)r2*(p1/g)%mod*x%mod)%mod;

        r1=ans;
        if(r1<0) r1+=mod;
        p1=mod;

    }
    return {r1,mod};
}

int main()
{
    ll t,cs,i,n,ans,P;
    scanf("%lld",&t);
    for(cs=1; cs<=t; cs++)
    {
        scanf("%lld",&n);
        for(i=0; i<n; i++)
        {
            scanf("%lld %lld",&p[i],&r[i]);
        }
        ans=CRT(n).first;
        printf("Case %lld: %lld\n",cs,ans);
    }
    return 0;

}

