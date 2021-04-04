#include<bits/stdc++.h>
using namespace std;
/**
     z[i] is the length of the
     longest common prefix between
     s and the suffix of s starting at i.

     longest common prefix between
     s[1...n], s[i...n]
*/

//O(s.size())
vector<int> z_function(string s)
{
    int n = (int) s.length();
    vector<int> z(n);
    //z[0]=n;
    for(int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    string s;
    cin>>s;
    vector<int> z = z_function(s);
    for(auto x : z)
        cout<<x<<" ";

}
   
