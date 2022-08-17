#include<bits/stdc++.h>
using namespace std;
#define MAX 1000

int num[MAX],a[MAX],n,k;

//O(nCk)
void combination(int pos, int left)
{
	if(left> n-pos) return; // baki sob nileo K ta hobe na
	if(left==0) // K ta newa hoye gese
	{
		for(int i=0; i<k; i++)
			cout<<num[i]<<" ";
		cout<<"\n";
		return;
	}
	num[k-left]=a[pos];
	combination(pos+1, left-1); // a[pos] nibo
	combination(pos+1, left); // a[pos] nibo na
}


int main()
{
    
    cin>>n>>k;
    for(int i=0; i<n; i++)
    	cin>>a[i];
    combination(0, k);
 
    return 0;
}
