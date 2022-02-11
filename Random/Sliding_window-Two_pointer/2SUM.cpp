/**
Given a sorted array  A,  having  
N  integers. You need to find any
pair (i,j)  having sum as given number  X .
*/

#include<bits/stdc++.h>
using namespace std;

//O(n)
bool TwoSUM(int A[], int n, int sum)
{
	int L=0, R=n-1;
	while(L<R)
	{
		if(A[L]+A[R]==sum) return 1;
		else if(A[L]+A[R]>sum) R--;
		else L++;
	}
	return 0;
}

int main()
{
	int a[]={1,2,3,4,5};
	int n=5;
	int sum=150;
	if(TwoSUM(a,n,sum)) cout<<"YES\n";
	else cout<<"NO"<<endl;
}