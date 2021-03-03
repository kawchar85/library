#include<bits/stdc++.h>
#define MAX 100005

int tree[2*MAX],N;

void build(int n)
{
	N=n;
	for(int i=N-1; i>0; --i)
		tree[i]=tree[i<<1]+tree[i<<1|1];
}

void modify(int p, int val) //arr[p]=val
{
	for(tree[p+=N]=val; p>1; p>>=1)
		tree[p>>1]=tree[p]+tree[p^1];
}

//[l,r)
int query(int l, int r)
{
	int res=0;
	for(l+=N,r+=N; l<r; l>>=1, r>>=1)
	{
		if(l&1) res+=tree[l++];
		if(r&1) res+=tree[--r];
	}
	return res;
}
void modify(int l, int r, int val)
{
	for(l+=N,r+=N; l<r; l>>=1,r>>=1)
	{
		if(l&1) tree[l++]+=val;
		if(r&1) tree[--r]+=val;
	}
}
//access single element after modification on interval
int valueAt(int p)
{
	int res=0;
	for(p+=N; p>0; p>>=1)
		res+=tree[p];
	return res;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; ++i)
		scanf("%d", tree+n+i);
	build(n);
	modify(0,1);
	printf("%d\n", query(0,5));
}
