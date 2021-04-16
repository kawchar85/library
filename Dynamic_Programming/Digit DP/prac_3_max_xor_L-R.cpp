/*
    You are given two integers l and r.
    find maximum value of a^b
    l<=a,b<=r
    https://codeforces.com/problemset/problem/276/D
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

vector<int> L,R;
ll dp[60][2][2][2][2];

//DP[current_bit][a is bigger than L][a is lower than R][b is bigger than L][b is lower than R]
//L to R er modde 2ta number a,b nibo... maximize a^b
ll call(int pos,int bigA,int smallA,int bigB,int smallB)
{
    if(pos==(int)R.size()) 
        return 0;

    ll &res=dp[pos][bigA][smallA][bigB][smallB];
    if(~res) return res;

    res=0;
    int startA = bigA? 0 : L[pos];
    int stopA = smallA? 1 : R[pos];
    int startB = bigB? 0 : L[pos];
    int stopB = smallB? 1 : R[pos];

    for(int i=startA; i<=stopA; i++)
    {
        for(int j=startB; j<=stopB; j++)
        {
            int x = i^j;
            ll add = 0;
            if(x) //ai bit 1 bananu jabe
                add = (1LL<<(R.size()-pos-1)); //reverse kora chilo
            res=max(res,add+call(pos+1, bigA|i>L[pos], smallA|i<R[pos], bigB|j>L[pos], smallB|j<R[pos]));
        }
    }
    return res;
}
ll solve(ll a, ll b)
{
    L.clear();R.clear();
    while(b>0)
    {
        R.push_back(b%2);
        b/=2;
    }
    while(a>0)
    {
        L.push_back(a%2);
        a/=2;
    }
    while(L.size()<R.size())
        L.push_back(0);
    reverse(L.begin(), L.end());
    reverse(R.begin(), R.end());
    
    memset(dp, -1, sizeof(dp));
    return call(0, 0, 0, 0, 0);
}
void syntex_error()
{
    ll l,r;
    
    cin>>l>>r;
    cout<<solve(l,r)<<endl;
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    //cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}
