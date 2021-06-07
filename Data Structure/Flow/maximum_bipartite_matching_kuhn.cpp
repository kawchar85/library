#include<bits/stdc++.h>
using namespace std;

#define MAX 1003

vector<int> adj[MAX];
bool used[MAX];
int matchR[MAX];

bool try_kuhn(int v)
{
    if(used[v]) return 0;
    used[v] = true;
    for(int to : adj[v])
    {
        if(matchR[to] == -1 || try_kuhn(matchR[to]))
        {
            matchR[to] = v;
            return 1;
        }
    }
    return 0;
}

void maxBPM(int n)
{
    memset(matchR, -1, sizeof matchR);
    int total=0;
    for(int i=1; i<=n; i++)
    {
        memset(used, 0, sizeof used);
        total+=try_kuhn(i);
    }
    cout<<total<<endl;
    for(int i=1; i<=n; i++)
    {
        if(matchR[i] != -1)
            cout<<matchR[i]<<" "<<i<<endl;
    }
}
int main()
{
    int i,j,n,m,x,y;
    cin>>n>>m;
    for(i=0; i<m; ++i)
    {
        cin>>x>>y;
        adj[x].push_back(y);
    }
    maxBPM(n);
    return 0;
}
/*
5 5
1 4
1 5
2 5
3 4
3 5
*/
