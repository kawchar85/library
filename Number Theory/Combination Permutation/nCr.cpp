#include<bits/stdc++.h>
#define MAX 100
#define ll long long

ll nCr[MAX][MAX];
void combinassion()
{
    int i,j;
    for(i=1; i<MAX; i++)
    {
        nCr[i][0]=1;
        nCr[i][1]=i;
    }
    for(i=1; i<MAX; i++)
    {
        for(j=2; j<=i; j++)
        {
            nCr[i][j]=nCr[i-1][j]+nCr[i-1][j-1];
        }
    }
}

int main()
{

}
