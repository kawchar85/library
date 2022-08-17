#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);

#define MAX 1000006

int tree[3*MAX];

void update(int node,int l,int r,int pos,int val)
{
    if(pos>r || pos<l)
        return;
    if(l==r)
    {
        tree[node]+=val;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(node*2,l,mid,pos,val);
    else
        update(node*2+1,mid+1,r,pos,val);

    tree[node]=tree[node*2]+tree[node*2+1];
}
int search_index(int node, int l, int r, int sum)
{
    int mid=(l+r)/2;
    if(l==r)
        return l;
    if(sum<=tree[2*node])
    {
       return search_index(2*node, l, mid, sum);
    }
    else
    {
        return search_index(2*node+1, mid+1, r, sum-tree[2*node]);
    }
}
void addToMultiset(int val)
{
    update(1, 1, MAX-1, val, 1);
}
void deleteFromMultiset(int val)
{
    update(1, 1, MAX-1, val, -1);
}
int find_k_th(int k)
{
    if(tree[1]<k) return -1;
    return search_index(1, 1, MAX-1, k);
}
int main()
{
    FAST
    int i,j;
    
    int n,q,k;
    cin>>n>>q;
    while(n--)
    {
        cin>>k;
        addToMultiset(k);
    }
    while(q--)
    {
        cin>>k;
        if(k>0)
            addToMultiset(k);
        else
        {
            k*=-1;
            k=find_k_th(k);
            deleteFromMultiset(k);
        }
    }

    k=tree[1]?find_k_th(1): 0;
    cout<<k<<endl;


    return 0;
}
 
