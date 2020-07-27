#include<bits/stdc++.h>
using namespace std;
#define MAX 10

int p[MAX],a[MAX],n;
bool used[MAX];

///O(n!)
void permutation(int pos)
{
	if(pos==n)
	{
		for(int i=0; i<n; i++)
			cout<<p[i]<<" ";
		cout<<"\n";
		return;
	}
	for(int i=0; i<n; i++)
	{
		if(used[i]) continue;
		used[i]=1;
		p[pos]=a[i];
		permutation(pos+1);
		used[i]=0;
	}
}

void permutation2()
{
	sort(a, a+n);
	do
	{
		for(int i = 0; i < n; ++i)
			cout<<a[i]<<" ";
		cout<<"\n";
	}
	while(next_permutation(a, a+n));
}
int main()
{
    
    cin>>n;
    for(int i=0; i<n; i++)
    	cin>>a[i];
    permutation(0);
    //permutation2();
 
    return 0;
}
