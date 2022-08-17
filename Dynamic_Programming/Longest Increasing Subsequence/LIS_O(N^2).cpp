#include<bits/stdc++.h>
#define MAX 10004
using namespace std;

int dp[MAX],dir[MAX],value[MAX],n,start;

///Longest length from u (index)
int longest(int u)
{
    if(~dp[u]) return dp[u];

    int mx=0;
    for(int v=u+1; v<n; v++)
    {
        if(value[v]>value[u])
        {
            int x=longest(v);
            if(x>mx)
            {
                mx=x;
                dir[u]=v;
            }
        }
    }
    return dp[u]=1+mx;
}

void print_solution(int start)
{
    while(~start)
    {
        cout<<value[start]<<" ";
        start=dir[start];
    }
}

///O(n*n)
int findLIS()
{
    int lis=0,x;
    memset(dir,-1,sizeof dir);
    memset(dp,-1,sizeof dp);
    for(int i=0; i<n; i++)
    {
        x=longest(i);
        if(x>lis)
        {
            lis=x;
            start=i;
        }
    }
    return lis;
}
int main()
{
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>value[i];
    cout<<"LIS : "<<findLIS()<<endl;
    print_solution(start);

}

