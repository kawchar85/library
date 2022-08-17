/*
https://vjudge.net/problem/LightOJ-1155
*/

#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
#define endl "\n"
typedef long long ll;

struct FlowEdge{
    int v,u;
    ll cap,flow=0LL;
    FlowEdge(int vv, int uu, ll c)
    {
        v=vv; u=uu; cap=c;
        //Edge v to u
    }
};

//O(V*V*E)
struct Dinic{
    const ll flow_inf=LLONG_MAX;
    vector<FlowEdge> edges;
    vector< vector<int> > adj;
    vector<int> level, par;
    int n,m=0,s,t;
    queue<int> q;

    Dinic(int nn, int ss, int tt)
    {
        n=nn+3; s=ss; t=tt;
        adj.resize(n+5);
        par.resize(n+5);
        level.resize(n+5);
    }

    void add_edge(int v, int u, ll cap)
    {
        edges.emplace_back(v,u,cap);
        edges.emplace_back(u,v,0LL);//Ulto edge
        adj[v].push_back(m);
        adj[u].push_back(m+1);
        m+=2;
    }

    bool bfs()
    {
        while(!q.empty())
        {
            int v=q.front();
            q.pop();
            for(int id : adj[v])
            {
                if(level[edges[id].u]!=-1 || edges[id].cap - edges[id].flow < 1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t]!=-1;
    }

    ll dfs(int v, ll pushed)
    {
        if(pushed == 0LL)
            return 0LL;
        if(v == t)
            return pushed;
        for(int& cid = par[v]; cid < (int)adj[v].size(); cid++)
        {
            int id = adj[v][cid];
            int u = edges[id].u;
            if(level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            ll tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if(tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0LL;
    }

    ll maxFlow() 
    {
        ll f = 0LL,pushed;
        while(1) 
        {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if(!bfs())
                break;
            fill(par.begin(), par.end(), 0);
            while(pushed = dfs(s, flow_inf)){
                f += pushed;
            }
        }
        return f;
    }

};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T,cs;
    int n,s,t,m,i,u,v,tot;
    ll c;

    cin>>T;
    for(cs=1; cs<=T; cs++)
    {
        cin>>n;
        s=0;
        tot=2*n+1;
        Dinic dinic(tot,s,tot);
        for(i=1; i<=n; i++)
        {
            cin>>c;
            dinic.add_edge(i, i+n, c);
        }
        cin>>m;
        for(i=0; i<m; i++)
        {
            cin>>u>>v>>c;
            dinic.add_edge(u+n, v, c);
        }
        
        cin>>s>>t;
        //make Super surce=0
        for(i=0; i<s; i++)
        {
            cin>>u;
            dinic.add_edge(0, u, (ll)1e6);
        }
        //super sink=tot
        for(i=0; i<t; i++)
        {
            cin>>u;
            dinic.add_edge(u+n, tot, (ll)1e6);
        }
        cout<<"Case "<<cs<<": "<<dinic.maxFlow()<<endl;
    }

}
