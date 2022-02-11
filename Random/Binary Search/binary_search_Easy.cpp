#include<bits/stdc++.h>
using namespace std;
 
bool Search(int arr[], int n, int key)
{
	int id=0; //-1
	for(int jump=n; jump>0; jump/=2)
		while(id+jump<n && arr[id+jump]<=key) id+=jump;
	return arr[id]==key;
}

int Count(int arr[], int n, int key)
{
	int p=0;
	int q=0;
	for(int jump=n; jump>0; jump/=2)
	{
		while(p+jump<n && arr[p+jump]<key) p+=jump;
		while(q+jump<n && arr[q+jump]<=key) q+=jump;
	}
	return q-p;
}

int Upper(int arr[], int n, int key)
{
	int p=-1;
	for(int jump=n; jump>0; jump/=2)
	{
		while(p+jump<n && arr[p+jump]<=key) p+=jump;
	}
	return p+1;
}
int Lower(int arr[], int n, int key)
{
	int p=-1;
	for(int jump=n; jump>0; jump/=2)
	{
		while(p+jump<n && arr[p+jump]<key) p+=jump;
	}
	return p+1;
}
int main()
{
   	int a[5]={2,5,7,9,9};
   	bool f=Search(a, 1, 2);
   	if(f)
   	{
   		cout<<"YES"<<endl;
   	}
   	else
   	{
   		cout<<"NO"<<endl;
   	}
   	cout<<Count(a,5,9)<<endl;
   	cout<<Upper(a,5,9)<<endl;
   	cout<<Lower(a,5,9)<<endl;
    return 0;
}