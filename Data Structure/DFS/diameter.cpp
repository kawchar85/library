#include<bits/stdc++.h>
#define N 3005
using namespace std;

int n;
int ans;
vector<int>adj[N];

int dfs(int node,int parent)
{
    int mx1=0,mx2=0;
    for(int u: adj[node])
    {
        if(u!=parent)
        {
            int now=dfs(u,node)+1;
            if(now>=mx1)
            {
                mx2=mx1;
                mx1=now;
            }
            else if(now>=mx2)
            {
                mx2=now;
            }
        }
    }
    ans=max(ans,mx1+mx2);
    return mx1;
}
int main()
{
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,0);
    cout<<ans;
}

