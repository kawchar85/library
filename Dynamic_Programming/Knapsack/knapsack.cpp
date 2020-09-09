#include<bits/stdc++.h>
using namespace std;
vector<int> cost,wt;
int dp[1005][35];

///O(i*remain)
int solve(int i, int remain)
{
    if(i==cost.size())
        return 0;
    if(~dp[i][remain])
        return dp[i][remain];
    int x=0,y;
    if(wt[i]<=remain)
        x=cost[i]+solve(i+1,remain-wt[i]);
    y=solve(i+1,remain);
    return dp[i][remain]=max(x,y);
}

int main()
{
    int i,t,n,p,w,g,ans;
    scanf("%d",&t);
    while(t--)
    {
        cost.clear();
        wt.clear();
        ans=0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d %d",&p,&w);
            cost.push_back(p);
            wt.push_back(w);
        }
        scanf("%d",&w);
        memset(dp,-1,sizeof dp);
        ans=solve(0,w);
        printf("%d\n",ans);
    }
    return 0;
}
