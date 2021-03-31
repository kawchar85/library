//https://codeforces.com/contest/412/problem/D

#include<bits/stdc++.h>
#define SZ 30004
#define pb push_back

using namespace std;

bool vis[SZ];
vector<int>adj[SZ],topo_order;

void DFS(int n)
{
    vis[n]=1;
    for(auto x : adj[n])
    {
        if(vis[x]) continue;
        DFS(x);
    }
    topo_order.pb(n);
}

int main()
{
    int n,m,x,y,i;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].pb(y);
    }
    for(i=1; i<=n; i++)
        if(!vis[i])
            DFS(i);
    for(int x : topo_order)
        cout<<x<<" ";
    return 0;
}
 
