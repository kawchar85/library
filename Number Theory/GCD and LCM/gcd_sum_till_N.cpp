/**
    G(N) = summation of gcd(i,N) for i=1 to N
         = summation of (d* phi(N/d) ) for all d|N
*/

#include<bits/stdc++.h>
#define MAX 500005
typedef long long ll;
using namespace std;

ll phi[MAX],G[MAX];
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

void GCD_SUM()
{
    Euler_Phi();

    int i,j;
    for(i=1; i<MAX; i++)
    {
        for(j=i; j<MAX; j+=i)
            G[j]+=i*phi[j/i];
    }
}

int main()
{
    GCD_SUM();
    cout<<G[10]<<endl;
}
