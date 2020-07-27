#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007
#define M 60

ll n;
ll A[M][M],I[M][M];

void mul(ll A[][M], ll B[][M])
{
    ll temp[M][M],i,j,k;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            temp[i][j]=0LL;
            for(k=0; k<n; k++)
            {
                temp[i][j]=(temp[i][j]+(A[i][k]*B[k][j])%MOD)%MOD;
            }
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            A[i][j]=temp[i][j];
    }
}

void power(ll A[][M], ll p)
{
    while(p)
    {
        if(p&1)
        {
            mul(I, A);
            p--;
        }
        else
        {
            mul(A, A);
            p/=2LL;
        }
    }

    for(ll i=0; i<n; i++)
    {
        for(ll j=0; j<n; j++)
            printf("%lld ",I[i][j]);
        puts("");
    }
}

int main()
{
    ll t,p,i,j;
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld %lld",&n,&p);
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                scanf("%lld",&A[i][j]);
                if(i==j) I[i][j]=1LL;
                else I[i][j]=0LL;
            }
        }
        power(A, p);
    }

    return 0;
}
