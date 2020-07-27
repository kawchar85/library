#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 100005
#define inf 10000000
using namespace std;

bool siv[MAX];
vector<ll>prime;
map<ll,ll> A,B;
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

void prime_factorization(ll n, ll m)
{
    ll i,sq=sqrt(n),mul;
    for(i=0; i<prime.size()&&prime[i]<=sq; i++)
    {
        mul=1;
        if(n%prime[i]==0)
        {
            while(n%prime[i]==0)
            {
                n/=prime[i];
                mul*=prime[i];
            }
           sq=sqrt(n);
        }
        A[prime[i]]=mul;  
    }

    if(n>1){
        A[n]=n;
    }

    for(auto p : prime)
    {
        if(p*p>m) break;

        mul=1;
        while(m%p==0)
        {
            m/=p;
            mul*=p;
        }
        B[p]=mul;
    }
    if(m>1)
        B[m]=m;
}


int main()
{
    sieve();

    ll i,a,b,g=1,l=1;

    cin>>a>>b;
    prime_factorization(a, b);

    for(auto p : prime)
    {
        a=min(A[p],B[p]);
        b=max(A[p],B[p]);
        if(a) g*=a;
        if(b) l*=b;
    }
    
    cout<<g<<"___"<<l<<endl;

    return 0;
}
