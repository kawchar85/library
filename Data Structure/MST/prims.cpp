#include<bits/stdc++.h>
#define MAX 10001
#define pb push_back
#define PQ(x) x, vector< x >, greater< x >
#define xx pair<int,pair<int,int> >
using namespace std;

vector<int> adj[MAX],cost[MAX];
int visit[MAX];

void mst_init()
{
    for(int i=0; i<MAX; i++)
    {
        visit[i]=0;
    }
}

long long int MST(int x)
{
    int i,p,q,w,u,v,now;
    long long int total=0LL;
    vector< xx > ans;
    priority_queue<PQ(xx)> pq;


    visit[x]=1;
    for(i=0; i<adj[x].size(); i++)
    {
        now=adj[x][i];
        p=min(now,x);
        q=max(now,x);
        pq.push({cost[x][i],{p,q}});
    }

    while(!pq.empty())
    {
        w=pq.top().first;
        p=pq.top().second.first;
        q=pq.top().second.second;
        pq.pop();

        if(visit[p]&&visit[q]) //already connected
                continue;

        ans.pb({w,{p,q}});
        total+=w;
            
        x=visit[p]?q:p;//kunta new add hocche?
        visit[x]=1;
        for(i=0; i<adj[x].size(); i++)
        {
            now=adj[x][i];
            p=min(now,x);
            q=max(now,x);
            pq.push({cost[x][i],{p,q}});
        }
    }

    cout <<"Edge List in MST:\n";
    for (i = 0; i<ans.size(); i++)
    {
        w = ans[i].first;
        p = ans[i].second.first;
        q = ans[i].second.second;
        cout << "("<<p<<","<<q<<") -> " <<w <<"\n";
    }

    return total;
}

int main()
{
    int n,m,x,y,z,i,j;
    //mst_init();
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y>>z;
        adj[x].pb(y);
        adj[y].pb(x);
        cost[x].pb(z);
        cost[y].pb(z);
    }
    cout<<"Total Weight="<<MST(1)<<endl;
    return 0;
}
