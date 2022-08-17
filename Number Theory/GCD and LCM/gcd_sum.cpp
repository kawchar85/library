#include<bits/stdc++.h>
#define MAX 500005
typedef long long ll;
using namespace std;

ll phi[MAX];
void Euler_Phi()
{
    int i,j;
    for(i=1; i<MAX; i++)
        phi[i]=i;
    for(i=2; i<MAX; i++)
    {
        if(phi[i]==i)
        {
            phi[i]=i-1;
            for(j=i+i; j<MAX; j+=i)
            {
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}

/**
    G(N) = summation of gcd(i,N) for i=1 to N
         = summation of (d* phi(N/d) ) for all d|N
*/

ll GCD_SUM(ll n)
{
    ll cnt=0;
    for(ll i=1; i*i<=n; i++)
    {
        if(i*i==n)
            cnt+=i*phi[n/i];
        else if(n%i==0)
        {
            cnt+=i*phi[n/i];
            ll x=n/i;
            cnt+=x*phi[n/x];
        }
    }
    return cnt;
}

int main()
{
    Euler_Phi();
    cout<<GCD_SUM(10LL)<<endl;
}
