
//Use __int128 to avoid overflow
#include<bits/stdc++.h>
#define ll long long
using namespace std;

//#define ll __int128

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

ll inverse(ll a, ll m)
{
    ll g,x,y;
    g = EGCD(a,m,x,y);
    if(g!=1)
        return -1LL; /// no inverse
    x%=m;
    if(x<0) x+=m;
    return x;
}

//O(n*LogP)
ll CRT(ll n, ll P)
{
    ll y,z,i,ans=0;
    for(i=0; i<n; i++)
    {
        y=P/p[i];
        z=inverse(y,p[i]);
        ans=(ans+r[i]*y*z)%P;
    }
    return (ans+P)%P;
}

int main()
{
    ll t,cs,i,n,ans,P;
    scanf("%lld",&t);
    for(cs=1; cs<=t; cs++)
    {
        scanf("%lld",&n);
        P=1;
        for(i=0; i<n; i++)
        {
            scanf("%lld %lld",&p[i],&r[i]);
            P*=p[i];
        }
        ans=CRT(n,P);
        printf("Case %lld: %lld\n",cs,ans);
    }
    return 0;

}

