/**
    https://lightoj.com/problem/substring-frequency-ii
*/
#include<bits/stdc++.h>
#define MAX 200005
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

#define t_sz 26

struct node{
    int ending;
    int next[t_sz];
    int link,par;
    vector<int> idx;

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
        return ch-'A'+26;
    }
    void ADD(string &s, int id=0)
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
        aho[u].idx.push_back(id);//kun string sesh hoise?
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
                for(auto &id : aho[aho[v].link].idx)
                    aho[v].idx.push_back(id);
                q.push(v);
            }
        }
    }

    int pos[502];
    int CNT(string &s, vector<string> &v)
    {
        int n=v.size();
        for(int i=0; i<n; i++)
            pos[i]=0;

        int u=0,sum=0;
        for(int i=0; i<s.size(); i++)
        {
            int x=ID(s[i]);
            u=transition(u, x);
            sum+=aho[u].ending;
            for(auto id : aho[u].idx)
                pos[id]++;
        }
        for(int i=0; i<n; i++)
        {
            cout<<pos[i]<<endl;
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
    string s,t;
    int n,i,j,k,cs=1,tc;

    aho_corasick ac;
    vector<string> v;
    cin>>tc;
    while(tc--)
    {
        cin>>n>>t;
        v.clear();
        for(i=0; i<n; i++)
        {
            cin>>s;
            ac.ADD(s,i);
            v.push_back(s);
        }
        ac.push_links();
        cout<<"Case "<<cs++<<":\n";
        ac.CNT(t,v);

        ac.clear();
    }

    
    return 0;
}
