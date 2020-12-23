#include<bits/stdc++.h>
using namespace std;

vector<int> z_function(string s)
{
    int n = (int) s.size();
    vector<int> z(n);
    z[0]=n;
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
/**
    task is, for any prefix of
    string s which matches a
    suffix of string s, print the
    number of times it occurs
    in string s as a substring.
*/
vector< pair<int,int> > PrefixWithSuffix(string s)
{
    int n=s.size();

    vector<int> z = z_function(s);

    vector<int> cnt(n+5);

    for(int i=0; i<n; i++)
    {
        cnt[z[i]]++;
    }

    int x=0;
    for(int i=n; i>0; i--)
    {
        if(cnt[i])
        {
            cnt[i]+=x;
            x=cnt[i];
        }
    }
    vector< pair<int, int> > v;
    for(int i=0; i<n; i++)
    {
        if(z[i]+i==n) /// suffix matches
            v.push_back({z[i], cnt[z[i]]});
    }
    sort(v.begin(), v.end());
    return v;
}

int main()
{
    string s;
    cin>>s;

    vector< pair<int, int> > v = PrefixWithSuffix(s);
    cout<<v.size()<<endl;
    for(auto x : v)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }


    return 0;
}
