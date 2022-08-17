#include<bits/stdc++.h>
#define ll long long
#define MAX 1000006
using namespace std;

ll phi[MAX];
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

/**
    LSUM(N)=sum of LCM(i,N) for i=1 to N
           =(N/2)*(x+1)
    here x=sum of (d* phi(d) ) for all d|N

*/

ll LCM_SUM(ll n)
{
    ll i,j,sum=0;
    for(i=1; i*i<=n; i++)
    {
        if(n%i==0)
        {
            if(i*i==n)
                sum+=i*phi[i];
            else
            {
                j=n/i;
                sum+=i*phi[i];
                sum+=j*phi[j];
            }
        }
    }
    sum+=1;
    sum*=n;
    sum/=2;
    return sum;
}

int main()
{
    Euler();
    ll t,a;
    cin>>t;
    while(t--)
    {
        cin>>a;
        printf("%lld\n",LCM_SUM(a));
    }
}

