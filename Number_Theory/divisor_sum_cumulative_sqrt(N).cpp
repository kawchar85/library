#include<bits/stdc++.h>
using namespace std;
#define ll long long

//O(sqrt(n))
ll CSOD(ll n)
{
    ll i,j,ans=0LL;
    for(i=1; i*i<=n; i++)
    {
        j=n/i;
        ans+=(i+j)*(j-i+1)/2LL;
        ans+=i*(j-i);
    }
    return ans;
}
ll CSOD(ll l, ll r)
{
    return CSOD(r)-CSOD(l-1);
}

//another way
ll get(ll n){
    return (n*(n+1))/2LL;
}
//O(sqrt(N)
ll SOD_1_N(ll n)
{
    ll r,sum=0;
    for(ll i=1; i<=n; i++)
    {
        r=n/(n/i);
        sum+=(get(r)-get(i-1))*(n/i);
        i=r;
    }
    return sum;
}

ll SOD(ll n)
{
    return CSOD(n)-CSOD(n-1);
}
int main()
{
    int n;
    cin>>n;
    cout<<SOD(n)<<endl;
}

