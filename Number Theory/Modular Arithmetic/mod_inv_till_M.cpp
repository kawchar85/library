#include<bits/stdc++.h>
#define MAX 500
using namespace std;

int inv[MAX];

///O(m) m must be prime
void inverse(int m)
{
    inv[1]=1;
    for(int i=2; i<m; i++)
        inv[i]=(m-(m/i)*inv[m%i]%m)%m;
}

int main()
{

}
