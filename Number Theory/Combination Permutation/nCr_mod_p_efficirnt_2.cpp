#include<bits/stdc++.h>
#define MAX 10000001
#define ll long long
#define MOD 1000000007
using namespace std;

ll fact[MAX];

///O(Lg N)
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

///O(Lg MOD)
ll inv(ll n)
{
    return BigMod(n, MOD-2);
}

///O(Lg MOD)
ll nCr(ll n, ll r)
{
    if(r>n) return 0;
    return ((fact[n]*inv(fact[r]))%MOD*inv(fact[n-r]))%MOD;
}

///O(N)
void PreCalculaton()
{
    ll i;
    fact[0]=1;
    for(i=1; i<MAX; ++i)
        fact[i]=i*fact[i-1]%MOD;
}
int main()
{
    PreCalculaton();
    ll n,r;
    while(cin>>n>>r)
        cout<<nCr(n,r)<<endl;
}


