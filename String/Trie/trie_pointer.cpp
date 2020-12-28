#include<bits/stdc++.h>
#define sz 200005
#define t_sz 26
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

struct node{
    bool ending;
    node *next[t_sz];

    node()
    {
        ending=0;
        for(int i=0; i<t_sz; i++)
            next[i]=NULL;
    }
}*root;

void ADD(string s)
{
    int i,now;
    node *cur=root;
    for(i=0; i<s.size(); i++)
    {
        now=s[i]-'a';
        if(cur->next[now]==NULL)
            cur->next[now]=new node();
        cur=cur->next[now];
    }
    cur->ending=1;
}

bool SEARCH(string s)
{
    node *cur=root;
    int i,now;
    for(i=0; i<s.size(); i++)
    {
        now=s[i]-'a';
        if(cur->next[now]==NULL)
            return 0;
        cur=cur->next[now];
    }
    return cur->ending;
}

void delete_trie(node *cur)
{
    for(int i=0; i<t_sz; i++)
        if(cur->next[i]!=NULL)
            delete_trie(cur->next[i]);
    delete(cur);
}

int main()
{
    FAST
    root= new node();

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
    delete_trie(root);
    return 0;
}
