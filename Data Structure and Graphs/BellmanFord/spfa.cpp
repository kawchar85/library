//Shortest Path Faster Algorithm
//SPFA is a improvement of the Bellman-Ford algorithm
#include<bits/stdc++.h>
#define pb push_back
#define MAX 1001
#define inf 1<<28
using namespace std;

vector< pair<int,int> > adj[MAX];
int d[MAX];
int cnt[MAX];
bool inqueue[MAX];

bool spfa(int n, int s)
{
    for(int i=1; i<=n; i++)
    {
        d[i]=inf;
        cnt[i]=0;//relaxation count
        inqueue[i]=0;
    }

    queue<int> q;
    d[s] = 0;
    q.push(s);
    inqueue[s] = true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        for(auto edge : adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            if(d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                if(!inqueue[v])
                {
                    q.push(v);
                    inqueue[v] = true;
                    cnt[v]++;
                    if(cnt[v] > n)
                        return false;  // negative cycle
                }
            }
        }
    }
    return true;
}
int main()
{
    int i,x,y,z,n,m;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y>>z;
        adj[x].push_back({y,z});
    }
    if(spfa(n,1))
        cout<<"1 to "<<n<<" : "<<d[n]<<endl;
    else
        cout<<"negative cycle!";
}

/*
5 6
1 2 2
2 3 3
3 4 2
4 5 -2
1 5 100
4 2 -10
*/
