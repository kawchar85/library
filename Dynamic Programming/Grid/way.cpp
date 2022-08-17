/**
    Total way to go from (0,0)
    to (n-1, m-1), '#' means wall
    dir: right or down
*/
#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define MAX 1003
#define ll long long 

int n,m;
ll dp[MAX][MAX];
string s[MAX];

ll solve(int i, int j)
{
    if(i>=n || j>=m || s[i][j]=='#') return 0;
    if(i+1==n && j+1==m) return 1LL;
    if(~dp[i][j]) return dp[i][j];
    return dp[i][j]=(solve(i+1, j)+solve(i, j+1))%MOD;
}

int main()
{
    cin>>n>>m;
    for(int i=0; i<n; i++)
    {
        cin>>s[i];
    }
    memset(dp, -1, sizeof dp);
    cout<<solve(0,0)<<endl;
    return 0;
}
