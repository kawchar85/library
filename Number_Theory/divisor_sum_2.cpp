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

