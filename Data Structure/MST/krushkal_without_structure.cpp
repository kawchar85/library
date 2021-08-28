#include<bits/stdc++.h>
#define pb push_back
#define xx pair< int, pair< int, int > >
#define PQ(x) x, vector< x >, greater< x >
#define MAX 10004
using namespace std;

vector<int>adj[MAX],cost[MAX],tree[MAX];
int par[MAX];
priority_queue< PQ(xx) >pq;

void init()
{
    for(int i=0; i<MAX; i++)
    {
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

int MST(int n)
{
    int w,p,q,u,v,i,j,total=0;
    for(i=1; i<=n; i++){
        for(j=0; j<adj[i].size(); j++){

            p=min(i,adj[i][j]);
            q=max(i,adj[i][j]);
            pq.push({cost[i][j],{p,q}}); //weight,u,v
        }
    }
    

    while(!pq.empty())
    {
        w=pq.top().first;
        p=pq.top().second.first;
        q=pq.top().second.second;
        pq.pop();


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

int main()
{
    int t,cs,i,n,m,x,y,z,ans;
    
    cin>>t;
    for(cs=1; cs<=t; cs++)
    {
        init();
        cin>>n>>m;
        for(i=0; i<m; i++)
        {
            cin>>x>>y>>z;
            adj[x].pb(y);
            adj[y].pb(x);
            cost[x].pb(z);
            cost[y].pb(z);
        }
        ans=MST(n);
        printf("Case %d: %d\n",cs,ans);
    }
    return 0;
}
