/**
    UVA-11517
    make taka>=total using minimum coin
*/
#include<bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define endl "\n"

#define MAX 10004
#define INF 100000
 
typedef long long ll;
typedef vector<ll> vl;
typedef vector<int> vi;

int dp[102][MAX];
int coin[102];
int total,pay,cnt,n;

int solve(int i, int tk)
{
    if(tk>=total) return tk;
    if(i==n) return INT_MAX;
    if(~dp[i][tk])
        return dp[i][tk];
    return dp[i][tk]=min(solve(i+1, tk), solve(i+1, tk+coin[i]));
}

int coins(int i, int taka)
{
    if(taka==0)
        return 0;
    if(taka<0 || i==n)
        return INF;
    if(~dp[i][taka])
        return dp[i][taka];
    return dp[i][taka]=min(1+coins(i+1,taka-coin[i]),coins(i+1,taka));
}
void solveTest()
{
    pay=cnt=INT_MAX;

    cin>>total>>n;
    for(int i=0; i<n; ++i)
    {
        cin>>coin[i];
    }
    
    memset(dp, -1, sizeof dp);
    pay=solve(0,0);
    memset(dp, -1, sizeof dp);
    cnt=coins(0,pay);
    cout<<pay<<" "<<cnt<<endl;
}
 
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    ll T=1;
    cin>>T;
    while(T--) solveTest();

    return 0;
}
