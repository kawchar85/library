/**
    ->Shortest paths from starting node to all nodes
    -> Negative edge ~ won't work (infinite loop!!)
*/
#include<bits/stdc++.h>
#define in(x) scanf("%d",&x)
#define sz 105
#define INF 1<<28
#define pb push_back
using namespace std;
struct Edge{
    int to,w;
    Edge() {}
    Edge(int x,int y)
    {
        to=x;w=y;
    }
};
bool operator<(Edge a,Edge b)
{
    return b.w<a.w;
}

vector<Edge> adj[sz];
int cost[sz];
void init()
{
    for(int i=0; i<sz; i++)
    {
        cost[i]=INF;
        adj[i].clear();
    }
}
///O(E+V*LogV)
int dijkstra(int s, int d)
{
    cost[s]=0;
    int w,n,i,test;
    priority_queue<Edge>q;
    q.push(Edge(s,0));
    while(!q.empty())
    {
        w=q.top().w;
        n=q.top().to;
        q.pop();

        if(cost[n] < w) continue;

        for(auto v: adj[n])
        {
            test=w+v.w;
            if(test<cost[v.to])
            {
                cost[v.to]=test;
                q.push(Edge(v.to,test));
            }
        }
    }
    return cost[d];
}

int main()
{
    int t,cs,i,n,m,x,y,z,ans;
    in(t);
    for(cs=1; cs<=t; cs++)
    {
        init();
        in(n);in(m);
        for(i=0; i<m; i++)
        {
            in(x);in(y);in(z);
            adj[x].pb(Edge(y,z));
            adj[y].pb(Edge(x,z));
        }
        cout<<"input done..\n";
        ans=dijkstra(1,n);
        printf("Case %d: ",cs);
        if(ans==INF)
            puts("Impossible");
        else
            printf("%d\n",ans);
    }
    return 0;
}
