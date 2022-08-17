/**
    Given two strings A and B and 
    below operations that can be 
    performed on A. Find the minimum
    number of edits (operations) 
    required to convert ‘A’ into ‘B’.

        --Insert
        --Remove
        --Replace
    All of the above operations are of equal cost(1).
*/

#include<bits/stdc++.h>
using namespace std;
#define MAX 5003

string A,B;
int dp[MAX][MAX];

int distance(int i, int j)
{
    if(i==0) return j;
    if(j==0) return i;
    int &ret=dp[i-1][j-1];
    if(~ret) return ret;

    ret = (A[i-1]!=B[j-1])+distance(i-1, j-1); //match or modify
    ret = min(ret, 1+distance(i, j-1)); // insert
    ret = min(ret, 1+distance(i-1, j)); // delete

    return ret;
}

int main()
{
    memset(dp, -1, sizeof dp);
    cin>>A>>B;
    cout<<distance(A.size(), B.size())<<endl;
    return 0;   
}
