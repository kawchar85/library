#include<bits/stdc++.h>
#define MAX 10001
using namespace std;

string A,B,ans="";
int dp[MAX][MAX],dir[MAX][MAX];

///O(n*m)
int LCS(int i, int j)
{
    if(i==A.size() || j==B.size())
        return 0;
    if(~dp[i][j]) return dp[i][j];
    if(A[i]==B[j])
    {
        dir[i][j]=1;
        return dp[i][j]=1+LCS(i+1, j+1);
    }
    int x=LCS(i,j+1);
    int y=LCS(i+1, j);
    if(x>=y)
    {
        dir[i][j]=2;
        dp[i][j]=x;
    }
    else
    {
        dir[i][j]=3;
        dp[i][j]=y;
    }
    return dp[i][j];
}

void solution(int i, int j)
{
    if(i==A.size() || j==B.size())
        return;
    if(dir[i][j]==1)
    {
        ans+=A[i];
        solution(i+1, j+1);
    }
    else if(dir[i][j]==2)
        solution(i,j+1);
    else
        solution(i+1, j);
}

int main()
{
    cin>>A>>B;
    memset(dp,-1,sizeof dp);
    int x = LCS(0,0);
    solution(0,0);
    cout<<"Length of LCS "<<x<<endl;
    cout<<"LCS is: "<<ans<<endl;
    return 0;
}

