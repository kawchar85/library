#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

//{n,n+1}
pii fib(int n)
{
	if(n==0) return {0,1};
	pii p = fib(n>>1);
	int a = p.first*(2*p.second-p.first);
	int b = p.first*p.first+p.second*p.second;
	if(n&1) return {b, b+a};
	else return {a,b};
}

int main()
{
	pii p=fib(9);
	cout<<p.first<<" "<<p.second<<endl;
}
