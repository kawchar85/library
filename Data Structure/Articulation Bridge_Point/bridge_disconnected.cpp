#include<bits/stdc++.h>
#define MAX 10004
#define pb push_back
using namespace std;

vector<int> adj[MAX];
vector<pair<int,int> >bridge;
bool visit[MAX];
int d[MAX],low[MAX],timer;

void clean()
{
    memset(visit,0,sizeof visit);
    bridge.clear();
    timer=0;
    for(int i=0; i<MAX; i++)
    {
        adj[i].clear();
    }
}

void FindBridge(int u,int par)
{
    visit[u]=1;
    low[u]=d[u]=++timer;
    int now,i,x,y;
    for(i=0; i<adj[u].size(); i++)
    {
        now=adj[u][i];
        if(now==par)
            continue;
        if(visit[now])
            low[u]=min(low[u],d[now]);
        else
        {
            FindBridge(now,u);
            low[u]=min(low[u],low[now]);
            if(d[u]<low[now])
            {
                x=min(now,u);
                y=max(now,u);
                bridge.pb({x,y});
            }
        }
    }
}

int main()
{
    int t,n,i,j,x,y,z,cs;
    scanf("%d",&t);
    for(cs=1; cs<=t; cs++)
    {
        clean();
        scanf(" %d",&n);
        for(i=0; i<n; i++)
        {
            scanf("%d %d",&x,&y);
            for(j=0; j<y; j++)
            {
                scanf("%d",&z);
                adj[x].pb(z);
                adj[z].pb(x);
            }
        }

        for(i=0; i<n; i++)
        {
            if(!visit[i])
                FindBridge(i,-1);
        }

        sort(bridge.begin(),bridge.end());
        printf("Case %d:\n%d critical links\n",cs,bridge.size());
        for(pair<int,int> p : bridge)
            printf("%d - %d\n",p.first,p.second);
    }
    return 0;
}
