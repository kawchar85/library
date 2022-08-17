#include<bits/stdc++.h>
#define sz 5005
#define ll long long
using namespace std;

string add(string a,string b)
{
    string ans="";
    char sum;
    int carry=0,i,j,k,x,la=a.size(),lb=b.size();
    x=max(la,lb);

    for(i=la-1,j=lb-1; x>0; i--,j--,x--)
    {
        if(i<0)
            sum=b[j]+carry;
        else if(j<0)
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
    reverse(ans.begin(),ans.end());
    return ans;
}

int main()
{
    string a,b;
    cin>>a>>b;
    cout<<add(a,b);
}

