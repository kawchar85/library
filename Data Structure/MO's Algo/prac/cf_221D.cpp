/*
    cnt x suth that
    freq[x]=x

    https://codeforces.com/contest/221/problem/D
*/

#include<bits/stdc++.h>
using namespace std;
#define MAX 300005
#define B_SIZE 320 

struct query{
    int l,r,id;
};
query Q[MAX];
int ar[MAX], ans[MAX],cnt=0;
unordered_map<int, int> fre;
bool cmp(query &a, query &b)
{
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
void add(int pos)
{
    if(fre[ar[pos]]==ar[pos])
        cnt--; //ageerta bad
    fre[ar[pos]]++;
    if(fre[ar[pos]]==ar[pos])
        cnt++;//new freq[x]=x
}
void sub(int pos)
{
    if(fre[ar[pos]]==ar[pos])
        cnt--;//already add chilo.
    fre[ar[pos]]--;
    if(fre[ar[pos]]==ar[pos])
        cnt++; //new asche
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
    cin>>n>>q;
    for(i=0; i<n; i++)
    {
        cin>>ar[i];
        //scanf("%d",&ar[i]);
    }
    
    for(i=0; i<q; i++)
    {
        cin>>L>>R;
        //scanf("%d %d",&L, &R);
        Q[i].id=i;
        Q[i].l=L-1;
        Q[i].r=R-1;
    }

    MO(q);

    for(i=0; i<q; i++)
        cout<<ans[i]<<endl;
        //printf("%d\n", ans[i]);

    return 0;
}
