//https://codeforces.com/contest/86/problem/D

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
#define MAX 200005
 
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
 
#define B_SIZE 450 ///sqrt(MAX)
 
struct query{
    int l,r,id;
};
query Q[MAX];
int ar[MAX], fre[1000006];
ll power=0LL, ans[MAX];
 
bool cmp(query a, query b)
{
    if(a.l/B_SIZE==b.l/B_SIZE)
        return a.r<b.r;
    return a.l/B_SIZE < b.l/B_SIZE;
}
void add(int pos)
{
    int pre=fre[ar[pos]];
    int now=pre+1;
    fre[ar[pos]]++;
    power-=1LL*pre*pre*ar[pos];
    power+=1LL*now*now*ar[pos];
 
}
void sub(int pos)
{
    int pre=fre[ar[pos]];
    int now=pre-1;
    fre[ar[pos]]--;
    power-=1LL*pre*pre*ar[pos];
    power+=1LL*now*now*ar[pos];
}
ll get_ans()
{
    return power;
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
    FAST
 
    int i,j,n,q,L,R;
 
    cin>>n>>q;
    for(i=0; i<n; i++)
    {
        cin>>ar[i];
    }
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
