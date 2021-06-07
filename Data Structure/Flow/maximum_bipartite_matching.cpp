#include<bits/stdc++.h>
using namespace std;

#define MAX 1003

typedef pair<int,int> pii;

int cap[MAX][MAX];
int par[MAX];
vector<int> adj[MAX];

void add_edge(int u, int v, int c=1)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
    cap[u][v]=c;
    cap[v][u]=0;
}

int BFS(int s, int t)
{
    memset(par, -1, sizeof par);
    par[s]=-2;
    queue< pii > q;
    q.push({s, INT_MAX});
    int cur,flow;

    while(!q.empty())
    {
        cur=q.front().first;
        flow=q.front().second;
        q.pop();

        for(int next : adj[cur])
        {
            if(par[next]==-1 && cap[cur][next])
            {
                par[next]=cur;
                flow=min(flow, cap[cur][next]);
                if(next==t)
                    return flow;
                q.push({next, flow});
            }
        }
    }
    return 0;
}

int maxFlow(int s, int t)
{
    int flow=0;
    int new_flow,cur,pre;

    while(1)
    {
        new_flow=BFS(s,t);
        if(new_flow==0) break;
        flow+=new_flow;
        cur=t;
        while(cur!=s)
        {
            pre=par[cur];
            cap[pre][cur]-=new_flow;
            cap[cur][pre]+=new_flow;
            cur=pre;
        }
    }
    return flow;
}
vector<int>A[2];
bool vis[MAX];
void Bipartite(int u=1, int f=0)
{
    A[f].push_back(u);
    vis[u]=1;
    for(auto v : adj[u])
    {
        if(vis[v])
            continue;
        Bipartite(v, f^1);
    }
}
int maximumBipartiteMatching(int n)
{
    int s=n+1;
    int t=n+2;
    Bipartite();
    for(auto v : A[0])
        add_edge(s,v);
    for(auto v : A[1])
        add_edge(v,t);
    return maxFlow(s,t);
}
int main()
{
    int i,j,n,m,x,y,c,s,t;

    cin>>n>>m;
    for(i=0; i<m; ++i)
    {
        cin>>x>>y;
        add_edge(x,y);
    }
    x=maximumBipartiteMatching(n);
    cout<<x<<endl;
    return 0;
}
