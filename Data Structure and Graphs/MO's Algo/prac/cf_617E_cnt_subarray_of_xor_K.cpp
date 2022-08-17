//https://codeforces.com/contest/617/problem/E


#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 100005
#define B_SIZE 320 ///sqrt(MAX)

struct query{
    int l,r,id;
};
query Q[MAX];
int ar[MAX],fre[MAX*100];
int k;
ll cnt=0LL,ans[MAX];

bool cmp(query &a, query &b)
{
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}

void add(int pos)
{
    cnt+=1LL*fre[ar[pos]^k];
    fre[ar[pos]]++;
}
void sub(int pos)
{
    fre[ar[pos]]--;
    cnt-=1LL*fre[ar[pos]^k];
}
ll get_ans()
{
    return cnt;
}
void MO(int q)
{
    sort(Q, Q+q, cmp);

    int cur_l=0, cur_r=-1;
    for(int i=0; i<q; i++)
    {
        int L=Q[i].l;
        int R=Q[i].r;

        while(cur_l>L)  add(--cur_l);
        while(cur_r<R)  add(++cur_r);

        while(cur_l<L)  sub(cur_l++);
        while(cur_r>R)  sub(cur_r--);

        ans[Q[i].id]=get_ans();
    }
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int i,j,n,q,L,R;
    cin>>n>>q>>k;
    for(i=1; i<=n; i++)
    {
        cin>>ar[i];
        ar[i]^=ar[i-1];
    }
    
    for(i=0; i<q; i++)
    {
        cin>>L>>R;
        Q[i].id=i;
        Q[i].l=L-1; //cum[1...x]^cum[1...L-1]=cum[1...L]
        Q[i].r=R;
    }

    MO(q);

    for(i=0; i<q; i++)
        cout<<ans[i]<<"\n";

    return 0;
}
