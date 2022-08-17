//https://codeforces.com/contest/919/problem/B

#include <bits/stdc++.h>
using namespace std;
 
vector<int> num;
int DP[12][20][2][2];
 
int call(int pos, int sum, int small, int startHere)
{
    if(sum>10) return 0;
    if(pos==(int)num.size())
    {
        return sum==10;
    }
 
    if(~DP[pos][sum][small][startHere]) return DP[pos][sum][small][startHere];
 
    int res = 0;
    int LMT = small? 9 : num[pos];
 
    if(startHere)
    {
        res+=call(pos+1, 0, 1, 1);
    }
    for(int dgt=startHere; dgt<=LMT; dgt++)
    {
        res+= call(pos+1, sum+dgt, small|(dgt<num[pos]), 0);
    }
 
    return DP[pos][sum][small][startHere] = res;
}
int solve(int b)
{
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
    int k,ans=-1;
    scanf("%d",&k);
    int low=0, high=1e9,mid;
    while(low<=high)
    {
        mid=(low+high)/2;
        int x=solve(mid);
        if(x<k)
            low=mid+1;
        else
        {
            high=mid-1;
            if(x==k)
            {
                ans=mid;
                //break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
