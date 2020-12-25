#include<bits/stdc++.h>
using namespace std;

#define MAX 100

int dp[MAX][MAX];
string A,B;

int getLCS(int n, int m)
{
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=m; j++)
		{
			if(A[i-1]==B[j-1])
				dp[i][j]=1+dp[i-1][j-1];
			else
				dp[i][j]=max(dp[i-1][j], dp[i][j-1]);
		}
	}

	return dp[n][m];
}


set<string> findALL(int i, int j)
{
	set<string> st,st2;

	if(i==0 || j==0)
	{
		st2.insert("");
		return st2;
	}

	if(A[i-1]==B[j-1])
	{
		st=findALL(i-1, j-1);

		for(string s : st)
		{
			s+=A[i-1];
			st2.insert(s);
		}
		return st2;
	}

	if(dp[i-1][j]>dp[i][j-1])
		return findALL(i-1, j);

	if(dp[i-1][j]<dp[i][j-1])
		return findALL(i, j-1);

	//multiple possible
	st=findALL(i-1,j);
	st2=findALL(i, j-1);

	for(string s : st)
		st2.insert(s);
	return st2;

}
int main()
{
	cin>>A>>B;
	int n=A.size();
	int m=B.size();
	cout<<getLCS(n,m)<<endl;

	set<string> all = findALL(n,m);
	for(auto s : all)
		cout<<s<<"\n";
}
