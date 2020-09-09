/***
  knapsack with high capacity

  https://atcoder.jp/contests/dp/tasks/dp_e
  
*/
#include <bits/stdc++.h>
using namespace std;
#define maxN 1000
#define maxV 1003
#define INF 1e17
#define ll long long 
#define endl "\n"

ll dp[maxN*maxV+5];
vector<ll> wt,profit;

int main()
{   
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int i,j,n,ans=0;
    for(i=1; i<=maxN*maxV; i++) dp[i] = INF;
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
    for(i=0; i<n; i++)
    {
        w=wt[i];
        v=profit[i];
        sum+=v;
        for(j=sum; j>=v; j--)
        {
            dp[j] = min(dp[j], w+dp[j-v]);
            if(dp[j]<=cap) ans=max(ans, j);
        }
    }
    cout<<ans<<endl;
    return 0;
}
