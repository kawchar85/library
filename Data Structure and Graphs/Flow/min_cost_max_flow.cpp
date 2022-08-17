#include<bits/stdc++.h>
#define pb push_back
#define MAX 1001
#define inf 1<<28
using namespace std;

vector<int> adj[MAX];
int cost[MAX][MAX];
int capacity[MAX][MAX];

int d[MAX];
bool inq[MAX];
int p[MAX];

void add_edge(int u, int v, int cap, int c){
    //u--->v : directed , capacity cap, cost c
    adj[u].push_back(v);
    adj[v].push_back(u);
    cost[u][v]=c;
    cost[v][u]=-c;
    capacity[u][v]=cap;
    capacity[v][u]=0;
}

void shortest_paths(int n, int s)
{
    for(int i=1; i<=n; i++)
    {
        d[i]=inf;
        inq[i]=0;
        p[i]=-1;
    }

    queue<int> q;
    d[s] = 0;
    q.push(s);
    inq[s] = true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for(int v : adj[u])
        {
            if(capacity[u][v] > 0 && d[v] > d[u] + cost[u][v])
            {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if(!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

//O(V*V*E*E)
int min_cost_flow(int N, int s, int t, int maxFlow=inf)
{
    int flow = 0;
    int minCost = 0;
    int cur,f;

    while(flow < maxFlow)
    {
        shortest_paths(N, s);
        if(d[t] == inf) //no new path
            break;

        // find max flow on that path
        f = maxFlow - flow;
        cur = t;
        while(cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        minCost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    //cout<<maxFlow<<" --- "<<flow<<endl;
    return minCost;
}

int main()
{
    int i,x,y,cap,c,n,m;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y>>cap>>c;
        add_edge(x,y,cap,c);
    }
    cout<<min_cost_flow(n,1,n)<<endl;
    //cout<<min_cost_flow(n,1,n, 10)<<endl;
}

/*
4 5
1 2 10 10
1 3 10 5
3 2 20 1
2 4 20 5
3 4 20 10
*/
