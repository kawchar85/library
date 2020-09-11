
//CF: 463D
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
#define MAX 1005

#define dbg(x) cout<<(#x)<<"="<<(x)<<":\n"
#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector< pii > vpi;
typedef vector< pll > vpl;
typedef map<int, int> mii;
typedef map<ll, ll> mll;

ll A[10][MAX];
ll index[10][MAX];
ll n,k;
ll dp[MAX][2];

bool valid(ll now, ll next)
{
    for(int i=0; i<k; i++)
    {
        if(index[i][now]>index[i][next])
            return 0;
    }
    return 1;
}
ll solve(ll pos, bool start)
{
    if(pos==n)
        return 0LL;
    if(~dp[pos][start])
        return dp[pos][start];
    ll ret=0LL;
    ll now,next;

    now=A[0][pos];
    for(ll i=pos+1; i<n; i++)
    {
        next=A[0][i];
        if(valid(now, next))
            ret=max(ret, solve(i, 1));
    }
    ret++;
    if(!start)
        ret=max(ret, solve(pos+1, 0));
    //cout<<pos<<" : "<<ret<<endl;
    return dp[pos][start]=ret;

}
void syntex_error()
{
    ll i,j,l,r,m,a,b,c,x,y,z,sum=0LL;
    
    cin>>n>>k;

    for(j=0; j<k; j++)
    {
        for(i=0; i<n; i++)
        {
            cin>>A[j][i];
            index[j][A[j][i]]=i;
        }
    }

    clean(dp, -1);
    cout<<solve(0,0)<<endl;

}

int main()
{
    FAST
    
    ll TC=1LL;

    //cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}
