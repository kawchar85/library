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

//length of longest palindromic prefix
int palindromicPrefix(string s)
{
    string rev=s;
    reverse(rev.begin(), rev.end());
    s=s+'#'+rev;
    return prefix_function(s);
}

int main()
{
    string s="abababccbaba";
    cout<<palindromicPrefix(s);
}
