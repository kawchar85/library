#include<bits/stdc++.h>
using namespace std;

void minK(int a[], int n, int k)
{
	int st[n];
	int L=0,R=0,i,j;

	st[0]=0;
	for(i=1; i<k; i++)
	{
		while(L<=R && a[i]<a[st[R]]) R--;
		st[++R]=i;
	}
	cout<<"[0,"<<k-1<<"]-->"<<a[st[L]]<<endl; // ans for initial window
	for(i=k; i<n; i++)
	{
		if(st[L]==i-k) L++;
		while(L<=R && a[i]<a[st[R]]) R--;
		st[++R]=i;
		cout<<"["<<i-k+1<<","<<i<<"]-->"<<a[st[L]]<<endl;//ans for present window
	}
}

void minK2(int a[], int n, int k)
{
	int st[n];
	int L=0,R=0,i,j;

	st[0]=0;
	for(i=1; i<k-1; i++)
	{
		while(L<=R && a[i]<a[st[R]]) R--;
		st[++R]=i;
	}
	for(i=k-1; i<n; i++)
	{
		if(st[L]==i-k) L++;
		while(L<=R && a[i]<a[st[R]]) R--;
		st[++R]=i;
		cout<<"["<<i-k+1<<","<<i<<"]-->"<<a[st[L]]<<endl;//ans for present window
	}
}
int main()
{
	int a[]={2,1,4,5,3,4,1,2};
	int n=8;
	int k=4;
	minK2(a,n,k);
}