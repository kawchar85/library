#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define MAX 1000006
using namespace std;

bool siv[MAX];
vector<ll>prime,fact;

///O(n*Lg(Lg(n)))
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

///O(Primes + Lg(n))
///primes= sqrt(n)/ln(sqrt(n))
void Factorization(ll n)
{
    for(ll i=0; i<prime.size()&&prime[i]*prime[i]<=n; i++)
    {
        if(n%prime[i]==0)
        {
            while(n%prime[i]==0)
            {
                fact.pb(prime[i]);
                n/=prime[i];
            }
        }
    }
    if(n>1)
        fact.pb(n);
}

int main()
{
    sieve();
    Factorization(100);
    for(auto x : fact)
        cout<<x<<" ";
    return 0;
}
