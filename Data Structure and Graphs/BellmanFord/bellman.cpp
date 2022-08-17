/**
    ->Shortest paths from starting node to all nodes
    -> Negative edge ~ No problem
    -> Negative cycle ~ No shortest path

    ->a possible way to make the algorithm 
     more efﬁcient is to stop the algorithm
     if no distance can be reduced during 
     a round.
*/
#include<bits/stdc++.h>
#define pb push_back
#define MAX 1001
#define inf 1<<28
using namespace std;

struct Edge{
    int u,v,w;
    Edge() {}
    Edge(int x,int y,int z)
    {
        u=x; v=y; w=z;
    }
};
vector<Edge>E;
int dis[MAX],n,m;

//O(V*E)
int BellmanFord(int s)
{
    int i,j;
    Edge now;
    for(i=0; i<=n; i++)
        dis[i]=inf; ///initialize
    dis[s]=0;

    for(i=1; i<n; i++) ///n-1 times relaxation
    {
        for(j=0; j<E.size(); j++) ///relaxation of all edge
        {
            now=E[j];
            if(dis[now.u]+now.w<dis[now.v])
            {
                dis[now.v]=dis[now.u]+now.w;
            }
        }
    }

    ///negative cycle checking
    for(j=0; j<E.size(); j++)
    {
        now=E[j];
        if(dis[now.u]+now.w<dis[now.v])
        {
            cout<<"Negative cycle present\n";
            break;
        }
    }

    ///print
    for(i=1; i<=n; i++)
    {
        cout<<i<<"\t\t"<<dis[i]<<"\n";
    }
}
int main()
{
    int i,x,y,z;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y>>z;
        E.pb(Edge(x,y,z));
       /// E.pb(Edge(y,x,z));
    }
    BellmanFord(1);
}
