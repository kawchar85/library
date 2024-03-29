///same as factorization
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
ll Euler_Phi(ll n)
{
    ll i,result=n;
    for(i=0; i<prime.size() && prime[i]*prime[i] <= n; i++)
    {
        if(n%prime[i]==0)
        {
            while(n%prime[i]==0)
                n/=prime[i];
            result=(result/prime[i])*(prime[i]-1);
        }
    }
    if(n>1)
        result=(result/n)*(n-1);
    return result;
}

int main()
{
    sieve();
    cout<<Euler_Phi(10);
    return 0;
}
