#include<bits/stdc++.h>
#define MAX 505
using namespace std;

int A[MAX], B[MAX];
short dp[MAX][MAX][MAX], n, m;

short LCS(short i, short j, short last)
{
    if(i>n || j>m)
        return 0;
    if(~dp[i][j][last]) return dp[i][j][last];

    short x=LCS(i,j+1, last);
    short y=LCS(i+1, j, last);
    short z=(A[i]==B[j] && A[i]>A[last])? 1+LCS(i+1, j+1, i) : 0;

    return dp[i][j][last]=max({x,y,z});
}

void solution(short i, short j, short last, short lcs)
{
    if(i>n || j>m)
        return;

    if(LCS(i, j+1, last)==lcs)
        solution(i,j+1, last, lcs);
    else if(LCS(i+1, j, last)==lcs)
        solution(i+1, j, last, lcs);
    else
    {
        printf("%d ",A[i]);
        solution(i+1, j+1, i, lcs-1);
    }
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);

    scanf("%hd",&n);
    A[0]=B[0]=INT_MIN;
    for(short i=0; i<n; i++)
    {
        scanf("%d",&A[i+1]);
    }
    scanf("%hd",&m);
    for(short i=0; i<m; i++)
    {
        scanf("%d",&B[i+1]);
    }
    memset(dp,-1,sizeof dp);
    short y=LCS(1, 1, 0);
    printf("%hd\n",y);
    solution(1, 1, 0, y);

    return 0;
}

