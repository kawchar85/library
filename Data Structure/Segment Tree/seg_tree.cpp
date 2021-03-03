#include<bits/stdc++.h>
#define MAX 100005
#define ll long long
using namespace std;

ll arr[MAX];
int N;

struct info{
    ll sum;
    info(){
        sum=0;
    }
    info(ll x){
        sum=x;
    }
    void show(){
        cout<<"Sum = "<<sum<<"\n";
    }
};
info tree[3*MAX];

info leaf(int i){
    return info(arr[i]);
}
info outOfRange(){
    return info(0);
}
info Set(ll x){
    return info(x);
}
info merge(info x, info y){
    info temp;
    temp.sum=x.sum+y.sum;
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
        tree[node]=Set(val);
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
    if(sum<=tree[2*node].sum)
    {
       return searchQuery(2*node, l, mid, sum);
    }
    else
    {
        return searchQuery(2*node+1, mid+1, r, sum-tree[2*node].sum);
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
ll query(int x, int y){
    auto ans = query(1,0,N-1,x,y); 
    return ans.sum;
}
int find_index(ll sum){
    return searchQuery(1,0,N-1,sum);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,q,k;
    cin>>n>>q;
    for(i=0;i<n;i++)
        cin>>arr[i];
    build(n);
    while(q--)
    {
        cin>>k;
        if(k==2){
            int x,y;
            cin>>x>>y;
            update(x-1,y);
        }
        else{
            int x; ll y;
            cin>>x>>y;
            cout<<query(x-1,y-1)<<endl;
        }
    }
    return 0;
}
