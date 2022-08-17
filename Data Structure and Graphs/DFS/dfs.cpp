#include<bits/stdc++.h>
#define MAX 1000
using namespace std;

vector<int> adj[MAX];
bool vis[MAX];
int child[MAX];

///O(V+E)
void DFS(int n)
{
    vis[n]=1;
    for(auto x: adj[n])
    {
        if(vis[x]) continue;
        DFS(x);
    }
}


int DFS2(int u)
{
    vis[u]=1;
    int cnt=0;
    for(auto x : adj[u])
    {
        if(vis[x]) continue;
        cnt+=DFS2(x);
    }
    child[u]=cnt;
    return cnt+1;
}

int main()
{
    int n,m,x,y,i,p,q;
    cin>>n>>m;
    for(i=0;i<m;i++)
    {
        cin>>p>>q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    DFS(1);
}
