#include<bits/stdc++.h>
#define ll long long
#define MAX 1000006
using namespace std;

ll phi[MAX],sum[MAX];
///O(nLg(n))
void Euler()
{
    ll i,j;

    for(i=0; i<MAX; i++)
        phi[i]=i;
    for(i=2; i<MAX; i++)
    {
        if(phi[i]==i)
        {
            phi[i]=i-1;
            for(j=i+i; j<MAX; j+=i)
                phi[j]=phi[j]/i*(i-1);
        }
    }
}

///O(nLg(n))
void LCM_SUM(ll n)
{
    for(ll i=1; i<=n; i++)
    {
        for(ll j=i; j<=n; j+=i)
            sum[j]+=(i*phi[i]);
    }
}

ll getSum(ll n)
{
    ll ans=sum[n]+1;
    ans*=n;
    ans/=2;
    return ans;
}
int main()
{
    Euler();
    LCM_SUM(MAX-6);
    ll t,n,ans;
    cin>>t;
    while(t--)
    {
        cin>>n;
        printf("%lld\n",getSum(n));
    }
}

