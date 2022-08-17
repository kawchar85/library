//https://lightoj.com/problem/internet-bandwidth

#include<bits/stdc++.h>
using namespace std;

#define MAX 105

typedef pair<int,int> pii;

int cap[MAX][MAX];
int par[MAX];
vector<int> adj[MAX];

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

//O(V*E*E)
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

void init()
{
    memset(cap, 0, sizeof cap);
    for(int i=0; i<MAX; i++)
        adj[i].clear();
}

int main()
{
    int i,j,n,m,x,y,c,s,t;
    int cs,T;
    cin>>T;
    for(cs=1; cs<=T; cs++)
    {
        init();
        cin>>n;
        cin>>s>>t>>m;
        for(i=0; i<m; ++i)
        {
            cin>>x>>y>>c;
            adj[x].push_back(y);
            adj[y].push_back(x);
            cap[x][y]+=c;
            cap[y][x]+=c;
        }
        x=maxFlow(s,t);
        cout<<"Case "<<cs<<": "<<x<<endl;
    }
    
    
    return 0;
}
