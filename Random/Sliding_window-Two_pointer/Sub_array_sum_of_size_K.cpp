/**
Given an array of integers, find minimum
sum sub-arry of size K.
*/

#include<bits/stdc++.h>
using namespace std;

void subArraySum(int arr[], int n, int k)
{
	int i,sum=0;
	int mn=INT_MAX;
	int start=0;
	//initial window
	for(i=0; i<k; i++)
		sum+=arr[i];

	mn=sum;
	for(i=k; i<n; i++)
	{
		sum-=arr[i-k];
		sum+=arr[i];

		if(sum<mn)
		{
			mn=sum;
			start=i-k+1;
		}
	}
	printf("sum=%d [%d,%d]\n",mn, start, start+k-1);
}

int main()
{
	int a[8]={10,4,2,5,6,3,8,1};
	int k=3;
	int n=8;
	subArraySum(a,n,k);
}