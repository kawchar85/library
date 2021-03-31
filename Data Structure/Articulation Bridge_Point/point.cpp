#include<iostream>
#include<vector>
#define MAX 10000
#define pb push_back
using namespace std;

vector<int>adj[MAX];
bool arti_point[MAX],visited[MAX];
int d[MAX],low[MAX],time=0;

void findArticulationPoint(int u, int par)
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
            findArticulationPoint(now,u);
            low[u]=min(low[u],low[now]);
            if(d[u]<=low[now] && par!=-1)
                arti_point[u]=1;
            child++;
        }
        if(child>1 && par==-1)
            arti_point[u]=1;
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

    findArticulationPoint(0,-1);

    cout<<"Node\td[i]\tlow[i]\n";
    for(i=0; i<n; i++)
        cout<<i<<"\t"<<d[i]<<"\t"<<low[i]<<endl;
    cout<<"Articulation Point List:\n";
    for(i=0; i<n; i++)
        if(arti_point[i])
            cout<<i<<" ";
    return 0;
}
