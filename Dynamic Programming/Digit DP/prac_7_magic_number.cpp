/**
    https://codeforces.com/contest/628/problem/D
*/
#include<bits/stdc++.h>
using namespace std;

#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 2003
typedef long long ll;

ll DP[MAX][MAX][2][2];
ll m,d;
string a,b;

//dp[current_pos][reminder][is_smaller_than_R][is_ bigger_than_L]
ll solve(int pos, int rem, int small, int big)
{
    if(pos==(int)a.size())
    {
        return !rem;
    }

    ll &res = DP[pos][rem][small][big];
    if(~res) return res;

    res=0;
    int start=a[pos]-'0', stop=b[pos]-'0';
    if(big) start=0;
    if(small) stop=9;

    for(int dgt=start; dgt<=stop; dgt++)
    {
        if(pos&1 && dgt!=d) continue;
        if((pos&1) ==0 && dgt==d) continue;
        res+=solve(pos+1, (rem*10+dgt)%m, small| dgt<(b[pos]-'0'), big | dgt>(a[pos]-'0'));
        if(res>=MOD) res%=MOD;
    }

    return res;
}

int main ()
{
    FAST

    cin>>m>>d>>a>>b;
    clean(DP, -1)
    cout<<solve(0, 0, 0, 0)<<endl;

    return 0;
}
