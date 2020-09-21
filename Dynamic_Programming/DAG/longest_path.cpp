/**
    Find the length of the longest directed
    path in G. Here, the length of a 
    directed path is the number of edges in it.
*/
#include<bits/stdc++.h>
#define MAX 100005
#define endl "\n"
using namespace std;

vector<int> adj[MAX];
int dp[MAX];

int DFS(int u)
{
    if(~dp[u]) return dp[u];
    int mx=0;
    for(auto v: adj[u])
    {
        mx=max(mx, 1+DFS(v));
    }
    return dp[u]=mx;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,m,i,ans=0;
    cin>>n>>m;

    for(i=0; i<m; ++i)
    {
        int xx,yy;
        cin>>xx>>yy;
        adj[xx].push_back(yy);
        //adj[yy].push_back(xx);
    }

    memset(dp, -1, sizeof dp);
    for(i=1; i<=n; i++)
        ans = max(ans, DFS(i));
    cout<<ans<<endl;
    return 0;
}
