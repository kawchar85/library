/**
https://turing13.wordpress.com/2017/05/22/ncrm-when-m-is-not-prime-and-n-and-r-is-sufficiently-large/
*/
#include <bits/stdc++.h>
using namespace std;
#define MAX 1000006
#define MOD 1000000007
#define pb push_back
typedef long long ll;

vector<pair<ll,ll> >factor;
ll factorial[MAX];
ll arr[MAX];
vector<ll>ans;
bool siv[MAX];
vector<ll>prime;

///O(n*lg(lg(n)))
void sieve()
{
    ll i,j;
    for(i=3; i*i<MAX; i+=2)
        if(!siv[i])
            for(j=i*i; j<MAX; j+=i+i)
                siv[j]=1;
    prime.pb(2);
    for(i=3; i<MAX; i+=2)
        if(!siv[i]) prime.pb(i);
}



void precal(ll p, ll q, ll mod)
{
    arr[0]=1;
    arr[1]=1;
    ll x=1;
    for(ll i=2; i<=mod; i++)
    {
        if(i%p)
            x=i;
        else
            x=1;
        arr[i]=(arr[i-1]*x)%mod;
    }
}

ll bigmod(ll n, ll p, ll mod)
{
    ll ret=1;
    while(p)
    {
        if(p&1)
            ret=(ret*n)%mod;
        n=(n*n)%mod;
        p/=2;
    }
    return ret;
}

ll E(ll n, ll p)
{
    ll ret=0;
    while(n)
    {
        ret+=n/p;
        n=n/p;
    }
    return ret;
}

ll f(ll n, ll mod)
{
    ll ret=bigmod(arr[mod-1],n/mod,mod)*arr[n%mod];
    return ret;
}

ll F(ll n, ll mod, ll p)
{
    ll ret=1;
    ll i=1;
    while(i<=n)
    {
        ret=(ret*f(n/i,mod))%mod;
        i=i*p;
    }
    return ret;
}

ll inv(ll a, ll m) // Calculating Modular Multiplicative Inverse
{
    ll m0 = m, t, q;
    ll x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

//     Apply extended Euclid Algorithm
    while (a > 1)
    {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    return x1;
}




ll nCr(ll n, ll r, ll p, ll mod)
{
    ll e=E(n,p)-E(r,p)-E(n-r,p);
    ll mod1=F(n,mod,p);
    ll mod2=(F(r,mod,p)*F(n-r,mod,p))%mod;
    mod2=inv(mod2,mod);
    ll ret=bigmod(p,e,mod);
    ret*=mod1;
    ret%=mod;
    ret*=mod2;
    ret%=mod;
    return ret;
}

ll findMinX(int k) // Chinese Remainder
{
    ll prod = 1;
    vector<ll>num;
    for(ll i=0; i<k; i++)
    {
        num.pb(bigmod(factor[i].first,factor[i].second,MOD));
    }
    for (ll i = 0; i < k; i++)
        prod *= num[i];

    ll result = 0;

    for (ll i = 0; i < k; i++)
    {
        ll pp = prod / num[i];
        result += ans[i] * inv(pp, num[i]) * pp;
    }

    return result % prod;
}

ll nCr_mod_m(ll n, ll r, ll m)
{
    factor.clear();
    ans.clear();
    ll root=sqrt(m);
    ll mm=m;
    for(ll i=0; i<prime.size() && prime[i]<=root; i++)
    {
        if(mm%prime[i]==0)
        {
            ll cnt=0;
            while(mm%prime[i]==0)
            {
                mm/=prime[i];
                cnt++;
            }
            factor.pb(make_pair(prime[i],cnt));
            root=sqrt(mm);
        }
    }

    if(mm>1)
        factor.pb(make_pair(mm,1));



    for(ll i=0; i<factor.size(); i++)
    {
        ll p=factor[i].first;

        ll num=bigmod(p,factor[i].second,MOD);
        precal(p,factor[i].second,num);
        ans.pb(nCr(n,r,p,num));
    }

    ll anss=findMinX(factor.size());
    return anss;
}

int main()
{
    sieve();

    ll t;
    cin>>t;
    while(t--)
    {
        ll n,r,m;
        cin>>n>>r>>m;

        ll ans=nCr_mod_m(n,r,m);
        if(r>n) ans=0;

        printf("%lld C %lld mod %lld = %lld\n",n,r,m,ans);
    }

    return 0;
}
