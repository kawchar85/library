#include<bits/stdc++.h>
using namespace std;
#define MAX 300005
#define B_SIZE 550 ///sqrt(MAX)

struct query{
    int l,r,id;
};
query Q[MAX];
int ar[MAX], ans[MAX], fre[1000006],cnt=0;

bool cmp(query &a, query &b)
{
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
/*
bool cmp(query a, query b)
{
    if(a.l/B_SIZE==b.l/B_SIZE)
        return a.r<b.r;
    return a.l/B_SIZE < b.l/B_SIZE;
}
*/
void add(int pos)
{
    fre[ar[pos]]++;
    if(fre[ar[pos]]==1)
        cnt++;
}
void sub(int pos)
{
    fre[ar[pos]]--;
    if(!fre[ar[pos]])
        cnt--;
}
int get_ans()
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
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>ar[i];
    }
    cin>>q;
    for(i=0; i<q; i++)
    {
        cin>>L>>R;
        Q[i].id=i;
        Q[i].l=L-1;
        Q[i].r=R-1;
    }

    MO(q);

    for(i=0; i<q; i++)
        cout<<ans[i]<<"\n";

    return 0;
}
