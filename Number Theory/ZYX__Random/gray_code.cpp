#include<bits/stdc++.h>
using namespace std;

//Gray code is a binary numeral system
//where two successive values differ in only one bit.

int G(int n)
{
	return n^(n>>1);
}

int rev_g (int g)
{
  int n = 0;
  for( ; g; g >>= 1)
    n^= g;
  return n;
}

int main()
{
	int n=6;
	cout<<G(n)<<" "<<rev_g(G(n))<<endl;
}
