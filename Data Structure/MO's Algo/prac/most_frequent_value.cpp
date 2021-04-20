//https://www.spoj.com/problems/FREQ2/

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 300005

typedef long long ll;

ll max_cnt;
#define B_SIZE 550 ///sqrt(MAX)

struct Query{
    ll l,r,id;
};

Query Q[MAX];
ll cnt[MAX],fre[MAX],ans[MAX],ar[MAX];

bool cmp(Query &a, Query &b)
{
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
void add(int pos)
{
    if(cnt[ar[pos]] != 0) fre[cnt[ar[pos]]]--;
    //if(fre[max_cnt]==0) max_cnt--;
        cnt[ar[pos]]++;
    fre[cnt[ar[pos]]]++;
    max_cnt=max(max_cnt, cnt[ar[pos]]);    
}
void sub(int pos)
{
    if(cnt[ar[pos]] != 0) fre[cnt[ar[pos]]]--;
    if(fre[max_cnt]==0) max_cnt--;
    if(max_cnt<1) max_cnt=1;
        cnt[ar[pos]]--;
    if(cnt[ar[pos]] != 0) fre[cnt[ar[pos]]]++;
}
ll get_ans()
{
    return max_cnt;
}
void MO(int q)
{
    sort(Q, Q+q, cmp);

    int cur_l=0, cur_r=-1;
    for(int i=0; i<q; i++)
    {
        int L=Q[i].l;
        int R=Q[i].r;
        int len=(R-L+1);

        while(cur_l>L)  add(--cur_l);
        while(cur_r<R)  add(++cur_r);

        while(cur_l<L)  sub(cur_l++);
        while(cur_r>R)  sub(cur_r--);

        ans[Q[i].id]=get_ans();
    }
}
void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    
    cin>>n>>m;
    for(i=0; i<n; i++)
    {
        cin>>ar[i];
    }

    ll L,R;
    for(i=0; i<m; i++)
    {
        cin>>L>>R;
        Q[i].id=i;
        Q[i].l=L;
        Q[i].r=R;
    }

    MO(m);

    for(i=0; i<m; i++)
        cout<<ans[i]<<"\n";
    
    
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    //cin>>TC;

    while(TC--){
        //CS(cs++);
        syntex_error();
    }

    return 0;
}   
