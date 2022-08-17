//https://codeforces.com/contest/914/problem/D

#include<bits/stdc++.h>
#define MAX 500005
#define ll long long
using namespace std;

ll arr[MAX];
int N,mis;

struct info{
    ll g;
    info(){
        g=0;
    }
    info(ll x){
        g=x;
    }
    void show(){
        cout<<"GCD = "<<g<<"\n";
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
    return info(__gcd(x.g,y.g));
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

void query(int node,int l,int r,int i,int j,ll x)
{
    if(mis>1) return;
    if(i>r || j<l)
        return;
    int mid=(l+r)/2;
    if(l>=i && r<=j)
    {
        if(l==r)
        {
            mis+=!(tree[node].g%x==0);
            return;
        }
        if(tree[node].g%x==0) return;
        if(tree[node*2].g%x && tree[node*2+1].g%x)
        {
            mis+=2;
            return;
        }
        if(tree[node*2].g%x)
        {
            query(node*2,l,mid,i,j,x);
            return;
        }
        if(tree[node*2+1].g%x)
        {
            query(node*2+1,mid+1,r,i,j,x);
            return;
        }
    }
    
    query(node*2,l,mid,i,j,x);
    query(node*2+1,mid+1,r,i,j,x);
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
string query(int i, int j, ll x){
    mis=0;
    query(1,0,N-1,i,j,x); 
    if(mis>1) return "NO";
    else return "YES";
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,q,k;
    cin>>n;
    for(i=0;i<n;i++)
        cin>>arr[i];
    build(n);
    //print();
    cin>>q;
    while(q--)
    {
        cin>>k;
        if(k==1){
            int x,y;
            ll g;
            cin>>x>>y>>g;
            cout<<query(x-1,y-1,g)<<endl;
        }
        else{
            int x; ll y;
            cin>>x>>y;
            update(x-1,y);
            //print();
        }
    }
    return 0;
}
