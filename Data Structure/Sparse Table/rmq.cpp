#include<bits/stdc++.h>
using namespace std;

#define MAX 100005
#define LOG 20

int logs[MAX];
int arr[MAX];
int table[MAX][LOG+1];

void cal_log(int n)
{
	logs[1]=0;
	for(int i=2; i<=n; i++)
	{
		logs[i]=logs[i/2]+1;
	}
}

//O(nLogn)
void buildSparseTable(int n)
{
	cal_log(n);
	int i,j;
	for(i=0; i<n; i++)
		table[i][0]=arr[i];

	for(j=1; j<=LOG; j++)
	{
		for(i=0; i+(1<<j)<=n; i++)
		{
			table[i][j]=min(table[i][j-1], table[i+(1<<(j-1))][j-1]);
		}
	}
}
//O(1)
int query(int L, int R)
{
	int j=logs[R-L+1];
	return min(table[L][j], table[R-(1<<j)+1][j]);
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
		cout<<query(l,r)<<endl;
	}
}
