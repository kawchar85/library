#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

string add(string a,string b)
{
    ///reversed number
    string ans="";
    char sum;
    int carry=0,i,j,k,x,la=a.size(),lb=b.size();
    x=max(la,lb);

    for(i=0,j=0; x>0; i++,j++,x--)
    {
        if(i>=la)
            sum=b[j]+carry;
        else if(j>=lb)
            sum=a[i]+carry;
        else
            sum=a[i]+b[j]+carry-'0';
        if(sum>'9')
        {
            sum-=10;
            carry=1;
        }
        else
            carry =0;
        ans+=sum;
    }
    if(carry) ans+="1";
    return ans;
}


string MUL(string A, string B)
{
    string ans="",temp;
    int i,j,carry,x;

    for(i=A.size()-1; i>=0; i--)
    {
        carry=0;
        temp="";
        for(x=A.size()-1; x>i; x--)
            temp+="0";
        for(j=B.size()-1; j>=0; j--)
        {
            x=(A[i]-'0')*(B[j]-'0')+carry;
            //temp+=to_string(x%10);
            temp+=(x%10)+'0';
            carry=x/10;
        }
        ans=add(ans,temp);
    }

    reverse(ans.begin(),ans.end());
    return ans;
}

int main()
{
    string a,b;
    cin>>a>>b;
    cout<<MUL(a,b);
}
