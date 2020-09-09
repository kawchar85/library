/***
  memory O(Max_Cap)
*/
#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
#define INF 1e17
#define ll long long 
#define endl "\n"

ll dp[MAX];
vector<ll> wt,profit;

ll get_profit(ll cap, ll n)
{
    ll i,j,ans=0LL;

    for(i=0; i<n; i++)
    {
        for(j=cap; j>0; j--)
        {
            if(wt[i]<=j)
                dp[j]=max(dp[j], dp[j-wt[i]]+profit[i]);
        }
    }

    return dp[cap];
}
int main()
{   
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll i,j,n;
    ll cap,sum=0,v,w,x;
    cin>>n>>cap;
    for(i=0; i<n; i++)
    {
        cin>>x;
        wt.push_back(x);
    }
    for(i=0; i<n; i++)
    {
        cin>>x;
        profit.push_back(x);
    }
    cout<<get_profit(cap,n)<<endl;
    return 0;
}
