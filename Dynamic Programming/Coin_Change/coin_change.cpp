///how many way?
//1+2+1, 1+1+2 are same

#include<bits/stdc++.h>
#define MAX 10000
using namespace std;
int N 5
int coin[N]={1,5,10,25,50},DP[N][MAX];


///O(i*tk)
int solve(int i, int taka)
{
    if(taka<0 || i>4)
        return 0;
    if(taka==0)
        return 1;
    if(DP[i][taka]!=-1)
        return DP[i][taka];
    return DP[i][taka]=solve(i,taka-coin[i])+solve(i+1,taka);
}
int32_t main()
{
    memset(DP,-1,sizeof DP);
    int n;
    while(~scanf("%d",&n))
    {
        printf("%d\n",solve(0,n));
    }
    return 0;
}
