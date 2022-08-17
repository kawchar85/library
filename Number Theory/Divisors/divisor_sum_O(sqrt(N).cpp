#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll SOD(ll n)
{
    ll i,j,ans=0LL;
    for(i=1; i*i<=n; i++)
    {
        if(i*i==n) ans+=i;
        else if(n%i==0)
        {
            ans+=i;
            ans+=(n/i);
        }
    }
    return ans;
}
int main()
{
    int n;
    cin>>n;
    cout<<SOD(n)<<endl;
}

