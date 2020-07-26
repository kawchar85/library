#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
string DIV(string s, ll a)
{
    string ans="";
    ll temp=0,r,i=0;
    while(i<s.size())
    {
        temp=(temp*10+s[i++]-'0');
        r=temp/a;
        temp=temp%a;
        ans+=to_string(r);
    }
    for(i=0; i<ans.size(); i++)
    {
        if(ans[i]=='0')
            ans.erase(ans.begin()+(i--));
        else
            break;
    }
    if(!ans.size())
        ans="0";
    /**
    vhagfol=ans
    vhag sesh=temp
    */
    return ans;
}

int main()
{
    string s;
    ll a;
    cin>>s>>a;
    cout<<DIV(s,a);
}
