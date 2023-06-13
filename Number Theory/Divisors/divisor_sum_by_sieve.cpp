#include<bits/stdc++.h>
#define ll long long
#define MAX 1000006
using namespace std;

bool siv[MAX];
vector<ll>prime;

///O(n*Lg(Lg(n)))
void sieve()
{
    ll i,j;
    for(i=3; i*i<MAX; i+=2)
        if(!siv[i])
            for(j=i*i; j<MAX; j+=i+i)
                siv[j]=1;
    prime.push_back(2);
    for(i=3; i<MAX; i+=2)
        if(!siv[i]) prime.push_back(i);
}

///O(Primes + Lg(n))
///primes= sqrt(n)/ln(sqrt(n))
ll SOD(ll n)
{
    ll i,x,mul=1;
    for(i=0; i<prime.size() && prime[i]*prime[i] <= n; i++)
    {
        x=prime[i];
        if(n%prime[i]==0)
        {
            while(n%prime[i]==0)
            {
                n/=prime[i];
                x*=prime[i];
            }
            x--;
            x/=(prime[i]-1);
            mul*=x;
        }
    }
    if(n>1)
    {
        x=n*n-1;
        x/=(n-1);
        mul*=x;
    }
    return mul;
}


int main()
{
    sieve();
    cout<<SOD(10);
    return 0;
}

