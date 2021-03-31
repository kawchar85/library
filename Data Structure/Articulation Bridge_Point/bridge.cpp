#include<iostream>
#include<vector>
#define MAX 10000
#define pb push_back
using namespace std;

vector<int>adj[MAX];
vector<pair<int,int> >arti_bridge;
bool visited[MAX];
int d[MAX],low[MAX],time=0;

void findArticulationBridge(int u, int par)
{
    low[u]=d[u]=++time;
    visited[u]=1;
    int child=0,i,now;
    for(i=0; i<adj[u].size(); i++)
    {
        now=adj[u][i];
        if(now==par)
            continue;
        if(visited[now])
            low[u]=min(low[u],d[now]);
        else
        {
            findArticulationBridge(now,u);
            low[u]=min(low[u],low[now]);
            if(d[u]<low[now])
                arti_bridge.pb({u,now});
        }
    }
}

int main()
{
    int n,m,x,y,i,j,k;
    cin>>n>>m;

    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }

    findArticulationBridge(0,-1);

    cout<<"Node\td[i]\tlow[i]\n";
    for(i=0; i<n; i++)
        cout<<i<<"\t"<<d[i]<<"\t"<<low[i]<<endl;
    cout<<"Articulation Bridge List:"<<arti_bridge.size()<<"\n";
    for(pair<int,int> k : arti_bridge)
        cout<<k.first<<"-"<<k.second<<endl;
    return 0;
}
