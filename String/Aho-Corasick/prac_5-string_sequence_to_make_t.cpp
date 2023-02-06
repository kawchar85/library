/**
    https://codeforces.com/contest/727/problem/E
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
    void check(string &s, int n, int k)
    {
        int len = s.size();
        s += s; // cyclic so...
        set<int> startFrom[k];
        vector<int> seq[k];

        int u=0, start;
        for(int i=0; i<s.size(); i++)
        {
            int x=ID(s[i]);
            u=transition(u, x);

            if(aho[u].idx.size()){ // eikhane kunota sesh hoise, same length er distinct 1tai ache, size()=1 hobe
                start = i - k + 1;
                //start --> i
                if(start < len) { // 1st part teke start hoite hbe
                    //k distance por por ekta string takbe, beg_idx%k same
                    startFrom[start%k].insert(1+aho[u].idx.back());//id ghula sort hoye jacche!!
                    seq[start%k].push_back(1+aho[u].idx.back());//for print
                }
            }
        }

        for(int i=0; i<k; i++) {
            if(startFrom[i].size() == n) {
                cout << "YES\n";
                for(auto it : seq[i]) {
                    cout << it << " ";
                }
                return;
            }
        }

        cout << "NO\n";
        
    }
    void clear(){
        aho.clear();
        aho.emplace_back();
    }
};

void solve(){
    int n, k, m;
    string s,t;
    aho_corasick ac;

    cin >> n >> k >> t >> m;
    for(int i = 0; i < m; i++) {
        cin >> s;
        ac.ADD(s, i);
    }
    ac.push_links();
    ac.check(t, n, k);
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
