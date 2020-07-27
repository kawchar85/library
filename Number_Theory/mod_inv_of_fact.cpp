#include<bits/stdc++.h>
#define MAX 10000001
#define ll long long
#define MOD 1000000007
using namespace std;

ll fact[MAX],inv[MAX],invFact[MAX];

void Cal()
{
    ll i;
    fact[0]=1;
    for(i=1; i<MAX; ++i)
        fact[i]=i*fact[i-1]%MOD;
    inv[1]=1;
    for(i=2; i<MAX; ++i)
        inv[i]=((MOD-MOD/i)*inv[MOD%i])%MOD;
    invFact[0]=1;
    for(i=1; i<MAX; ++i)
        invFact[i]=(invFact[i-1]*inv[i])%MOD;
}
int main()
{
    Cal();
    ll n;
    cout<<"Enter number:\n";
    while(cin>>n)
        cout<<invFact[n]<<endl;
}
