#include<bits/stdc++.h>
using namespace std;

string NewString(string s)
{
    string ss="$#";
    for(int i=0; i<s.size(); i++)
    {
        ss+=s[i];
        ss+='#';
    }
    ss+='@';
    return ss;
}

string manachar(string s)
{
    string ans=s;
    s=NewString(s);
    vector<int>d(s.size());
    for(int i=1,c=0,r=0; i+1<s.size(); i++)
    {
        int miror=c+c-i;
        if(i<r)
            d[i]=min(d[miror], r-i);
        while(s[i+1+d[i]]==s[i-1-d[i]])
            d[i]++;
        if(i+d[i]>r)
        {
            c=i;
            r=i+d[i];
        }
    }
    int mx=0,center=0;
    for(int i =0; i<s.size(); i++)
    {
        //cout<<i<<":"<<d[i]<<endl;
        if(d[i]>mx)
        {
            mx=d[i];
            center=i;
        }
    }

    ans=ans.substr((center-mx-1)/2, mx);
    return ans;
}

int main()
{
    //string s="ababcccba";
    string s="aabbccdd";
    cout<<manachar(s)<<endl;
}
