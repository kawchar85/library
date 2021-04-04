/**
    https://vjudge.net/problem/SPOJ-EPALIN
    make palindrome
*/

#include<bits/stdc++.h>
using namespace std;
#define endl "\n"
#define ll long long 

int prefix_function(string &s) {
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
void palindromicSuffix(string &s)
{
    int n=(int)s.size();
    string rev=s;
    string tmp=s;
    reverse(rev.begin(), rev.end());
    s=rev+'#'+s;
    int x=prefix_function(s);
    string ex=tmp.substr(0, n-x);
    reverse(ex.begin(), ex.end());
    cout<<tmp<<ex<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    while(cin>>s)
    {
        palindromicSuffix(s);
    }   
}
