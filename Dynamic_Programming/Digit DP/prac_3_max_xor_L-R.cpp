//https://codeforces.com/problemset/problem/276/D
/*
    You are given two integers l and r.
    Let's consider the values of  for 
    all pairs of integers a and b 
    (l ≤ a ≤ b ≤ r). Your task is to 
    find the maximum value among all
    considered ones.
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

vector<int> A,B;
ll DP[60][2][2][2][2];

//L to R er modde 2ta number a,b... maximize a^b

//DP[current_bit][a is lower than R][a is bigger than L][b is lower than R][b is bigger than L]
ll call(int pos, int smallA, int bigA, int smallB, int bigB)
{
    if(pos==(int)B.size())
        return 0;
 
    if(~DP[pos][smallA][bigA][smallB][bigB]) return DP[pos][smallA][bigA][smallB][bigB];
 
    ll res = 0;
    int startA = bigA? 0 : A[pos];
    int stopA = smallA? 1 : B[pos];
    int startB = bigB? 0 : A[pos];
    int stopB = smallB? 1 : B[pos];
 
    for(int i= startA; i<=stopB; i++)
    {
        for(int j= startB; j<=stopB; j++)
        {
            int x = i^j;
            ll add = 0;
            if(x) //ai bit 1 bananu jabe
            {
                add = (1LL<<(B.size()-pos-1)); //reverse kora chilo
            }
            res = max(res, add+call(pos+1, smallA| i< B[pos], bigA | i>A[pos], smallB| j< B[pos], bigB | j>A[pos]));
 
        }
    }
 
    return DP[pos][smallA][bigA][smallB][bigB] = res;
}
ll solve(ll a, ll b)
{
    A.clear();B.clear();
    while(b>0)
    {
        B.push_back(b%2);
        b/=2;
    }
    while(a>0)
    {
        A.push_back(a%2);
        a/=2;
    }
    while(A.size()<B.size())
        A.push_back(0);
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
 
    memset(DP, -1, sizeof(DP));
    return call(0, 0, 0, 0, 0);
}

void syntex_error()
{
    ll i,j,k,l,r,n,m,a,b,c,d,x,y,z;
    ll sum=0LL, mn=LLONG_MAX, mx=LLONG_MIN;
    vl v;
    string s;
    
    cin>>l>>r;
    cout<<solve(l,r)<<endl;
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
