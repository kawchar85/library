//code is not tested
//Broken link: BZOJ2654

/**
    You’re given a weighted, undirected and connected graph G
    with N nodes, and M edges. Every edge has a weight w and
    a color c, which is either black or white. Please calculate
    the sum of weights on the minimum spanning tree that
    contains exactly K white edges
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;
vector<ll> adj[MAX];
struct Edge{
    ll u,v,w,c;
    Edge(){}
    Edge(ll x,ll y,ll z, ll col){
        u=x;v=y;w=z;c=col;
    }
};
bool operator<(Edge a,Edge b){
    return a.w<b.w;
}

vector<Edge>E;
ll par[MAX],n;

ll find_par(ll x){
    return par[x]==x?x:par[x]=find_par(par[x]);
}

pair<ll,ll> solveWithPenalty(ll p){
  //add penalty
  for(int i=0; i<E.size(); i++){
    if(E[i].c == 0)//white edge
        E[i].w+=p;
  }

  ll ans=0,cnt=0;

  //mst
  for(int i=0; i<=n; i++) par[i]=i;
  sort(ALL(E));
  for(auto now : E){
    ll u = find_par(now.u);
    ll v = find_par(now.v);
    if(u == v) continue;
    par[u]=v;
    ans+=now.w;
    if(now.c == 0) cnt++;//white taken
  }
  //remove penalty
  for(int i=0; i<E.size(); i++){
    if(E[i].c == 0)//white edge
        E[i].w-=p;
  }
  return {ans, cnt};
}
ll Alien(ll l, ll r, ll need){
  ll ans=-1;
  while(l <= r) {
    ll mid = l+(r-l)/2;
    pair<ll,ll> res = solveWithPenalty(mid); 
    if(res.second >= need) ans = res.first - mid * need, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}
void syntex_error()
{
    ll m,k,i,x,y,z,c;

    cin>>n>>m>>k;
    for(i=0; i<m; i++){
        cin>>x>>y>>z>>c;
        E.push_back({x,y,z,c});
    }

    //max weight = 500
    cout<<Alien(-500, 500, k)<<endl;
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    //cin>>TC;

    while(TC--){
        //CS(cs++);
        syntex_error();
    }

    return 0;
}

/*
5 6 1
1 3 100 1
1 2 5 1
2 3 200 0
2 4 100 1
3 4 5 1
4 5 100 1
*/
