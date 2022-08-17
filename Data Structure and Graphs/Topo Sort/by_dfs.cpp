#include<bits/stdc++.h>
#define MAX 100
#define pb push_back

using namespace std;

bool vis[MAX];
int Time,in[MAX],out[MAX];
vector<int>adj[MAX];

void DFS(int n)
{
    vis[n]=1;
    in[n]=++Time;
    for(auto x : adj[n])
    {
        if(vis[x]) continue;
        DFS(x);
    }
    out[n]=++Time;
}

int main()
{
    int n,m,x,y,i;
    cin>>n>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].pb(y);
    }

    for(i=1; i<=n; i++)
        if(!vis[i])
            DFS(i);
    vector< pair <int, int> > seq;
    for (int i = 1; i<=n; i++)
        seq.pb({out[i],i});
    sort(seq.rbegin(), seq.rend());
    cout<<"\nOne possible ordering: ";
    for (int i = 0; i < n; i++)
        cout << seq[i].second <<" \n"[i==n-1] ;
    return 0;
}
/**
13 14
0 1
0 4
8 10
1 3
7 9
4 3
8 7
11 2
10 12
0 5
3 6
5 6
7 12
3 5
*/
