#include<bits/stdc++.h>
using namespace std;

int prefix_function(string s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi[n-1];
}

//length of longest palindromic suffix
int palindromicSuffix(string s)
{
    string rev=s;
    reverse(rev.begin(), rev.end());
    s=rev+'#'+s;
    return prefix_function(s);
}

int main()
{
    int t;
    cin>>t;
    for(int cs=1; cs<=t; cs++)
    {
        string s;
        cin>>s;
        cout<<palindromicSuffix(s)<<endl;
        //int need=2*s.size()-palindromicSuffix(s);
        //cout<<"Case "<<cs<<": "<<need<<"\n";
    }
}
