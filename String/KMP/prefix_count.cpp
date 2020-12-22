#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi prefix_function(string s) {
    int n = (int)s.size();
    vi pi(n);
    for(int i = 1; i < n; i++)
    {
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

/**
Given a string s of length n.
Count the number of appearances of
each prefix s[0…i] in this string s.
*/
vi count_prefix(string s)
{
    int n=s.size(),i;
    vi ans(n+1);
    vi pi = prefix_function(s);

    for(int i=0; i<n; i++)
        ans[pi[i]]++;
    for(i=n-1; i>0; i--)
        ans[pi[i-1]]+=ans[i]; //k len er takle k-1,k-2,.... er ache
    for(int i=0; i<=n; i++)
        ans[i]++; //for not-proper. p_f find only proper
    return ans;
}

/**
Given a string s of length n.
Count the number of appearances of
each prefix s[0…i] in string T.
*/

vi count_prefix(string s, string t)
{
    int n=s.size(),i,m=t.size();
    string S=s;
    S+="#";
    S+=t;
    vi ans(S.size()+2);
    vi pi = prefix_function(S);

    for(int i=n+1; i<S.size(); i++)
        ans[pi[i]]++;
    for(i=S.size()-1; i>n+1; i--)
        ans[pi[i-1]]+=ans[i];
    for(int i=n+1; i<=S.size(); i++)
        ans[i]++;
    return ans;
}


int main()
{
    string s="ababc";
    //string s="012345";
    vector<int> v=count_prefix(s);
    for(int i=1; i<=s.size(); i++)
        cout<<v[i]<<" ";
    puts("");
    string t="aababcabc";
    vector<int> v2=count_prefix(s,t);
    for(int i=1; i<=s.size(); i++)
        cout<<v2[i]<<" ";
}

