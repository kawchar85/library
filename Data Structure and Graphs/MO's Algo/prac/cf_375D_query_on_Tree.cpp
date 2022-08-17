//https://codeforces.com/contest/375/problem/D


/**
    "If you have an apple and I have an apple and
    we exchange apples then you and I will still
    each have one apple. But if you have an idea
    and I have an idea and we exchange these
    ideas, then each of us will have two ideas."
                        -George Bernard Shaw
*/
#include<bits/stdc++.h>
using namespace std;
 
#define clean(x,y) memset(x,y,sizeof(x));
#define pb push_back
#define F first
#define S second
#define LB lower_bound
#define UB upper_bound
#define ALL(v) v.begin(),v.end()
#define PI acos(-1.0)
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define printa(a,L,R) for(int ii=L; ii<R; ii++) cout<<a[ii]<<" \n"[ii==R-1]
#define printv(a) printa(a,0,(int)a.size())
#define Unique(a) sort(ALL(a)); (a).resize(unique(ALL(a)) - (a).begin())
#define SZ(v) (int)v.size()
#define MOD 1000000007
#define MAX 100005
 
#define dbg(x) cout<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "
#define tin ll T; cin>>T; while(T--)
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
 
#define B_SIZE 320 ///sqrt(MAX)
 
struct query{
    int l,r,id,k;
};
 
query Q[MAX];
vector<int> adj[MAX];
int col[MAX], ans[MAX], BIT[MAX+5], cnt[MAX];
int FT[MAX], in[MAX], out[MAX];
int Timer=1, N;
 
void DFS(int u, int p)
{
    FT[Timer]=u;
    in[u] = Timer++;
 
    for(auto v: adj[u])
    {
        if(v==p) continue;
        DFS(v, u);
    }
 
    out[u] = Timer-1;
}
void update(int x, int val)
{
    while(x<=MAX)
    {
        BIT[x]+=val;
        x+=x&(-x);
    }
}
 
int get_sum(int x)
{
    int sum=0;
    while(x>0)
    {
        sum+=BIT[x];
        x-=x&(-x);
    }
    return sum;
}
 
bool cmp(query &a, query &b)
{
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
void add(int pos)
{
    int c=col[FT[pos]];
    if(cnt[c]>0)  update(cnt[c], -1);
    cnt[c]++;
    if(cnt[c]>0)  update(cnt[c], 1);
}
void sub(int pos)
{
    int c=col[FT[pos]];
    if(cnt[c]>0)  update(cnt[c], -1);
    cnt[c]--;
    if(cnt[c]>0)  update(cnt[c], 1);
}
int get_ans(int k)
{
    return get_sum(MAX)-get_sum(k-1);
}
void MO(int q)
{
    sort(Q, Q+q, cmp);
 
    int cur_l=1, cur_r=0;
    for(int i=0; i<q; i++)
    {
        int L=Q[i].l;
        int R=Q[i].r;
 
        while(cur_l>L)  add(--cur_l);
        while(cur_r<R)  add(++cur_r);
 
        while(cur_l<L)  sub(cur_l++);
        while(cur_r>R)  sub(cur_r--);
 
        ans[Q[i].id]=get_ans(Q[i].k);
    }
}
 
int main()
{
    FAST
 
    int i,j,k,q,L,R;
 
    cin>>N>>q;
    for(i=1; i<=N; i++)
    {
        cin>>col[i];
    }
    for(i=1; i<N; i++)
    {
        int xx,yy;
        cin>>xx>>yy;
        adj[xx].push_back(yy);
        adj[yy].push_back(xx);
    }
    DFS(1, -1);
    for(i=0; i<q; i++)
    {
        cin>>j>>k;

        Q[i].id=i;
        Q[i].k=k;
        Q[i].l=in[j];
        Q[i].r=out[j];
    }
 
    MO(q);
 
    for(i=0; i<q; i++)
        cout<<ans[i]<<endl;
 
    return 0;
}
