#include<bits/stdc++.h>
#define MAX 100005
#define ll long long
#define INF LLONG_MAX
using namespace std;

struct item{
    ll mx,pref,suf,sum,lazy;
    item()
    {
        lazy=INF;
        mx=pref=suf=sum=0LL;
    }
    item(ll a, ll b, ll c, ll d, ll e)
    {
        mx=a;
        pref=b;
        suf=c;
        sum=d;
        lazy=e;
    }
    void show(){
        cout<<mx<<" "<<pref<<" "<<suf<<" "<<sum<<" "<<lazy<<endl;
    }
}; 
ll arr[MAX];
int N;
item tree[3*MAX];

item merge(item x,item y, ll lazy)
{
    return item(
        max({x.mx, y.mx, x.suf+y.pref}),
        max(x.pref, x.sum+y.pref),
        max(y.suf, y.sum+x.suf),
        x.sum+y.sum,
        lazy);
}

void propagate(int node, int l, int r)
{
    if(tree[node].lazy==INF) return;

    tree[node].sum=tree[node].lazy*(r-l+1);
    tree[node].pref=max(0LL,tree[node].sum);
    tree[node].mx=max(0LL,tree[node].sum);
    tree[node].suf=max(0LL,tree[node].sum);

    if(l!=r)
    {
        tree[2*node].lazy=tree[node].lazy;
        tree[2*node+1].lazy=tree[node].lazy;
    }
    tree[node].lazy=INF;
}

item query(int node,int l,int r,int i,int j)
{
    propagate(node, l,r);
    if(i>r || j<l)
        return item(0LL,0LL,0LL,0LL,0LL);
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    item x =query(node*2,l,mid,i,j);
    item y =query(node*2+1,mid+1,r,i,j);

    return merge(x,y,0LL);
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

    tree[node]=merge(tree[node*2],tree[node*2+1],tree[node].lazy);
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
void build(int n)
{
    N=n;
    //build(1,0,N-1);
}
void update(int i, int j, ll val)
{
    update(1,0,N-1,i,j,val);
}
ll query()
{
    return query(1,0,N-1,0,N-1).mx;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,q,x,y;
    ll z;
    cin>>n>>q;
    build(n);
    //print();
    while(q--)
    {
        cin>>x>>y>>z;
        update(x,y-1,z);
        //print();
        cout<<query()<<endl;
    }
    return 0;
}
