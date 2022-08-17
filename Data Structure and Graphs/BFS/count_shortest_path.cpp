#include<stdio.h>
#include<bits/stdc++.h>
#define MAX 100001
using namespace std;

vector<int> adj[MAX];
bool vis[MAX];
int lvl[MAX];
int cnt[MAX];
/**
    cnt[i]--> the number of way to go from s to i with shortest path
*/

void BFS(int s)
{
    queue<int>q;
    q.push(s);
    vis[s]=1;
    cnt[s]=1;
    lvl[s]=0;

    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        for(auto now : adj[k])
        {
            if(!vis[now])
            {
                q.push(now);
                vis[now]=1;
                lvl[now]=1+lvl[k];
                cnt[now]+=cnt[k];
            }
            else
            {
                if(lvl[now]==1+lvl[k])
                    cnt[now]+=cnt[k];
            }
        }
    }

}

int main()
{
    int n,m,i,j,p,q;

    cin>>n>>m;
    for(i=0;i<m;i++)
    {
        cin>>p>>q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    BFS(1);
    for(i=1; i<=n; i++)
        cout<<i<<" "<<cnt[i]<<endl;
}
