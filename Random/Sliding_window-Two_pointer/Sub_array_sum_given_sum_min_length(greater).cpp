/**
Given an array of positive integers, find a 
smallest sub-arry having sum greater than given sum.
*/

#include<bits/stdc++.h>
using namespace std;

void findSubArraySum(int arr[], int n, int sum)
{
	int cur_sum=0;
	int mn=INT_MAX;
	int start=-1;
	for(int L=0,R=0; R<n; R++)
	{
		cur_sum+=arr[R];

		while(cur_sum>sum)
		{
			if(mn>R-L+1)
			{
				mn=R-L+1;
				start=L;
			}
			cur_sum-=arr[L++];
		}
	}
	if(start==-1)	printf("no solution\n");
	else
	{
		printf("length=%d, [%d,%d]\n",mn,start,start+mn-1);
	}
}


int main()
{
	int a[8]={10,4,2,5,6,3,8,1};
	int sum=10;
	int n=8;
	findSubArraySum(a,n,sum);
}