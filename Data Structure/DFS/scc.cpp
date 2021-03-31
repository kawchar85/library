#include<bits/stdc++.h>
#define SZ 100
#define pb push_back

using namespace std;

bool vis[SZ];
int Time,dis[SZ],fin[SZ];
vector<int>adj[SZ],adjR[SZ],ans;
vector< pair<int,int> >order;

void DFS(int n)
{
    vis[n]=1;
    dis[n]=++Time;
    for(auto x : adj[n])
    {
        if(vis[x]) continue;
        DFS(x);
    }
    fin[n]=++Time;
    order.push_back({fin[n],n});
}

void DFS2(int n)
{
    vis[n]=1;
    ans.pb(n);
    for(auto x: adjR[n])
    {
        if(vis[x]) continue;
        DFS2(x);
    }
}


int main()
{
    int n,m,x,y,i;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].pb(y);
        adjR[y].pb(x);
    }
    memset(vis,0,sizeof vis);
    for(i=0; i<n; i++)
        if(!vis[i])
            DFS(i);
    sort(order.rbegin(), order.rend());
    memset(vis,0,sizeof vis);
    Time=0;
    for(auto k : order)
    {
        if(!vis[k.second])
        {
            ans.clear();
            DFS2(k.second);
            cout<<"{ ";
            for(auto K : ans)
                cout<<K<<" ";
            cout<<"},";
        }
    }
    return 0;
}
/**
13 14
0 1
0 4
8 10
1 3
7 9
4 3
8 7
11 2
10 12
0 5
3 6
5 6
7 12
3 5
*/

