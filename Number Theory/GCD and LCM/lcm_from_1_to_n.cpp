#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MAX 100000006
using namespace std;

bool siv[MAX];
vector<ll>prime;

///O(n*lg(lg(n)))
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

ll LCM_1_n(ll n)
{
    ll lcm=1,p,i;
    for(i=0; i<prime.size()&&prime[i]<=n; i++)
    {
        p=prime[i];
        while(p*prime[i]<=n)
            p*=prime[i];
        lcm*=p;
    }
    return lcm;
}

int main()
{
    sieve();
    ll n;
    cin>>n;
    cout<<LCM_1_n(n);
    return 0;
}
