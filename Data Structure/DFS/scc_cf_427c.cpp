//https://codeforces.com/contest/427/problem/C
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
#define DEBUG 1

#define dbg(x) if(DEBUG) cout<<"Line "<<__LINE__<<": "<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;

bool vis[MAX];
int Time,dis[MAX],fin[MAX];
vector<int>adj[MAX],adjR[MAX],ans;
vector< pair<int,int> >order;
int cost[MAX];

void DFS(int n)
{
    vis[n]=1;
    dis[n]=++Time;
    for(auto x : adj[n])
    {
        if(vis[x]) continue;
        DFS(x);
    }
    fin[n]=++Time;
    order.push_back({fin[n],n});
}

void DFS2(int n)
{
    vis[n]=1;
    ans.pb(cost[n]);
    for(auto x: adjR[n])
    {
        if(vis[x]) continue;
        DFS2(x);
    }
}
void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN;
    vl v;
    string s;
    
    cin>>n;
    for(i=1; i<=n; i++)
        cin>>cost[i];
    cin>>m;
    for(i=0; i<m; i++)
    {
        cin>>x>>y;
        adj[x].pb(y);
        adjR[y].pb(x);
    }
    memset(vis,0,sizeof vis);
    for(i=1; i<=n; i++)
        if(!vis[i])
            DFS(i);
    sort(order.rbegin(), order.rend());
    memset(vis,0,sizeof vis);

    ll way=1LL;
    for(auto k : order)
    {
        if(!vis[k.second])
        {
            ans.clear();
            DFS2(k.second);
            //dbg(SZ(ans));
            ll cnt=0LL;
            mn=LLONG_MAX;
            for(auto K : ans)
            {
                if(K == mn)
                    cnt++;
                else if(K<mn)
                {
                    mn=K;
                    cnt=1LL;
                }
            }

            sum+=mn;
            way=(way*cnt)%MOD;
        }
    }
    
    cout<<sum<<" "<<way<<endl;
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
