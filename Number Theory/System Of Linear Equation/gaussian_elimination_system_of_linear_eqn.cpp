#include<bits/stdc++.h>
using namespace std;

#define MAX 205
#define EPS 1e-9
typedef long double ld;

/**
    return 1--> unique sol
    return 0--> 0/inf sol (singular system)
    n--> no of eqn
    O(N^3)
*/
bool zero(ld x) { return fabs(x)<EPS;}
ld mat[MAX][MAX];
ld con[MAX];

void print(int n)
{
    int i,j;
    cout<<"-------------------\n";
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++){
            if(zero(mat[i][j])) mat[i][j]=0;
            cout<<mat[i][j]<<" ";
        }
        cout<<"| "<<con[i]<<endl;
    }
    cout<<"-------------------\n";
}
bool Gaussian_Elimination(int n)
{
    int i,j,k,pivot;

    for(i=1; i<=n; i++)
    {
        //find non-zero pivot
        pivot=-1;
        for(j=i; j<=n; j++)
        {
            if(!zero(mat[j][i]))
            {
                pivot=j;
                break;
            }
        }

        if(pivot==-1) return 0; //singular system
        if(pivot != i) //need pivoting
        {
            for(j=i; j<=n; j++)
                swap(mat[i][j], mat[pivot][j]);
            swap(con[i], con[pivot]);
        }

        //normalization
        ld x=mat[i][i];
        for(j=1; j<=n; j++)
            mat[i][j]/=x;
        con[i]/=x;


        //forward elimination
        for(j=1; j<=n; j++)
        {
            if(j==i) continue;//pivot

            ld factor=mat[j][i]/mat[i][i];
            for(k=i; k<=n; k++)
            {
                mat[j][k]-=factor*mat[i][k];
            }
            con[j]-=factor*con[i];
        }
        //print(n);
    }

    print(n);
    return 1;
}

int32_t main()
{
    int n,i,j;
    cin>>n;
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            cin>>mat[i][j];
        cin>>con[i];
    }
    Gaussian_Elimination(n);
    
    return 0;
}

/*
input:
3
2 -1 3 15
4 -2 2 42
1 1 -1 9


3
3 -0.1 -0.2 7.85
0.1 7 -0.3 -19.3
0.3 -0.2 10 71.4
*/
