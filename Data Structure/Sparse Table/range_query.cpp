/**
	You are given an array of N integers A[N]
	and Q queries. For each query, you must
	find the F() value within the segment A[l..r]

    Pre_cal: O(nLogn)
    Query: O(1)

    sum:
    ---
    F(x,y)=x+y;
    identity=0;

    muliplication:
    -------------
    F(x,y)=x*y;
    identity=1;

    min:
    F(x,y)=min(x,y);
    identity=INT_MAX;

    max:
    F(x,y)=max(x,y);
    identity=INT_MIN;

    gcd:
    F(x,y)=__gcd(x,y);
    identity=0;
*/

#include<bits/stdc++.h>
using namespace std;

#define MAX 1000000
#define MAXPOWN 1048576		// 2^(ceil(log_2(MAXN)))
#define MAXLEV 21			// ceil(log_2(MAXN)) + 1
#define identity 0

int N, levels;
int arr[MAX];
int dst[MAXPOWN][MAXLEV+1];

int F(int x, int y)
{
	return x+y;
}

//build(0, 0, N-1)
void build(int depth, int l, int r)
{
	if(l==r) return;

	int mid=(l+r)>>1;
	
	dst[mid][depth]=arr[mid];
	for(int i=mid-1; i>=l; i--)
	{
		dst[i][depth]=F(dst[i+1][depth], arr[i]);
	}

	if(mid+1<=r)
	{
		dst[mid+1][depth]=arr[mid+1];
		for(int i=mid+2; i<=r; i++)
			dst[i][depth]=F(dst[i-1][depth], arr[i]);
	}

	build(depth+1, l, mid);
	build(depth+1, mid+1, r);
}

//0-based
int query(int l, int r)
{
	if(l==r) return arr[l];
	unsigned int lvl = __builtin_clz(l^r) - levels -1;
	return F(dst[l][lvl], dst[r][lvl]);	
}

void pre_calculation(int n)
{
	//n-->size of arr[]
	levels=__builtin_clz(n);
	N= 1<<(31-levels);
	if(n!=N)
	{
		levels--;
		N<<=1;
	}

	while(n<N) arr[n++]=identity;
	build(0, 0, N-1);

}

int main()
{
	int n,q,l,r,i;
	cin>>n;
	for(i=0; i<n; i++) cin>>arr[i];
	pre_calculation(n);
	cin>>q;
	while(q--)
	{
		cin>>l>>r;
		cout<<query(l,r)<<endl;
	}

	return 0;
}
