#include<bits/stdc++.h>
using namespace std;

#define MAX 2003

typedef long long ll;

bitset<MAX> mask[26];

void computeMask(string &text)
{
    text="#"+text; //to make text it 1-indexed.
    for(int i=1; i<(int)text.size(); ++i)
    {
        int c=text[i]-'a'; 
        mask[c].set(i);
    }
}

//O(N*N/64)
int StringMatching(string &pattern, string &text)
{
    if((int)pattern.size() > (int)text.size())
        return 0;

    //computeMask(text);
    pattern="#"+pattern;
    bitset<MAX> startMask; 
    startMask.set(); // all bits are set to one
    for(int i=1; i<(int)pattern.size(); ++i)
    {
        int c=pattern[i]-'a';
        startMask &= (mask[c] >> i);
    }
    for(int i=0; i<MAX; i++) if(startMask[i]) cout<<i+1<<" ";cout<<endl;
  
    return startMask.count(); // count() returns number of 1 bits
}

int32_t main()
{   
    string s,t;
    cin>>s>>t;

    computeMask(t);
    cout<<StringMatching(s,t)<<endl;

    return 0;
}
