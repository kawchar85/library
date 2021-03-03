/**
    Given a bracket sequence or 
    in other words a string S of
    length n, consisting of 
    characters ‘(‘ and ‘)’. Find 
    length of the maximum correct
    bracket subsequence of sequence
    for a given query range
*/
#include<bits/stdc++.h>
#define MAX 1000006
#define ll long long
using namespace std;

int N;
string s;

struct info{
    ll len,open,close;

    info(){
        len=open=close=0LL;
    }
    info(ll x, ll y, ll z){
        len=x;
        open=y;
        close=z;
    }
    void show(){
        cout<<len<<" "<<open<<" "<<close<<"\n";
    }
};

info tree[3*MAX];

info leaf(int i){
    return info(0LL, s[i]=='(', s[i]==')');
}

info outOfRange(){
    return info(0LL,0LL,0LL);
}

info merge(info x, info y){
    info temp;
    ll mn=min(x.open,y.close);
    temp.len=x.len+y.len+2LL*mn;
    temp.open=x.open+y.open-mn;
    temp.close=x.close+y.close-mn;
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
ll query(int x, int y){
    auto ans = query(1,0,N-1,x,y); 
    return ans.len;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n,i,q,x,y;
    cin>>s>>q;
    build((int)s.size());
    while(q--)
    {
        cin>>x>>y;
        cout<<query(x-1,y-1)<<endl;
    }
    return 0;
}
