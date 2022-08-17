#include<bits/stdc++.h>
using namespace std;
#define ll long long

/**
 Cumulative SOD of all the actual divisors
 (without 1 & n)
*/
ll CSOD(ll n)
{
    ll i,j,ans=0LL;
    for(i=2; i*i<=n; i++)
    {
        j=n/i;
        ans+=(i+j)*(j-i+1)/2LL;
        ans+=i*(j-i);
    }
    return ans;
}
int main()
{
    int n;
    cin>>n;
    cout<<CSOD(n)<<endl;
}

