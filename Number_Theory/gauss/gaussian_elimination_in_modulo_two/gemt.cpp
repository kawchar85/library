/**
	->A set of vectors is called a basis of a vector space, if all of the element vectors of that space can be written uniquely as the sum of a linear combination of elements of that basis
	->The basis is actually the smallest sized set such that all other vectors in the vector space are representable by a linear combination of just the element vectors of that set.
	->For a d−dimensional vector space, it's basis can have at most d vector elements.
	->For any linear combination of the basis vectors, we get a different possible xor of some subset
*/

#include <bits/stdc++.h> 
using namespace std;
#define ll long long

#define getbit(n,i) ((n>>i)&1)
const int LOG_A=20;//Dimension

ll basis[LOG_A];
int sz;

void addVector(ll mask)
{
	//for(int i=LOG_A-1; ~i; i--)
	for(int i=0; i<LOG_A; i++)
	{
		if(!getbit(mask, i)) continue;

		if(!basis[i])
		{
			basis[i]=mask;
			sz++;
			return;
		}
		mask^=basis[i];
	}
}
void clearSpace()
{
	sz=0;
	memset(basis, 0, sizeof(basis));
}

int main()
{
	int n;
	cin >> n;

	while(n--)
	{
		ll a;
		scanf("%lld", &a);

		addVector(a);
	}

	for(int i=0; i<LOG_A; i++)
	{
		if(basis[i])
			cout<<basis[i]<<" ";
	}
	cout<<endl;
	return 0;
}
