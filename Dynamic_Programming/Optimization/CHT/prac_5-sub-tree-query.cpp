/**
    problem: https://codeforces.com/contest/932/problem/F    
    
    dp[u] = min{a[u]*b[v]+dp[v]} for all v in subtree of u
    f(x) = b[v]*x+dp[v]
    query with a[u]
 */

#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;


vector<int> adj[MAX];


struct Line {
  //mx+c
  mutable ll m, c, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

//for min query LineContainer(true), normally->max
struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  int mnQ=1;
  LineContainer(bool minQuery=false){
    if(minQuery) mnQ=-1;
    else mnQ=1;
  }
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->m == y->m) x->p = x->c > y->c ? inf : -inf;
    else x->p = div(y->c - x->c, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll c) {
    m*=mnQ, c*=mnQ;
    auto z = insert({m, c, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return mnQ*(l.m * x + l.c);
  }
};

ll a[MAX],b[MAX], dp[MAX];
void DFS(ll u, ll p, LineContainer &h)
{
    for(auto v: adj[u])
    {
        if(v==p) continue;
        LineContainer hh(1);
        DFS(v, u, hh);

        //merge
        if(hh.size()>h.size()) swap(hh,h);

        for(auto x : hh)
            h.add(hh.mnQ*x.m, hh.mnQ*x.c);
        hh.clear();
    }

    if(u==1 || adj[u].size()>1)
        dp[u] = h.query(a[u]);
    h.add(b[u], dp[u]);
}

void syntex_error()
{
    ll n,m,i,j,k,x,y,l,r;
    
    cin>>n;
    LineContainer h(1);

    for(i=1; i<=n; i++) cin>>a[i];
    for(i=1; i<=n; i++) cin>>b[i];

    for(i=1; i<n; i++){
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    DFS(1,-1, h);

    // while(order.size()){
    //     x = order.back();
    //     order.pop_back();
    //     l=in[x]+1;
    //     r=out[x];

    //     h = LineContainer(1);
    //     for(i=l; i<=r; i++){
    //         h.add(b[FT[i]], dp[FT[i]]);
    //     }
    //     if(!h.size()) dp[x]=0;
    //     else dp[x] = h.query(a[x]);
    // }

    for(i=1; i<=n; i++) cout<<dp[i]<<" ";cout<<endl;
    
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
