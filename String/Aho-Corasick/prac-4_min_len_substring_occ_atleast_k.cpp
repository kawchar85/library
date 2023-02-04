/**
    https://codeforces.com/contest/963/problem/D
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MOD 1000000007
#define MAX 200005

#define CS(i) cout<<"Case "<<i<<": "

typedef long long ll;

int needCnt[MAX];

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
        //return ch-32;
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
    void CNT(string &s, vector<string> &v)
    {
        int n=v.size();
        vector<int> pos[n];

        int u=0;
        for(int i=0; i<s.size(); i++)
        {
            int x=ID(s[i]);
            u=transition(u, x);
            for(auto id : aho[u].idx)
                pos[id].push_back(i);
        }

        for(int i=0; i<n; i++)
        {
            if(needCnt[i] > pos[i].size()) {
                cout << "-1\n";
                continue;
            }
            int mn=INT_MAX/10;
            for(int j=0; (j+needCnt[i]-1)<pos[i].size(); j++) {
                int len = pos[i][(j+needCnt[i]-1)] - pos[i][j] + v[i].size();
                mn = min(mn, len);
            }
            cout << mn << endl;

        }
    }
    void clear(){
        aho.clear();
        aho.emplace_back();
    }
};

void solve(){
    string s,t;
    aho_corasick ac;
    vector<string> v;
    int n, k;

    cin >> t >> n;

    for(int i=0; i<n; i++) {
        cin >> needCnt[i] >> s;
        ac.ADD(s, i);
        v.push_back(s);
    }

    ac.push_links();
    ac.CNT(t,v);
}

int32_t main()
{
    FAST

    ll TC=1LL,cs=1LL;

    //cin>>TC;

    while(TC--){
        //CS(cs++);
        solve();
    }

    return 0;
}
