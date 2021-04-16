/**
    the number of integers in the 
    range [A, B] which are divisible
    by K and the sum of its digits is
    also divisible by K.

    https://vjudge.net/problem/LightOJ-1068
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> num;
ll DP[12][92][92][2][2],k;

//small-->MSB er kuno digit chuto nisi kina
ll call(int pos, int rem, int sum, int small, int startHere)
{
    if(pos==(int)num.size())
    {
        if(!sum && !rem) return 1LL;
        return 0LL;
    }

    if(~DP[pos][rem][sum][small][startHere]) return DP[pos][rem][sum][small][startHere];

    ll res = 0;
    int LMT = small? 9 : num[pos];

    if(startHere)
    {
        res+=call(pos+1, 0, 0, 1, 1); ///will start from next position, left digits are zero, small=true
    }
    for(int dgt=startHere; dgt<=LMT; dgt++)
    {
        res+= call(pos+1, (rem*10+dgt)%k, (sum+dgt)%k, small|(dgt<num[pos]), 0);
    }

    return DP[pos][rem][sum][small][startHere] = res;
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
    return call(0, 0, 0, 0,1);
}

int main ()
{
    int T,cs=1;
    ll n,m;
    scanf("%d",&T);
    for(cs=1; cs<=T; cs++)
    {
        scanf("%lld %lld %lld",&m,&n, &k);
        if(k>90)
        {
            printf("Case %d: 0\n",cs);
            continue;
        }
        ll ans = solve(n)-solve(m-1);
        printf("Case %d: %lld\n",cs, ans);
    }
    return 0;
}
