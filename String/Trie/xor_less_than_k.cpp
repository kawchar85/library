/**
    total continuous sub_array = (n*(n+1))/2;

    count sub-array such that xor<k
*/
#define sz 3000006
#include<bits/stdc++.h>
#define getbit(n,i) ((n>>i)&1)
#define ll long long
using namespace std;

struct node{
    ll cnt[2],next[2];
    node()
    {
        cnt[0]=cnt[1]=0;
        next[0]=next[1]=0;
    }
}tree[sz];

ll counter=1;
void Insert(ll n)
{
    ll i,now,cur=0;
    for(i=31; i>=0; i--)
    {
        now=getbit(n,i);
        tree[cur].cnt[now]++;
        if(tree[cur].next[now]==0)
            tree[cur].next[now]=counter++;
        cur=tree[cur].next[now];
    }
}

ll query(ll n, ll k)
{
    ll cur=0,i,now_n,now_k,ans=0;
    for(i=31; i>=0; i--)
    {
        now_k=getbit(k,i);
        now_n=getbit(n,i);
        if(now_k)
        {
            ans+=tree[cur].cnt[now_n];
            if(tree[cur].next[now_n^1]==0)
                break;
            cur=tree[cur].next[now_n^1];
        }
        else
        {
            if(tree[cur].next[now_n]==0)
                break;
            cur=tree[cur].next[now_n];
        }
    }
    return ans;
}

void delete_trie()
{
    counter=1;
    memset(tree,0,sizeof tree);
}

int main()
{
    ll t,n,x,k,Xor,ans,i;
    scanf("%lld",&t);
    while(t--)
    {
        ans=Xor=0;
        Insert(Xor);
        scanf("%lld %lld",&n,&k);
        while(n--)
        {
            scanf("%lld",&x);
            Xor^=x;
            ans+=query(Xor,k);
            Insert(Xor);
        }
        printf("%lld\n",ans);
        delete_trie();
    }
}
