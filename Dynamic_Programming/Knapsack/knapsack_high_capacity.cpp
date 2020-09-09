/***
  knapsack with high capacity

  https://atcoder.jp/contests/dp/tasks/dp_e
  
*/
#include <bits/stdc++.h>
using namespace std;
#define maxN 100
#define maxV 1000
#define INF 1e17
#define ll long long 
#define endl "\n"

ll dp[maxN*maxV+5];

int main()
{   
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int i,j,n,ans=0;
    for(i=1; i<=maxN*maxV; i++) dp[i] = INF;
    ll cap,sum=0,v,w;
    cin>>n>>cap;
    for(i=0; i<n; i++)
    {
        cin>>w>>v;
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
