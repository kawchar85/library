//https://codeforces.com/contest/145/problem/E
#include<bits/stdc++.h>
#define MAX 1000006
#define ll long long
using namespace std;

ll arr[MAX];
int N;
string s;

struct info{
    ll lazy,cnt4,cnt7,cnt47,cnt74;

    info()
    {
        lazy=0LL;
        cnt4=cnt7=cnt47=cnt74=0LL;
    }
    info(ll lz,ll a, ll b, ll c, ll d)
    {
        lazy=lz;
        cnt4=a; cnt7=b; cnt47=c; cnt74=d;
    }
    void show()
    {
        cout<<cnt4<<" "<<cnt7<<" "<<lazy<<endl;
    }
}tree[3*MAX];

void propagate(int node, int l, int r)
{
    if(!tree[node].lazy) return;

    swap(tree[node].cnt4, tree[node].cnt7);
    swap(tree[node].cnt47, tree[node].cnt74);
    if(l!=r)
    {
        tree[2*node].lazy^=tree[node].lazy;
        tree[2*node+1].lazy^=tree[node].lazy;
    }
    tree[node].lazy=0;
}

info merge(info x, info y, ll lz)
{
    return info(
        lz,
        x.cnt4+y.cnt4,
        x.cnt7+y.cnt7,
        max(x.cnt4+y.cnt47, x.cnt47+y.cnt7),
        max(x.cnt7+y.cnt74, x.cnt74+y.cnt4)
    );
}

void build(int node, int l,int r)
{
    if(l==r)
    {
        tree[node].lazy=0LL;
        tree[node].cnt4=(s[l]=='4');
        tree[node].cnt7=(s[l]=='7');
        tree[node].cnt47=1;
        tree[node].cnt74=1;
        return;
    }
    int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);

    tree[node]=merge(tree[node*2],tree[2*node+1], 0LL);
}
info query(int node,int l,int r,int i,int j)
{
    propagate(node,l,r);

    if(i>r || j<l)
        return info();
    if(l>=i && r<=j)
        return tree[node];

    int mid=(l+r)/2;
    auto x=query(node*2,l,mid,i,j);
    auto y=query(node*2+1,mid+1,r,i,j);
    return merge(x,y, 0LL);
}

void update(int node,int l,int r,int i,int j)
{
    propagate(node,l,r);
    if(i>r || j<l)
        return;
    if(l>=i && r<=j)
    {
        tree[node].lazy^=1;
        propagate(node,l,r);
        return;
    } 
    int mid=(l+r)/2;
    update(node*2,l,mid,i,j);
    update(node*2+1,mid+1,r,i,j);

    tree[node]=merge(tree[node*2],tree[node*2+1], tree[node].lazy);
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
void update(int i, int j){
     update(1,0,N-1,i,j);
}
ll query(){
    auto ans = query(1,0,N-1,0,N-1); 
    return max({ans.cnt4, ans.cnt7, ans.cnt47});
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll n,i,q,z,k;
    string ss;

    cin>>n>>q>>s;
    build(n);

    while(q--)
    {
        cin>>ss;
        if(ss=="switch")
        {
            int l,r;
            cin>>l>>r;
            update(l-1,r-1);
        }
        else
            cout<<query()<<endl;
    }
    return 0;
}
