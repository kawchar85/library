///minimum coin
#include<bits/stdc++.h>
#define MAX 10000
#define INF 1000000
using namespace std;
#define N 5
int coin[N]={1,5,10,25,50},DP[N][MAX];

///O(i*tk)
int solve(int i, int taka)
{
    if(taka==0)
        return 0;
    if(taka<0 || i>=N)
        return INF;
    if(DP[i][taka]!=-1)
        return DP[i][taka];
    return DP[i][taka]=min(1+solve(i,taka-coin[i]),solve(i+1,taka));
}
int main()
{
    memset(DP,-1,sizeof DP);
    int tk;
    while(~scanf("%d",&tk))
    {
        printf("%d\n",solve(0,tk));
    }
    return 0;
}
