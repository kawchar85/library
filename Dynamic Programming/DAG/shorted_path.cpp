//Shortest Path from 0 to n-1
#include<bits/stdc++.h>
using namespace std;
#defint ll long long
#define MAX 1003
#define inf INT_MAX

int w[MAX][MAX], DP[MAX], n;
//(n*n)
int f(int u)
{
    if(u==n-1)
        return 0;
    if(~DP[u]) return DP[u];
    int ans = inf;
    for(int v = 0; v<n; v++)
    {
        if(w[u][v]!=inf)
            ans= min(ans, f(v)+w[u][v]);
    }
    return DP[u]=ans;
}

void init()
{
    for(int i =0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            w[i][j]=inf;
        DP[i]=-1;
    }
}

int main()
{
    cin>>n;
    init();


    return 0;
}
