/***
  knapsack with high capacity

  https://atcoder.jp/contests/dp/tasks/dp_e
  
*/
#include <bits/stdc++.h>
using namespace std;
#define maxN 101
#define maxV 1003
#define INF 1e17
#define ll long long 
#define endl "\n"

ll dp[maxN*maxV+5];
vector<ll> wt,profit;

ll get_profit(ll cap, ll n)
{
    ll i,j,ans=0LL;

    for(i=0; i<=maxN*maxV; i++)
        dp[i]=INF;
    dp[0]=0;

    for(i=0; i<n; i++)
    {
        for(j=ans+profit[i]; j>=profit[i]; j--)
        {
            if(dp[j-profit[i]]+wt[i]<=cap)
            {
                dp[j]=min(dp[j], dp[j-profit[i]]+wt[i]);
                ans=max(ans,j);
            }
        }
    }

    return ans;
}
int main()
{   
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int i,j,n;
    ll cap,sum=0,v,w;
    cin>>n>>cap;
    for(i=0; i<n; i++)
    {
        cin>>w>>v;
        wt.push_back(w);
        profit.push_back(v);
    }
    cout<<get_profit(cap,n)<<endl;
    return 0;
}
