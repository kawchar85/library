#include<bits/stdc++.h>
using namespace std;

///A-B
string SUB(string A, string B)
{
    int i,j,carry=0;
    string ans="";
    char x;
    for(i=A.size()-1, j=B.size()-1; i>=0; i--,j--)
    {
        if(j<0)
            x=A[i]-carry;
        else
            x=A[i]-B[j]-carry+'0';
        if(x<'0')
        {
            x+=10;
            carry=1;
        }
        else
            carry=0;
        ans+=x;
    }
    for(i=ans.size()-1; i>=0; i--)
    {
        if(ans[i]=='0')
            ans.erase(ans.begin()+i);
        else
            break;
    }
    reverse(ans.begin(),ans.end());
    if(!ans.size())
        ans="0";
    return ans;
}

int main()
{
    string a,b;
    cin>>a>>b;
    cout<<SUB(a,b);
}
