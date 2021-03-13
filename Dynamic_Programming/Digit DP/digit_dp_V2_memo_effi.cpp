/**
    Find the number of integers between [1, n]
    satisfying the following condition:
    The sum of the digits is a multiple of D
*/
#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll long long 

vector<int> num;
ll DP[20][100][2],d;

ll call(int pos, int sum, int flag)
{
    if(pos == (int)num.size())
        return sum%d==0;
    if(~DP[pos][sum][flag]) 
        return DP[pos][sum][flag];
    
    ll res = 0;
    for(int i = 0; i<10; i++)
    {
        if(flag && i==num[pos]) 
        {
            res = (res + call(pos+1, (sum+i)%d, 1))%MOD;
            break;
        }
        res = (res + call(pos+1, (sum+i)%d, 0))%MOD;
    }
 
    return DP[pos][sum][flag]=res;
}
ll solve(ll b)
{
    num.clear();
    while(b>0)
    {
        num.push_back(b%10);
        b/=10;
    }
    reverse(num.begin(), num.end());

    memset(DP, -1, sizeof(DP));
    return (MOD+call(0, 0, 1)-1)%MOD; //-1 for 0
}
/*
ll solve(string& s)
{
    num.clear();
    for(int i=0; i<s.size(); i++)
        num.push_back(s[i]-'0');
    memset(DP, -1, sizeof(DP));
    return (call(0, 0, 1)-1+MOD)%MOD;
}
*/
int main ()
{
    ll n;
    cin>>n>>d;
    cout<<solve(n)<<endl;
    return 0;
}
