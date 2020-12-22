#include<bits/stdc++.h>
using namespace std;

/**
  k=n − pi[n−1].
  if k divides n, then k will be the
  answer, otherwise there doesn't
  exists an effective
  compression and the answer is n.
*/
int compress(string s)
{
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++)
    {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return n-pi[n-1];
}



int main()
{
    string s="ababab";
    int k=compress(s);
    if((s.size())%k==0)
        cout<<k<<endl;
    else
        cout<<s.size()<<endl;
}

