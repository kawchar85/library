#include<bits/stdc++.h>
using namespace std;
int d[]={30,20,15,5,10,5,10};

int main()
{
    int n=6,i,j,k,lvl;
    int M[10][10]={0};

    for(lvl=1; lvl<n; lvl++)
    {
        for(i=1; i<=n-lvl; i++)
        {
            j=i+lvl;
            //cout<<i<<" "<<j<<endl;
            M[i][j]=INT_MAX;
            for(k=i; k<j; k++)
            {
                M[i][j]=min(M[i][k]+M[k+1][j]+d[i-1]*d[k]*d[j],M[i][j]);
            }

        }
    }

    ///print
    for(lvl=0; lvl<n; lvl++)
    {
        for(i=1; i<=n-lvl; i++)
        {
            j=i+lvl;
            cout<<M[i][j]<<" ";

        }
        cout<<endl;
    }

}
