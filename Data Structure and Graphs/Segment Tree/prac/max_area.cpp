//LOJ-histogram

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

#define dbg(x) if(DEBUG) cout<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "

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

ll arr[MAX];
ll ans[MAX];
int N;

struct info{
    ll val,id;
    info(){
    }
    info(ll x){
        val=x;
    }
    info(ll x,ll y){
        val=x;
        id=y;
    }
    void show(){
        cout<<"Val = "<<val<<"\n";
    }
};
info tree[3*MAX];

info leaf(int i){
    return info(arr[i],i);
}
info outOfRange(){
    return info(INT_MAX,N);
}
info Set(ll x,ll i){
    return info(x,i);
}
info merge(info x, info y){
    info temp=y;
    if(x.val<y.val)
    {
        temp=x;
    }
    return temp;
}


void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node]=leaf(l);
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    tree[node]=merge(tree[node*2],tree[2*node+1]);
}

info query(int node,int l,int r,int i,int j)
{
    if(i>r || j<l)
        return outOfRange();
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    auto x=query(node*2,l,mid,i,j);
    auto y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

void update(int node,int l,int r,int pos,ll val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node]=Set(val,l);
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=merge(tree[node*2],tree[2*node+1]);
}

int searchQuery(int node, int l, int r, ll sum)
{
    int mid=(l+r)/2;
    if(l==r)
        return l;
    if(sum<=tree[2*node].val)
    {
       return searchQuery(2*node, l, mid, sum);
    }
    else
    {
        return searchQuery(2*node+1, mid+1, r, sum-tree[2*node].val);
    }
}
int searchQueryRight(int node, int l, int r, int sum)
{
    int mid=(l+r)/2;
    if(l==r)
        return l;
    if(sum<=tree[2*node+1].val)
    {
       return searchQueryRight(2*node+1, mid+1, r, sum);
    }
    else
    {
        return searchQueryRight(2*node, l, mid, sum-tree[2*node+1].val);
    }
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
    print(1,0,N-1);
}
void build(int n){
    N=n;
    build(1,0,N-1);
}
void update(int pos, ll val){
    update(1,0,N-1,pos,val);
}
info query(int x, int y){
    auto ans = query(1,0,N-1,x,y); 
    return ans;
}
int find_index(ll sum){
    return searchQueryRight(1,0,N-1,sum);
    //return searchQuery(1,0,N-1,sum);
}
ll Area(ll i, ll j){
    if(i>j) return 0LL;
    if(i==j) return arr[i];
    auto x = query(i,j);
    ll a1=x.val*(j-i+1);
    ll a2=Area(i, x.id-1);
    ll a3=Area(x.id+1, j);
    //cout<<i<<","<<j<<": "<<a1<<endl;
    return max({a1, a2, a3});
}

void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN;
    vl v;
    string s;
    
    cin>>n;

    for(i=0; i<n; i++)
        cin>>arr[i];
    build(n);
    //cout<<"\n----\n";
    //print();
    cout<<Area(0, n-1)<<endl;
}

int32_t main()
{
    FAST
    
    //freopen("a.in","r", stdin);
    //freopen("a.out","w", stdout);
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        CS(cs++);
        syntex_error();
    }

    return 0;
}
