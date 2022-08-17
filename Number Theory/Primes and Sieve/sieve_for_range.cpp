#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 10006
using namespace std;

bool siv[MAX];
vector<ll>prime;

///O(n*lg(lg(n)))
void sieve(ll n)
{
    ll i,j;
    for(i=3; i*i<n; i+=2)
        if(!siv[i])
            for(j=i*i; j<n; j+=i+i)
                siv[j]=1;
    prime.pb(2);
    for(i=3; i<n; i+=2)
        if(!siv[i]) prime.pb(i);
}

void PrimeRange(ll low, ll high)
{
    ll start,i,j,limit;
    if(high<2LL) return;
    if(low<2LL)
        low=2LL;
    limit=sqrt(high+1);
    sieve(limit);
    bool mark[high-low+5]={0};

    for(i=0; i<prime.size(); i++)
    {
        start=max(prime[i]*prime[i], ((low+prime[i]-1)/prime[i])*prime[i]);

        for(j=start; j<=high; j+=prime[i])
            mark[j-low]=1;
    }


    for(i=low; i<=high; i++)
        if(!mark[i-low])
            cout << i << "  ";
}

int main()
{
    ll a,b;

    cin>>a>>b;
    PrimeRange(a,b);
    return 0;
}
