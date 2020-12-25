#include<bits/stdc++.h>
#define MAX 101
using namespace std;

int row[MAX],col[MAX],dp[MAX][MAX];


/*
void dimToRowCol()
{
    //n=3 matrix
    //if input is 10 x 30 matrix, 30 x 5 matrix, 5 x 60 matrix
    //int dim[n+1] = { 10, 30, 5, 60 };
    for(int i=0; i<n; i++)
    {
        row[i]=dim[i];
        col[i]=dim[i+1];
    }
}
void RowColToDim()
{
    for(int i=0; i<n; i++)
        dim[i]=row[i];
    dim[n]=col[n-1];
}
*/
 int mergeCost(int l, int k, int r)
{
    return row[l]*col[k]*col[r];
}

//O(n^3)
int solve(int beg, int ending)
{
    if(beg>=ending)
        return 0;
    if(~dp[beg][ending])
        return dp[beg][ending];
    int ans = INT_MAX,left,right;
    for(int k=beg; k<ending; k++)
    {
        left=solve(beg,k);
        right=solve(k+1,ending);
        ans=min(ans,left+right+mergeCost(beg, k, ending));
    }
    
    return dp[beg][ending]=ans;
}

int main()
{
    int n,i;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>row[i]>>col[i];
    }
    memset(dp, -1, sizeof dp);
    cout<<solve(0,n-1)<<endl; 
}
