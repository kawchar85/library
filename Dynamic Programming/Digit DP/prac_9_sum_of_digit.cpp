/**
    calculate the digit sum of [a,b]
        0<=a<=b<=10^15
    https://www.spoj.com/problems/PR003004/
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
vector<int> A,B;
ll DP[20][150][2][2];
 
ll call(int pos, int sum, int small, int big)
{
    if(pos==(int)B.size())
    {
        return (ll)sum;
    }
 
    if(~DP[pos][sum][small][big]) return DP[pos][sum][small][big];
 
    ll res = 0;
    int start=A[pos], stop=B[pos];
    if(big) start=0;
    if(small) stop=9;
 
    for(int dgt=start; dgt<=stop; dgt++)
    {
        res+=call(pos+1, sum+dgt, small| dgt<B[pos], big |dgt>A[pos]);
    }
 
    return DP[pos][sum][small][big] = res;
}
ll solve(ll a, ll b)
{
    A.clear();B.clear();
    while(b>0)
    {
        B.push_back(b%10);
        b/=10;
    }
    while(a>0)
    {
        A.push_back(a%10);
        a/=10;
    }
    while(A.size()<B.size())
        A.push_back(0);
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
 
    memset(DP, -1, sizeof(DP));
    return call(0, 0, 0, 0);
}
 
int main ()
{
    ll a,b,ans;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld %lld",&a,&b);
        ans=solve(a,b);
        printf("%lld\n",ans);
    }
    return 0;
}
 
