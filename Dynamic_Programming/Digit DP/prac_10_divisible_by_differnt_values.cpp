/*
  https://www.hackerearth.com/problem/algorithm/sallu-bhai-and-ias-8838ac8d/
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
vector<int> A,B,val;
ll DP[14][2][2][2][2][2][2][2][2][2521][2][2];

//dp[current_pos][is present? flags for 2 to 9][reminder lcm(2..9)=2520][a is smaller than R][a is bigger than L]
ll call(int pos, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int r, int small, int big)
{
    if(pos==(int)B.size())
    {
        ll ok=1;
        if(p2 && (r%2)) ok=0;
        if(p3 && (r%3)) ok=0;
        if(p4 && (r%4)) ok=0;
        if(p5 && r%5) ok=0;
        if(p6 && r%6) ok=0;
        if(p7 && r%7) ok=0;
        if(p8 && r%8) ok=0;
        if(p9 && r%9) ok=0;
        
        return ok;
    }
 
    ll &res = DP[pos][p2][p3][p4][p5][p6][p7][p8][p9][r][small][big];
    if(~res) return res;
 
    res = 0;
    int start=A[pos], stop=B[pos];
    if(big) start=0;
    if(small) stop=9;
 
    for(int dgt=start; dgt<=stop; dgt++)
    {
        ll d=val[dgt];
        res+=call(pos+1, p2|(dgt==2), p3|(dgt==3), p4|(dgt==4), p5|(dgt==5), p6|(dgt==6), p7|(dgt==7), p8|(dgt==8), p9|(dgt==9), (r+d)%2520, small| dgt<B[pos], big |dgt>A[pos]);
    }
 
    return res;
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
    return call(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
 
int main ()
{   ll a,b,ans;
    val.push_back(0);
    for(ll i=1; i<10; i++)
    {
        ans=1;
        for(ll j=1; j<=i; j++)
            ans*=i;
        val.push_back(ans);
    }
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
