#include<bits/stdc++.h>
#define MAX 3003
using namespace std;

int dp[MAX][MAX];
char A[MAX], B[MAX];
void printLCS(int i, int j)
{
    if(i==0 || j==0) return;
    if(A[i]==B[j])
    {
        printLCS(i-1, j-1);
        putchar(A[i]);
    }
    else if(dp[i-1][j] >= dp[i][j-1])
        printLCS(i-1, j);
    else
        printLCS(i, j-1);
}
int main()
{
    scanf("%s", A+1);
    scanf("%s", B+1);
    int n = strlen(A+1);
    int m = strlen(B+1);
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            if(A[i]==B[j])
                dp[i][j]=1+dp[i-1][j-1];
            else
                dp[i][j]=max(dp[i][j-1], dp[i-1][j]);
        }
    }
    printLCS(n, m);
    puts("");
    return 0;
}
