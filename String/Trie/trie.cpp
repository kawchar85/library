#include<bits/stdc++.h>
#define sz 200005
#define t_sz 26
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

struct node{
    bool ending;
    int next[t_sz];
    node()
    {
        ending=0;
        for(int i=0; i<t_sz; i++)
            next[i]=0;
    }
}data[sz];

int counter=1;
void ADD(string s)
{
    int i,now,n=0;
    for(i=0; i<s.size(); i++)
    {
        now=s[i]-'a';
        if(data[n].next[now]==0)
            data[n].next[now]=counter++;
        n=data[n].next[now];
    }
    data[n].ending=1;
}

///O(length)
bool SEARCH(string s)
{
    int i,now,n=0;
    for(i=0; i<s.size(); i++)
    {
        now=s[i]-'a';
        if(data[n].next[now]==0)
            return 0;
        n=data[n].next[now];
    }
    return data[n].ending;
}

void delete_trie()
{
    counter=1;
    memset(data, 0, sizeof data);
}

int main()
{
    FAST

    int n,i;
    string s;
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>s;
        ADD(s);
    }
    cin>>n;
    for(i=0; i<n; i++)
    {
        cin>>s;
        if(SEARCH(s))
            puts("YES");
        else
            puts("NO");
    }
    delete_trie();
    return 0;
}
