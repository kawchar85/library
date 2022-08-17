#include<stdio.h>
#include<bits/stdc++.h>
#define MAX 100001
using namespace std;

vector<int> adj[MAX];
bool vis[MAX];

///O(V+E)
int BFS(int x, int y)
{
    queue<int>q;
    int origin[MAX],k;
    q.push(x);
    vis[x]=1;

    origin[x]=-1;
    while(!q.empty())
    {
        k=q.front();
        q.pop();
        for(auto now : adj[k])
        {
            if(!vis[now])
            {
                q.push(now);
                vis[now]=1;
                origin[now]=k;
            }
        }
    }

    int cnt=0;
    k=origin[y];
    while(k!=-1)
    {
        cnt++;
        k=origin[k];
    }
    return cnt;
}

int main()
{
    int n,m,x,y,i,j,p,q;

    cin>>n>>m;
    cin>>x>>y;
    for(i=0;i<m;i++)
    {
        cin>>p>>q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    cout<<BFS(x,y);
}
