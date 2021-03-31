#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
#define LOG 20

int arr[MAX];
int table[MAX][LOG+1];

//O(nLogn)
void buildSparseTable(int n)
{
	int i,j;
	for(i=0; i<n; i++)
		table[i][0]=arr[i];

	for(j=1; j<=LOG; j++)
	{
		for(i=0; i+(1<<j)<=n; i++)
		{
			table[i][j]=table[i][j-1]+table[i+(1<<(j-1))][j-1];
		}
	}
}
//O(logN)
long long getSum(int L, int R)
{
	long long sum=0LL;
	for(int j=LOG; j>=0; j--)
	{
		if((1<<j)<=R-L+1)
		{
			sum+=table[L][j];
			L+=(1<<j);
		}
	}
	return sum;
}

int main()
{
	int i,n,l,r,q;
	cin>>n;
	for(i=0; i<n; i++) cin>>arr[i];

	buildSparseTable(n);
	cin>>q;
	while(q--)
	{
		cin>>l>>r;
		cout<<getSum(l,r)<<endl;
	}
}
