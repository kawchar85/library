#include<bits/stdc++.h>
#define sz 200
using namespace std;

bool siv[sz];
int prime[sz],cnt;

void sieve()
{
    int i,j;
    for(i=3; i<sz; i+=2)
        if(!siv[i])
            for(j=i*i; j<sz; j+=i+i)
                siv[j]=1;
    prime[cnt++]=2;
    for(i=3; i<sz; i+=2)
        if(!siv[i]) prime[cnt++]=i;
}

int PrimePower(int n, int p)
{
    int cnt=0,d=p;
    int x=1;
    while(x)
    {
        x=n/d;
        cnt+=x;
        d*=p;
    }
    return cnt;
}
map<int,int>p;
void facorial_factorization(int n)
{
    p.clear();
    int i;
    for(i=0; prime[i]<=n; i++)
    {
        p[prime[i]]=PrimePower(n, prime[i]);
    }
}

int main()
{
    sieve();
    int i,t,n;

    scanf("%d",&t);
    for(i=1;i<=t;i++)
    {
        scanf("%d",&n);
        facorial_factorization(n);
        printf("Case %d: %d =",i,n);
        for(auto it=p.begin(); it!=p.end(); it++)
        {
            if(it!=p.begin())
                printf(" *");
            printf(" %d (%d)",it->first,it->second);
        }
        puts("");

    }
    return 0;
}
