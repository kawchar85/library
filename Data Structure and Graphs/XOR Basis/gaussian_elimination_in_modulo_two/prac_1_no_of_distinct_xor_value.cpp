/**
    Given a set S of size 1≤n≤10^5
    with elements 0≤ai<2^20. Find 
    the number of distinct integers
    that can be represented using 
    xor over the set of the given elements.

    sol:
    For any linear combination of the basis vectors,
    we get a different possible xor of some subset. 
    So, the answer would be 2^(size of basis)
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

    cout<<(1LL<<sz)<<endl;
    return 0;
}
