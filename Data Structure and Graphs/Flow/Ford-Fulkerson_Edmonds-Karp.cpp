/**
	Directed:
	cap[x][y]=c;
	cap[y][x]=0;

	Undirected:
	cap[x][y]=c;
	cap[y][x]=c;

	Multiple Edge:
	cap[x][y]+=c;
*/

#include<bits/stdc++.h>
using namespace std;

#define MAX 1003

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

int main()
{
    int i,j,n,m,x,y,c,s,t;

    cin>>n>>m;
    cin>>s>>t;
    for(i=0; i<m; ++i)
    {
        cin>>x>>y>>c;
        adj[x].push_back(y);
        adj[y].push_back(x);
        cap[x][y]=c;
        cap[y][x]=0;
    }
    x=maxFlow(s,t);
    cout<<x<<endl;
    return 0;
}

/*
4 5
1 4
1 2 20
1 3 10
2 3 5
2 4 10
3 4 20

*/
