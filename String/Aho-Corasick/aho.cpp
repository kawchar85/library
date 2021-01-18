/**
    Given a set of strings and a text.
    We have to count all occurrences 
    of all strings from the set in 
    the given text.
*/
#include<bits/stdc++.h>
#define MAX 5200005
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

#define t_sz 26

struct node{
    int ending;
    int next[t_sz];
    int link,par;
    node()
    {
        ending=0;
        memset(next,-1, sizeof next);
        par=-1;
        link=-1;
    }
};

struct aho_corasick{
    vector< node > aho;
    aho_corasick(){
        aho.emplace_back();
    }
    int ID(char ch){
        if('a'<=ch && ch<='z')
            return ch-'a';
        return ch-'A';
    }
    void ADD(string &s)
    {
        int now,u=0;
        for(auto ch:s)
        {
            now=ID(ch);
            if(aho[u].next[now]==-1)
            {
                aho[u].next[now]=aho.size();
                aho.emplace_back();
            }
            u=aho[u].next[now];
        }

        aho[u].ending++;
    }
    int transition(int u, int i) //from,by
    {
        if(u==-1) return 0; //root
        if(~aho[u].next[i]) return aho[u].next[i];
        return aho[u].next[i]=transition(aho[u].link, i);
    }
    void push_links()
    {
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=0; i<t_sz; i++)
            {
                int v=aho[u].next[i];
                if(v==-1) continue;

                aho[v].par=u;
                aho[v].link=transition(aho[u].link, i);
                aho[v].ending+=aho[aho[v].link].ending;
                q.push(v);
            }
        }
    }
    int CNT(string &s)
    {
        int u=0,sum=0;
        for(auto ch : s)
        {
            int x=ID(ch);
            u=transition(u, x);
            sum+=aho[u].ending;
        }
        return sum;
    }
    void clear(){
        aho.clear();
        aho.emplace_back();
    }
};


int main()
{
    FAST
    string s;
    int n,i,j,k;

    aho_corasick ac;
    while(cin>>n)
    {
        vector<string> v;
        for(i=0; i<n; i++)
        {
            cin>>s;
            ac.ADD(s);
            v.push_back(s);
        }
        ac.push_links();
        cin>>s;
        cout<<ac.CNT(s)<<endl;
        ac.clear();
    }

    
    return 0;
}
