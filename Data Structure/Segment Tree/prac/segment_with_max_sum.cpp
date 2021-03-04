/**
    1) i v: set arr[i]=v
    2) find segment with maximum sum
    https://codeforces.com/edu/course/2/lesson/4/2/practice/contest/273278/problem/A
*/
#include<bits/stdc++.h>
#define MAX 100005
#define ll long long
using namespace std;

ll arr[MAX];
int N;

struct info{
    ll mx,pref,suf,sum;

    info(){
        mx=pref=suf=sum=0LL;
    }
    info(ll x){
        mx=max(0LL, x);
        pref=suf=sum=x;
    }
    info(ll a, ll b, ll c, ll d){
        mx=a;pref=b;suf=c;sum=d;
    }
    void show(){
        cout<<mx<<" "<<pref<<" "<<suf<<" "<<sum<<"\n";
    }
};
info tree[3*MAX];

info leaf(int x){
    return info(x);
}
info outOfRange(){
    return info();
}
info merge(info x, info y){
    return info(
        max({x.mx, y.mx, x.suf+y.pref}),
        max(x.pref, x.sum+y.pref),
        max(y.suf, y.sum+x.suf),
        x.sum+y.sum
    );
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node]=leaf(arr[l]);
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
        tree[node]=leaf(val);
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=merge(tree[node*2],tree[2*node+1]);
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
info query(){
    auto ans = query(1,0,N-1,0,N-1); 
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,q,k,x,y;
    info ans;
    cin>>n>>q;
    for(i=0;i<n;i++)
        cin>>arr[i];
    build(n);
    ans=query();
    cout<<ans.mx<<endl;
    while(q--)
    {
        cin>>x>>y;
        update(x,y);
        ans=query();
        cout<<ans.mx<<endl;
    }
    return 0;
}
