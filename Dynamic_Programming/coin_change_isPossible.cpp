/**
	n ta coin infinite ta kore dewa ache,
	tk bananu possible kina?
*/
#include<bits/stdc++.h>
using namespace std;
#define INF 10000000
#define MAX_tk 10000

bool dp[MAX_tk+5];
vector<int> coin;

string isPossible(int tk)
{
	memset(dp, 0, sizeof dp);
	dp[0]=1;

	for(int i=1; i<=tk; i++)
	{
		for(auto now : coin)
		{
			if(now<=i)
				dp[i]|=dp[i-now];
		}
	}
	return dp[tk] ? "YES" : "NO";
}
int main()
{
	int n,x,tk,i;
	cin>>n>>tk;
	for(i=0; i<n; i++)
	{
		cin>>x;
		coin.push_back(x);
	}
	cout<<isPossible(tk)<<endl;
}
