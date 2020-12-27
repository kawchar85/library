/**
    https://codeforces.com/gym/309194/problem/I
    Knapsack+Bicoloring
    x-y cheat korle akta ke odd, onnotake
    even pos a rakhbo
*/

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
#define MAX 10004

#define dbg(x) cout<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "

#define ll int
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;

vl adj[MAX];
bool error=0;
ll col[MAX];
ll grp[MAX];
ll odd[MAX];
ll even[MAX];
ll no=1;
ll n;
ll dp[MAX][MAX/2];
ll final[MAX];

void DFS(ll u, ll c=0)
{
    if(error) return;

    col[u]=c;
    grp[u]=no;
    if(c) odd[no]++;
    else even[no]++;

    for(auto v: adj[u])
    {
        if(col[v]==c)
        {
            error=1;
            return;
        }
        if(col[v]==-1)
            DFS(v,c^1);
    }
}

ll solve(ll pos, ll total)
{
    if(pos==no)
        return total==(n/2);
    if(total>(n/2))
        return 0;
    if(~dp[pos][total])
        return dp[pos][total];
    ll x=solve(pos+1, total+odd[pos]);
    ll y=solve(pos+1, total+even[pos]);
    return dp[pos][total]=max(x,y);
}
void finally(ll pos, ll total)
{
    if(pos==no)
        return;
    if(solve(pos+1,total+odd[pos]))
    {
        final[pos]=1; //pos grp er odd ghula nibo
        finally(pos+1, total+odd[pos]);
    }
    else
    {
        final[pos]=0; //pos grp er evn ghula nibo
        finally(pos+1, total+even[pos]);
    }
}

void syntex_error()
{
    ll i,j,k,l,r,m,a,b,c,x,y,z,sum=0;
    
    cin>>n>>m;
    if(n&1 && m)
    {
        cout<<-1<<endl;
        return;
    }
    if(!m)
    {
        for(i=1; i<=n; i++)
            cout<<i<<" ";
        return;
    }

    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    
    clean(col, -1);
    clean(dp, -1);
    for(i=1; i<=n; i++)
    {
        if(col[i]==-1)
        {
            DFS(i);
            no++;
        }
    }
    if(error)
    {
        cout<<-1<<endl;
        return;
    }
    if(!solve(0,0))
    {
        cout<<-1<<endl;
        return;
    }

    finally(0,0);
    vl ans[2];
    for(i=1; i<=n; i++)
    {
        x=final[grp[i]];//i jei grp a, tar odd/even col nibo ans[0] te?
        if(x==col[i])
            ans[0].pb(i);
        else
            ans[1].pb(i);
    }

    //printv(ans[0]);printv(ans[1]);
    for(i=0; i<(n/2); i++)
        cout<<ans[0][i]<<" "<<ans[1][i]<<" ";

    
}

int main()
{
    FAST
    
    ll TC=1;

    //cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}
