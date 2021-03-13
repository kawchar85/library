//https://lightoj.com/problem/how-many-zeroes

#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> num;
ll DP[20][20][2][2];

ll call(int pos, int cnt, int small, int startHere)
{
    if(pos==(int)num.size())
    {
        return (ll)cnt;
    }

    if(~DP[pos][cnt][small][startHere]) return DP[pos][cnt][small][startHere];

    ll res = 0;
    int LMT = small? 9 : num[pos];

    if(startHere)
    {
        res+=call(pos+1, 0, 1, 1); ///will start from next position, left digits are zero, small=true
    }
    for(int dgt=startHere; dgt<=LMT; dgt++)
    {
        res+= call(pos+1, cnt+(dgt==0), small|(dgt<num[pos]), 0);
    }

    return DP[pos][cnt][small][startHere] = res;
}

ll solve(ll b)
{
    if(b<0) return -1LL; // considering 0

    num.clear();
    while(b>0)
    {
        num.push_back(b%10);
        b/=10;
    }
    reverse(num.begin(), num.end());

    memset(DP, -1, sizeof(DP));
    return call(0, 0, 0, 1);
}

int main ()
{
    int T,cs=1;
    ll n,m;
    scanf("%d",&T);
    for(cs=1; cs<=T; cs++)
    {
        scanf("%lld %lld",&m,&n);
        ll ans = solve(n)-solve(m-1);
        printf("Case %d: %lld\n",cs, ans);
    }
    return 0;
}
