#include<bits/stdc++.h>
#define SZ 100
#define ll long long

ll nPr[SZ][SZ];
void permutation()
{
    ll i,j;
    for(i=0; i<SZ; i++)
        nPr[i][0]=1;
    for(i=1; i<SZ; i++)
    {
        for(j=1; j<=i; j++)
        {
            nPr[i][j]=i*nPr[i-1][j-1];
        }
    }
}

int main()
{

}
