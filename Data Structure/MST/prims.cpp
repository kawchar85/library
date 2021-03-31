#include<bits/stdc++.h>
#define pb push_back
#define xx pair< int, pair< int, int > >
#define PQ(x) x, vector< x >, greater< x >
#define MAX 10004
#define in(x) scanf("%d",&x)
using namespace std;

vector<int>adj[MAX],cost[MAX],tree[MAX];
bool visit[MAX];
int par[MAX];
priority_queue< PQ(xx) >pq;

void init()
{
    for(int i=0; i<MAX; i++)
    {
        visit[i]=0;
        par[i]=i;
        cost[i].clear();
        tree[i].clear();
        adj[i].clear();
    }
}

int find_par(int x)
{
    return par[x]==x?x:par[x]=find_par(par[x]);
}

int MST(int n,int Max)
{
    int w,p,q,u,v,i,j,total=0;
    for(i=1; i<=n; i++)
    for(j=0; j<adj[i].size(); j++)
    {
        p=min(i,adj[i][j]);
        q=max(i,adj[i][j]);
        pq.push({cost[i][j],{p,q}});
    }

    while(!pq.empty())
    {
        w=pq.top().first;
        p=pq.top().second.first;
        q=pq.top().second.second;
        pq.pop();
        if(w>=Max)
            break;
        u=find_par(p);
        v=find_par(q);
        if(u==v) continue;
        par[u]=v;
        total+=w;
        tree[p].pb(q);
        tree[q].pb(p);
    }
    while(!pq.empty())
        pq.pop();
    return total;
}

void DFS(int u)
{
    visit[u]=1;
    for(int v: tree[u])
        if(!visit[v])
            DFS(v);
}

int main()
{
    int t,cs,i,j,n,m,a,x,y,z,ans,cnt;
    in(t);
    for(cs=1; cs<=t; cs++)
    {
        init();
        in(n);in(m);in(a);
        for(i=0; i<m; i++)
        {
            in(x);in(y);in(z);
            adj[x].pb(y);
            adj[y].pb(x);
            cost[x].pb(z);
            cost[y].pb(z);
        }
        ans=MST(n,a);
        cnt=0; ///counting total forest
        for(i=1; i<=n; i++)
        {
            if(!visit[i])
            {
                cnt++;
                DFS(i);
            }
        }
        ans+=a*cnt;
        printf("Case %d: %d %d\n",cs,ans,cnt);
    }
    return 0;
}

/**
17 13 63
6 13 19
15 7 20
8 5 31
8 11 36
3 13 6
12 3 29
14 1 37
15 12 9
7 3 47
1 17 42
14 3 60
12 9 16
10 5 46
*/
