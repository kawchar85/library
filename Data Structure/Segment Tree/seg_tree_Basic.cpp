#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
typedef long long ll;

int arr[MAX],N;
struct info
{
    int sum,mn,mx;
    info()
    {
        sum=0;
        mn=INT_MAX/100;
        mx=INT_MIN/100;
    }
    info(int x, int y, int z)
    {
        sum=x;
        mx=y;
        mn=z;
    }
    void show(){
        cout<<sum<<" "<<mn<<" "<<mx<<endl;
    }
}tree[3*MAX];

info leaf(int i){
    return info(arr[i], arr[i], arr[i]);
}
info Set(ll x){
    return info(x,x,x);
}
info outOfRange(){
    return info();
}
info merge(info x, info y){
    info ans;
    ans.sum=x.sum+y.sum;
    ans.mn=min(x.mn, y.mn);
    ans.mx=max(x.mx, y.mx);
    return ans;
}

///call with build(1,0,n-1)
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

    tree[node]=merge(tree[node*2], tree[2*node+1]);
}

info query(int node, int l, int r, int i, int j)
{
    if(i>r || j<l)
        return outOfRange();
    if(l>=i && r<=j)
        return tree[node];
    int mid=(l+r)/2;
    info x=query(node*2,l,mid,i,j);
    info y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y);
}

///call with update(1,0,n-1,pos,val)
void update(int node,int l,int r,int pos,int val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node]=Set(val);
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=merge(tree[node*2], tree[2*node+1]);

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
void update(int pos, ll val){ //arr[pos]=val
    update(1,0,N-1,pos,val);
}
void query(int i, int j){
    auto x = query(1, 0, N-1, i, j);
    x.show();
}
int main()
{

    int n,i,q,x,y,k,ans;
    cin>>n>>q;
    for(i=0;i<n;i++)
        cin>>arr[i];
    build(n);
    //print();
    while(q--)
    {
        cin>>k>>x>>y;
        if(k==1)
            query(x-1,y-1);
        else
            update(x-1,y);
    }
    return 0;
}
