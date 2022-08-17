/**
	go (0,0) to (n-1, m-1)
	with min cost.
	you can go Right or Down. 
*/
#include<bits/stdc++.h>
using namespace std;
#define INF 100000000
#define MAX 1000

#define ERROR 0

int a[MAX][MAX],n,m;
int dp[MAX][MAX];

int min_cost()
{
	int i,j;
	for(i=0; i<m; i++) dp[n][i]=INF;
	for(i=0; i<n; i++) dp[i][m]=INF;
	dp[n][m-1]=dp[n-1][m]=0;
	for(i=n-1; i>=0; i--)
	{
		for(j=m-1; j>=0; j--)
			dp[i][j]=a[i][j]+min(dp[i+1][j], dp[i][j+1]);
	}
	if(ERROR)
	for(i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
			cout<<dp[i][j]<<",";
		cout<<"\n";
	}
	return dp[0][0];
}
int main()
{
	cin>>n>>m;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			cin>>a[i][j];
		}
	}
	cout<<min_cost()<<endl;
	return 0;
}
