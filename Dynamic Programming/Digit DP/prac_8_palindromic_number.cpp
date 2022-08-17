/*
    Given L,R. Find no of palindromic
    number in [L,R]

    https://vjudge.net/problem/LightOJ-1205
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<int> num;
ll DP[20][20][2][2][2];

ll call(int pos, int pos2, int small, int OutOfLimit, int startHere)
{
    if(pos>pos2)
    {
        if(OutOfLimit && !small) return 0; //seshe boro nichi, kintu 1st half a chuto nei ni
        return 1;
    }

    ll &res=DP[pos][pos2][small][OutOfLimit][startHere];
    if(~res) return res;

    res = 0;
    int LMT = small? 9 : num[pos];

    if(startHere)
    {
        res+=call(pos+1, pos2, 1, 0, 1); ///will start from next position, left digits are zero, small=true
    }
    
    for(int dgt=startHere; dgt<=LMT; dgt++)
    {
        if(dgt == num[pos2])
            res+= call(pos+1, pos2-1, small|(dgt<num[pos]), OutOfLimit, 0); //ageerta
        else
            res+= call(pos+1, pos2-1, small|(dgt<num[pos]), (dgt>num[pos2]), 0); //onno kuno pos a OOL hoye takle, tar cheye pos2 chuto. ai index a chuto dilei hoilo
    }

    return res;
}

ll solve(ll b)
{
    if(b<10) return b+1;
    num.clear();
    while(b>0)
    {
        num.push_back(b%10);
        b/=10;
    }
    reverse(num.begin(), num.end());

    memset(DP, -1, sizeof(DP));
    return call(0, num.size()-1, 0, 0, 1);
}

int main()
{
    int T,cs=1;
    ll a,b;
    scanf("%d",&T);
    for(cs=1; cs<=T; cs++)
    {
        scanf("%lld %lld",&a, &b);
        if(a>b) swap(a,b);
        ll ans = solve(b) - solve(a-1);
        printf("Case %d: %lld\n",cs, ans);
    }
    return 0;
}
