/**
Given an array and an integer K, find the
count of distinct elements in every sub-array
of size K.
*/

#include<bits/stdc++.h>
using namespace std;

#define MAX 10004

void distinctCount(int arr[], int n, int k)
{
	int cnt[MAX]={0};
	int distinct=0;

	for(int i=0; i<n; i++)
	{
		if(i>=k)
		{
			if(--cnt[arr[i-k]]==0)
				distinct--;
		}
		cnt[arr[i]]++;
		if(cnt[arr[i]]==1)
			distinct++;
		if(i>k-2)
		{
			cout<<"["<<i-k+1<<","<<i<<"] --> "<<distinct<<endl;
		}
	}
}
int main()
{
	int a[]={1,1,2,1,3};
	int n=5;
	int k=3;

	distinctCount(a,n,k);
}