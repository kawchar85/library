//https://algo.codemarshal.org/contests/mist-ncpc-2020/problems/D

/**
    "If you have an apple and I have an apple and
    we exchange apples then you and I will still
    each have one apple. But if you have an idea
    and I have an idea and we exchange these
    ideas, then each of us will have two ideas."
                        -George Bernard Shaw
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
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define printa(a,L,R) for(int ii=L; ii<R; ii++) cout<<a[ii]<<" \n"[ii==R-1]
#define printv(a) printa(a,0,(int)a.size())
#define Unique(a) sort(ALL(a)); (a).resize(unique(ALL(a)) - (a).begin())
#define SZ(v) (int)v.size()
#define MOD 1000000007
#define MAX 200005
#define DEBUG 1

#define dbg(x) if(DEBUG) cout<<"Line "<<__LINE__<<": "<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<":\n"

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;

vl adj[MAX];

int FT[MAX],in[MAX], out[MAX];
int Timer=1;

ll arr[MAX];
int N;
struct info{
    ll lazy,val;
    info()
    {
        lazy=-1;
        val=0LL;
    }
    void show()
    {
        cout<<val<<" "<<lazy<<endl;
    }
}tree[3*MAX];

void propagate(int node, int l, int r)
{
    if(tree[node].lazy==-1) return;

    tree[node].val=tree[node].lazy*(r-l+1);
    if(l!=r)
    {
        tree[2*node].lazy=tree[node].lazy;
        tree[2*node+1].lazy=tree[node].lazy;
    }
    tree[node].lazy=-1;
}

ll merge(ll x, ll y)
{
    return x+y;
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node].lazy=-1;
        tree[node].val=arr[l];
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node].lazy=-1;
    tree[node].val=merge(tree[node*2].val,tree[2*node+1].val);
}
ll query(int node,int l,int r,int i,int j)
{
    propagate(node,l,r);

    if(i>r || j<l)
        return 0LL;
    if(l>=i && r<=j)
        return tree[node].val;
    int mid=(l+r)/2;
    auto x=query(node*2,l,mid,i,j);
    auto y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}
ll queryVal(int node,int l,int r,int idx)
{
    propagate(node,l,r);
    if(idx>r || idx<l)
        return 0LL;
    if(l==r)
        return tree[node].val;
    int mid=(l+r)/2;
    if(idx<=mid)
        return queryVal(node*2,l,mid,idx);
    else
        return queryVal(node*2+1,mid+1,r,idx);
}
int searchQuery(int node, int l, int r, ll sum)
{
    propagate(node,l,r);

    int mid=(l+r)/2;
    if(l==r)
        return l;
    ll x=tree[2*node].val;
    if(sum<=x)
        return searchQuery(2*node, l, mid, sum);
    else
        return searchQuery(2*node+1, mid+1, r, sum-x);
}

void update(int node,int l,int r,int i,int j,ll val)
{
    propagate(node,l,r);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy=val;
        propagate(node,l,r);
        return;
    } 
    int mid=(l+r)/2;
    update(node*2,l,mid,i,j,val);
    update(node*2+1,mid+1,r,i,j,val);

    tree[node].val=merge(tree[node*2].val,tree[node*2+1].val);
}

void print(int node, int l,int r)
{
    cout<<"["<<l<<","<<r<<"]:--> ";
    tree[node].show();
    if(l==r)
        return;
    int mid=(l+r)/2;
    print(node*2,l,mid);
    print(node*2+1,mid+1,r);
}
void print(){
    print(1,1,N);
}
void build(int n){
    N=n;
    build(1,1,N);
}
void update(int i, int j, ll val){ //add val to arr[i...j]
     update(1,1,N,i,j,val);
}
ll query(int x, int y){
    auto ans = query(1,1,N,x,y); 
    return ans;
}
ll queryVal(int idx){ //arr[idx]
    return queryVal(1,1,N,idx);
}

void DFS(int u, int p=-1)
{
    //FT[Timer]=u;
    in[u] = Timer;

    for(auto v: adj[u])
    {
        if(v==p) continue;
        DFS(v, u);
    }

    FT[Timer]=u;
    out[u] = Timer++;
}

void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN;
    vl v;
    string s;
    
    cin>>n;

    Timer=1;
    for(i=0; i<=n; i++)
    {
      adj[i].clear();
      FT[i]=in[i]=out[i]=0;
      arr[i]=1LL;
    }
    
    for(i=1; i<n; i++)
    {
      cin>>x>>y;
      adj[x].pb(y);
      adj[y].pb(x);
    }

    for(i=1; i<=n; i++)
    {
      sort(ALL(adj[i]));
    }
    DFS(1);
    build(n);
    //print();
    /*for(i=1; i<=n; i++)
      cout<<FT[i]<<" \n"[i==n];*/

    cin>>m;
    while(m--)
    {
      cin>>k>>x;
      if(k==1)
      {
        cin>>y;
        l=in[x];
        r=out[x];
        d=query(l,r);
        
        if(d<=y)
        {
          update(l,r, 0LL);
          continue;
        }

        int id=l;
        for(int jump=r; jump>0; jump/=2)
          while(id+jump<=r && query(l,id+jump)<=y) id+=jump;
        
        update(l, id, 0LL);
      }
      else
      {
        y=queryVal(out[x]);
        cout<<1-y<<endl;  
      }
    }

}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        CS(cs++);
        syntex_error();
    }

    return 0;
}
