//https://lightoj.com/problem/snakes-and-ladders

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
#define MAX 202
#define DEBUG 0
#define EPS 1e-9

#define dbg(x) if(DEBUG) cout<<(#x)<<"="<<(x)<<":\n"
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


ll go[MAX];
typedef long double ld;

/**
    return 1--> unique sol
    return 0--> 0/inf sol (singular system)
    n--> no of eqn
    O(N^3)
*/
bool zero(ld x) { return fabs(x)<EPS;}
ld mat[MAX][MAX];
ld con[MAX];

void print(int n)
{
    int i,j;
    cout<<"-------------------\n";
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++){
            if(zero(mat[i][j])) mat[i][j]=0;
            cout<<mat[i][j]<<" ";
        }
        cout<<"| "<<con[i]<<endl;
    }
    cout<<"-------------------\n";
}
bool Gaussian_Elimination(int n)
{
    int i,j,k,pivot;

    for(i=1; i<=n; i++)
    {
        //find non-zero pivot
        pivot=-1;
        for(j=i; j<=n; j++)
        {
            if(!zero(mat[j][i]))
            {
                pivot=j;
                break;
            }
        }

        if(pivot==-1) return 0; //singular system
        if(pivot != i) //need pivoting
        {
            for(j=i; j<=n; j++)
                swap(mat[i][j], mat[pivot][j]);
            swap(con[i], con[pivot]);
        }

        //normalization
        ld x=mat[i][i];
        for(j=1; j<=n; j++)
            mat[i][j]/=x;
        con[i]/=x;


        //forward elimination
        for(j=1; j<=n; j++)
        {
            if(j==i) continue;//pivot

            ld factor=mat[j][i]/mat[i][i];
            for(k=i; k<=n; k++)
            {
                mat[j][k]-=factor*mat[i][k];
            }
            con[j]-=factor*con[i];
        }
        //print(n);
    }

    //print(n);
    return 1;
}
void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN, cnt=0LL;
    vl v;
    string s;
    
    cin>>n;
    for(i=0; i<=100; i++)
        go[i]=i;
    for(i=0; i<n; i++)
    {
        cin>>x>>y;
        go[x]=y;
    }
    for(i=1; i<=100; i++)
    {
        if(go[i]==i)
        {
            x=0;
            for(j=1; j<=6 && (i+j)<=100; j++)
            {
                x++;
                mat[i][i+j]=-1;
            }
            mat[i][i]=x;
            con[i]=6;
        }
        else
        {
            mat[i][i]=1;
            mat[i][go[i]]=-1;
            con[i]=0;
        }
    }
    
    Gaussian_Elimination(100);
    cout<<fixed<<setprecision(10)<<con[1]<<endl;
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        CS(cs++);
        syntex_error();
    }

    return 0;
}
