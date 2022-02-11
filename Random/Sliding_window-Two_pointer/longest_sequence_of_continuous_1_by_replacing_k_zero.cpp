/**
Given a binary array,find the maximum sequence
of continuous 1's that can be formed by replacing
atmost k zeros by ones.
*/

#include<bits/stdc++.h>
using namespace std;

void longestSequence(int arr[], int n, int k)
{
	int start=0,zero=0,mx=INT_MIN;

	for(int L=0, R=0; R<n; R++)
	{
		if(arr[R]==0) zero++;

		//make stable
		while(zero>k)
		{
			if(arr[L]==0)
				zero--;
			L++;
		}

		//stable, so try to update ans
		if(mx<R-L+1)
		{
			mx=R-L+1;
			start=L;
		}
	}

	printf("[%d,%d]\n",start, start+mx-1);
}

int main()
{
	//string s="ababca";
	int a[12]={1,1,0,1,1,0,1,1,1,1,0,0};
	int k=2;
	longestSequence(a,12,k);
}