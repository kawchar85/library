#include<bits/stdc++.h>
#define pb push_back
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
    prime.pb(2);
    for(i=3; i<MAX; i+=2)
        if(!siv[i]) prime.pb(i);
}

///O(Primes + Lg(n))
///primes= sqrt(n)/ln(sqrt(n))
ll NOD(ll n)
{
    ll sq=sqrt(n),i,x,sum=1;
    for(i=0; i<prime.size()&&prime[i]<=sq; i++)
    {
        if(n%prime[i]==0)
        {
            x=1;
            while(n%prime[i]==0)
            {
                n/=prime[i];
                x++;
            }
            sum*=x;
            sq=sqrt(n);
        }
    }
    if(n>1)
        sum*=2;
    return sum;
}

int main()
{
    sieve();
    cout<<NOD(10);
    return 0;
}
