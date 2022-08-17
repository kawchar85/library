//https://codeforces.com/contest/296/problem/D

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
#define MAX 502
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

ll adj[MAX][MAX];
ll d[MAX][MAX];
ll ans[MAX];
bool vis[MAX];

void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN;
    string s;
    
    cin>>n;
    vl v(n);
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            cin>>adj[i][j];
    for(i=0; i<n; i++)
        cin>>v[i];
    for(x=n-1; x>=0; x--)
    {
        k=v[x];
        vis[k]=1;

        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                adj[i][j]=min(adj[i][j], adj[i][k]+adj[k][j]);

        sum=0;
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                if(vis[i] && vis[j])
                    sum+=adj[i][j];
        ans[x]=sum;
    }
    printa(ans, 0, n);

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
