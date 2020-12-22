#include<bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
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
/**
    Given a text t and a string s,
    we want to find and display the
    positions of all occurrences
    of the string s in the text t.
*/
vector<int> KMP(string s, string t)
{
    int n=s.size();
    s+="#";
    s+=t;
    vector<int>pi = prefix_function(s);
    vector<int>pos;
    for(int i=2*n; i<s.size(); i++)
    {
        if(pi[i]==n)
            pos.push_back(i-2*n);///i−(n+1)−n+1=i−2n
    }
    return pos;

}

int main()
{
    string s="aba";
    string t="ababacaba";
    vector<int>ans=KMP(s, t);
    for(auto i : ans)
        cout<<i<<" ";
}
