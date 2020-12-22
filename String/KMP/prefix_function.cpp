#include<bits/stdc++.h>
using namespace std;

/**
 the value π[i] shows the longest
 length of a substring ending in position i
 that(suffix of this substring) coincides with the prefix.
*/
vector<int> prefix_function(string s) {
    int n = (int)s.size();
    vector<int> pi(n);
    //int j=0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


int main()
{
    string s="abba#abcbaba";
    //string s="012345";
    vector<int> v=prefix_function(s);
    for(auto x : v)
        cout<<x<<" ";
}
