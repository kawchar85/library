#include<bits/stdc++.h>
using namespace std;

#define MAX 23

typedef long long ll;

bitset<MAX> mask[26];

void test()
{
    for(int i=0; i<26; i++)
    {
        cout<<(char)(i+'a')<<" "<<mask[i]<<endl;
    }
}
void computeMask(string &text)
{
    for(int i=1; i<(int)text.size(); ++i)
    {
        int c=text[i]-'a'; 
        mask[c].set(i);
    }
}

//O(N*N/64)
int StringMatchingInRange(string &pattern, string &text, ll l, ll r)
{
    if((int)pattern.size() > (r-l+1))
        return 0;

    //computeMask(text);
    bitset<MAX> startMask; 
    startMask.set(); // all bits are set to one
    for(int i=1; i<(int)pattern.size(); ++i)
    {
        int c=pattern[i]-'a';
        startMask &= (mask[c] >> i);
    }
    for(int i=l-1; i<r; i++) if(startMask[i]) cout<<i+1<<" ";cout<<endl;
  
    return (startMask>>(l-1)).count()-(startMask >> (r - (int)pattern.size() + 2)).count(); // count() returns number of 1 bits
}
int StringMatching(string &pattern, string &text)
{
    if((int)pattern.size() > (int)text.size())
        return 0;

    //computeMask(text);
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

//O(1)
void update(int idx, char ch, string &text) //set text[idx]=ch, 1-based idx
{
    char old=text[idx];
    mask[old-'a'][idx]=0;
    text[idx]=ch;
    mask[ch-'a'][idx]=1;
}
int32_t main()
{   
    string s,t;
    cin>>s>>t;

    s="#"+s;
    t="#"+t;
    computeMask(t);
    //test();

    int q,ty,l,r,x;
    char ch;
    cin>>q;
    while(q--)
    {
        cin>>ty;
        if(ty==1)
        {
            cin>>l>>r;
            cout<<StringMatchingInRange(s,t,l,r)<<endl;
        }
        else
        {
            cin>>x>>ch;
            update(x,ch,t);
        }
    }

    return 0;
}
/*
abc abcabcabaabccba
6
1 1 15
1 1 5
2 3 a
1 1 15
2 9 a
1 7 15

*/
