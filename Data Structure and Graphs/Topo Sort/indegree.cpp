#include<bits/stdc++.h>
#define MAX 1001
#define pb push_back
using namespace std;
typedef vector<int> vi;

vi adj[MAX],ans;
int indeg[MAX];
bool vis[MAX];

void topo_sort(int n)
{
    int i,k;
    queue<int>q;
    for(i=0; i<n; i++)
    {
        if(!indeg[i])
        {
            q.push(i);
            vis[i]=1;
        }
    }
    while(!q.empty())
    {
        k=q.front();
        ans.pb(k);
        q.pop();
        for(auto now : adj[k])
        {
            if(!vis[now])
            {
                indeg[now]--;
                if(!indeg[now])
                {
                    q.push(now);
                    vis[now]=1;
                }
            }
        }
    }
}

int main()
{
    int i,n,m,x,y;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        indeg[y]++;
        adj[x].pb(y);
    }
    topo_sort(n);
    cout << "One possible ordering: ";
    for(auto k : ans)
        cout<<k<<" ";
}
