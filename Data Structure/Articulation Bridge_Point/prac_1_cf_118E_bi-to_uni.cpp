/**
You are given an undirected connected graph G.
Direct all of its edges so that the resulting
digraph is strongly connected, or declare that
this is impossible.

https://codeforces.com/contest/118/problem/E
*/

#include<bits/stdc++.h>
using namespace std;

#define clean(x,y) memset(x,y,sizeof(x));
#define pb push_back
#define F first
#define S second
#define LB lower_bound
#define UB upper_bound
#define ALL(v) v.begin(),v.end()
#define PI acos(-1.0)
#define EPS 1e-9
#define INF (1 << 30)
#define MOD 1000000007
#define MAX 200005
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define dbg(x) cout<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "
#define tin ll T; cin>>T; while(T--)

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

vi adj[MAX];
vector< pii > span_edge,back_edge,bridge;
bool vis[MAX];
int d[MAX],low[MAX],timer;

void arti_bridge(int u, int par)
{
    vis[u]=1;
    low[u]=d[u]= ++timer;

    for(auto now : adj[u])
    {
        if(now==par) continue;
        if(vis[now])
        {
            low[u]=min(low[u],d[now]);
            if(d[now]<d[u])
            {
                back_edge.pb({u,now});
            }
        }
        else
        {
            span_edge.pb({u,now});
            arti_bridge(now, u);
            low[u]=min(low[u],low[now]);
            if(d[u]<low[now])
                bridge.pb({u,now});
        }
    }
}

int main()
{
    FAST

    int n,m,i,j;

    cin>>n>>m;

    for(i=0; i<m; i++)
    {
        int X,Y;
        cin>>X>>Y;
        adj[X].pb(Y);
        adj[Y].pb(X);
    }
    arti_bridge(1,-1);
    if(bridge.size())
        cout<<0<<endl;
    else
    {
        for(auto x : span_edge)
            cout<<x.F<<" "<<x.S<<endl;
        for(auto x : back_edge)
            cout<<x.F<<" "<<x.S<<endl;
    }

    return 0;
}

 
