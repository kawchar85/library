/*
    You are given two integers l and r.
    how many pairs of integers (a,b) 
    satisfy the following conditions:
    a+b=a^b
    l<=a,b<=r

    sol:
    a+b=a^b + 2*(a&b)
    that is a&b=0.
    so, count no of pairs s.t a&b==0

    https://codeforces.com/contest/1245/problem/F
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

vector<int> L,R;
ll dp[32][2][2][2][2];

//DP[current_bit][a is bigger than L][a is lower than R][b is bigger than L][b is lower than R]
ll call(int pos,int bigA,int smallA,int bigB,int smallB)
{
    if(pos==(int)R.size()) 
        return 1;

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
            if(i&j) continue;//i=j=1 hole ai bit 1 hoye jabe
            res+=call(pos+1, bigA|i>L[pos], smallA|i<R[pos], bigB|j>L[pos], smallB|j<R[pos]);
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

    cin>>TC;

    while(TC--){
        syntex_error();
    }

    return 0;
}
