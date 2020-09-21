/**
    Make palindrom by inserting
    minimum char at any pos
    UVA:10453
*/
#include<bits/stdc++.h>
using namespace std;
#define MAX 1003

string s,ans;
int dp[MAX][MAX];

int MP(int i, int j)
{
    if(i>j) return 0;
    if(~dp[i][j]) return dp[i][j];
    if(s[i]==s[j]) return dp[i][j]=MP(i+1, j-1);
    return dp[i][j]=1+min(MP(i+1, j), MP(i, j-1));
}
void print(int i, int j)
{
    if(i>j) return;
    if(s[i]==s[j])
    {
        ans+=s[i];
        print(i+1, j-1);
        if(i!=j)
            ans+=s[i];
        return;
    }
    //if(dp[i][j]==1+MP(i+1, j))
    if(dp[i][j]==1+dp[i+1][j])
    {
        ans+=s[i];
        print(i+1, j);
        ans+=s[i];
    }
    else
    {
        ans+=s[j];
        print(i, j-1);
        ans+=s[j];
    }
    return;
}
int main()
{
    while(getline(cin,s))
    {
        memset(dp, -1, sizeof dp);
        ans="";
        int x = MP(0, (int)s.size()-1);
        print(0, (int)s.size()-1);
        cout<<x<<" "<<ans<<endl;

    }
    return 0;
}
