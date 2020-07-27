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
        if(phi[i]==i) /// i is prime
        {
            phi[i]=i-1;
            for(j=i+i; j<MAX; j+=i)
                phi[j]=phi[j]/i*(i-1); ///i akta prime, ai i diye jeighula multiple, seighula n*(1-(1/i)) kortesi
        }
    }
}

int main()
{
    Euler();
    ll t,a;
    cin>>t;
    while(t--)
    {
        cin>>a;
        printf("phi[%lld]=%lld\n",a,phi[a]);
    }
}
