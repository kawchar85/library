/***
	n ta coin 1ta kore dewa ache,
	tk kotho bhabe bananu jabe?
*/
#include<bits/stdc++.h>
using namespace std;
#define INF 10000000
#define MAX_tk 10000

int dp[MAX_tk+5];
vector<int> coin;

int way(int tk)
{
	memset(dp, 0, sizeof dp);
	dp[0]=1;

	for(int i=0; i<coin.size(); i++)
	{
		for(int j=tk; j>=coin[i]; j--)
		{
			dp[j]+=dp[j-coin[i]];
		}
	}
	return dp[tk];
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
	cout<<way(tk)<<endl;
}
