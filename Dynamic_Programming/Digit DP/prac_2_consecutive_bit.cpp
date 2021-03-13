//https://lightoj.com/problem/fast-bit-calculations
#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> num;
ll DP[40][40][2][2],k;

ll call(int pos, int cnt, int pre, int small)
{
    if(pos==(int)num.size())
    {
        return (ll)cnt;
    }

    if(~DP[pos][cnt][pre][small]) return DP[pos][cnt][pre][small];

    ll res = 0;
    int LMT = small? 1 : num[pos];

    for(int dgt=0; dgt<=LMT; dgt++)
    {
        res+= call(pos+1, cnt+(pre&&dgt), dgt, small|(dgt<num[pos]));
    }

    return DP[pos][cnt][pre][small] = res;
}

ll solve(ll b)
{
    num.clear();
    while(b>0)
    {
        num.push_back(b%2);
        b/=2;
    }
    reverse(num.begin(), num.end());

    memset(DP, -1, sizeof(DP));
    return call(0, 0, 0, 0);
}

int main ()
{
    int T,cs=1;
    ll n;
    scanf("%d",&T);
    for(cs=1; cs<=T; cs++)
    {
        scanf("%lld",&n);
        ll ans = solve(n);
        printf("Case %d: %lld\n",cs, ans);
    }
    return 0;
}
