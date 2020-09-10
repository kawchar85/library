/***
    n ta coin infine ta kore dewa ache,
    minimum koyta coin diye tk bananu jabe?
*/
#include<bits/stdc++.h>
using namespace std;
#define INF 10000000
#define MAX_tk 10000

int dp[MAX_tk+5];
int use[MAX_tk+5];
vector<int> coin;

int min_coin(int tk)
{
    int i,mn;
    for(i=1; i<=tk; i++)
        dp[i]=INF;
    dp[0]=0;

    for(i=1; i<=tk; i++)
    {
        dp[i]=INF;
        for(auto now : coin)
        {
            if(now<=i)
            {
                if(1+dp[i-now]<dp[i])
                {
                    dp[i]=1+dp[i-now];
                    use[i]=now;
                }
            }
        }
    }
    cout<<"coins: ";
    int n=tk;
    while(n>0)
    {
        cout<<use[n]<<" ";
        n-=use[n];
    }
    cout<<endl;
    return dp[tk]==INF? -1: dp[tk];
}
int main()
{
    int n,x,tk,i;
    cin>>n>>tk;
    for(i=0; i<n; i++)
    {
        cin>>x;
        coin.push_back(x);
    }
    cout<<min_coin(tk)<<endl;
}
