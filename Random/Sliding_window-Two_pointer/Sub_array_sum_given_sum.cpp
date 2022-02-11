/**
Given an array of integers, find a sub-arry 
having given sum in it.
*/

#include<bits/stdc++.h>
using namespace std;

//only for positive number
void findSubArraySum(int arr[], int n, int sum)
{
	int cur_sum=0;
	for(int L=0,R=0; R<n; R++)
	{
		cur_sum+=arr[R];

		//make stable
		while(cur_sum>sum)
		{
			cur_sum-=arr[L++];
		}

		//check for ans
		if(cur_sum==sum)
		{
			printf("sub-arry found: [%d,%d]\n",L,R);
			return;
		}
	}
	printf("no solution\n");
}

//will work for +ve or -ve
void findSubArray(int arr[], int n, int sum)
{
	unordered_map<int,int> mp;
	mp.insert({0,-1});
	int cur_sum=0;

	for(int i=0; i<n; i++)
	{
		cur_sum+=arr[i];
		if(mp.find(cur_sum-sum)!=mp.end())
		{
			printf("sub-arry found: [%d,%d]\n",mp[cur_sum-sum],i);
			return;
		}
		mp.insert({cur_sum, i});
	}
}
int main()
{
	int a[8]={10,4,2,5,6,3,8,1};
	int sum=9;
	int n=8;
	findSubArraySum(a,n,sum);
}