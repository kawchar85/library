#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

string MUL(string A, ll x)
{
    string ans,k;
    ll temp,r,carry=0;
    for(int i=A.size()-1; i>=0; i--)
    {
        temp=(A[i]-'0')*x+carry;
        r=temp%10;
        carry=temp/10;
        ans+=to_string(r);
    }
    if(carry)
    {
        k=to_string(carry);
        reverse(k.begin(),k.end());
        ans+=k;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

int main()
{
    string s;
    ll x;
    cin>>s>>x;
    cout<<MUL(s,x);
}
