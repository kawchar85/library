#include<iostream>
#include<vector>
#define MAX 10000
#define ll long long
using namespace std;

vector<ll>adj[MAX],point;
vector< pair<ll,ll> > span_edge,back_edge,bridge;
bool arti_point[MAX],vis[MAX];
ll d[MAX],low[MAX],timer=0;

void arti_BP(ll u=1, ll par=-1)
{
    low[u]=d[u]=++timer;
    vis[u]=1;
    ll child=0;
    for(auto now : adj[u])
    {
        if(now==par)continue;

        if(vis[now])
        {
            low[u]=min(low[u],d[now]);
            if(d[now]<d[u])
            {
                back_edge.push_back({u,now});
            }
        }
        else
        {
            span_edge.push_back({u,now});
            arti_BP(now,u);
            low[u]=min(low[u],low[now]);
            if(d[u]<low[now])
                bridge.push_back({u,now});
            if(d[u]<=low[now] && par!=-1)
                arti_point[u]=1;
            child++;
        }
        if(child>1 && par==-1)
            arti_point[u]=1;
    }
}

void find_ABP(ll n)
{
    arti_BP();
    for(int i=1; i<=n; i++){
        if(arti_point[i])
            point.push_back(i);
    }

    cout<<"span_egdes:\n";
    for(auto x : span_edge)
        cout<<x.first<<":"<<x.second<<endl;
    cout<<"back_egdes:\n";
    for(auto x : back_edge)
        cout<<x.first<<":"<<x.second<<endl;
    cout<<"bridges:\n";
    for(auto x : bridge)
        cout<<x.first<<":"<<x.second<<endl;
    
    timer=0;
    for(int i=0; i<=n; i++){
        adj[i].clear();
        vis[i]=arti_point[i]=0;
    }
}

int main()
{
    int n,m,x,y,i,j,k;
    cin>>n>>m;

    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    find_ABP(n);
    return 0;
}
