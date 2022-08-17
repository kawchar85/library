/**
    go (0,0) to (n-1, m-1)
    with min cost.
    you can go Right or Down. 
*/
#include<bits/stdc++.h>
using namespace std;
#define INF 100000000
#define MAX 1000

#define ERROR 0

int cost[MAX][MAX],n,m;
int dp[MAX][MAX];

int solve(int i, int j)
{
    if(i>=n || j>=m) return INF;
    if(i+1==n && j+1==m) return cost[i][j];
    if(~dp[i][j]) return dp[i][j];
    return dp[i][j]=cost[i][j]+min(solve(i+1,j),solve(i,j+1));
}
int32_t main()
{
    cin>>n>>m;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>>cost[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    cout<<solve(0,0)<<endl;
    return 0;
}
