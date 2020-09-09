#include<bits/stdc++.h>
#define pb push_back
#define MOD 100000007
using namespace std;

vector<int>coin,mx;
int dp[55][1005][30];
int solve(int i,int taka,int avail)
{
    if(avail<0)
        return 0;
    if(taka==0)
        return 1;
    if(taka<0 || i==coin.size())
        return 0;
    if(dp[i][taka][avail]!=-1)
        return (dp[i][taka][avail]);
    int x=(solve(i,taka-coin[i],avail-1))%MOD;
    int y=(solve(i+1,taka,mx[i+1]))%MOD;
    dp[i][taka][avail]=(x+y)%MOD;
    return dp[i][taka][avail];
}

int main()
{
    int t,cs,n,k,i,x;
    scanf("%d",&t);
    for(cs=1; cs<=t; cs++)
    {
        coin.clear();
        mx.clear();
        memset(dp,-1,sizeof dp);
        scanf("%d %d",&n,&k);
        for(i=0; i<n; i++)
        {
            scanf("%d",&x);
            coin.pb(x);
        }
        for(i=0; i<n; i++)
        {
            scanf("%d",&x);
            mx.pb(x);
        }
        printf("Case %d: %d\n",cs,solve(0,k,mx[0]));
    }
    return 0;
}
