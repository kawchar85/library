#include<bits/stdc++.h>
using namespace std;
#define MAX 100001
#define ll long long


int a[MAX];

/**
Given a sequence of N integer numbers. At each step it is
allowed to increase the value of any number by 1 or to
decrease it by 1. The goal is to make the sequence
non-decreasing with the smallest number of steps.
For strictly increasing sequence
remove i from every a[i] and solve
the upper mentioned problem!

	a[i]-=i;
*/
//O(nlogn)
ll make1(int n)
{
	priority_queue<int>q;
 	ll ans=0;
 	q.push(a[1]);
 	for(int i=2; i<=n; i++)
 	{
 		q.push(a[i]);
 		if(q.top()>a[i])
 		{ 
 			ans+=q.top()-a[i];
 			q.pop();
 			q.push(a[i]);
 		}
 	}
 	return ans;
}
/**
Given a sequence of N integer numbers. At each step it is
allowed to select L,R and increase the value of a[i] by 1 L<=i<=R. The goal is to make the sequence
non-decreasing with the smallest number of steps.
*/
//O(n)
ll make2(int n)
{
	ll sum=0;
	for(int i=2; i<=n; i++)
	{
		sum+=max(0, a[i-1]-a[i]);
	}
	return sum;
}

int32_t main()
{
	int i,j,k,n,m;
 	cin>>n;
 	for(i=1;i<=n;i++) cin>>a[i];
 	
 	
 	cout<<make1(n)<<endl;
 	return 0;
}

/**
	
*/