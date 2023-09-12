/*
 https://cses.fi/problemset/task/1731/
 You are given a string of length n
 and a dictionary containing k words.
 In how many ways can you create the 
 string using the words?
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define MOD 1000000007
#define MAX 6005

typedef long long ll;
ll pref[MAX], suff[MAX];

#define t_sz 26
struct node {
    int ending;
    int next[t_sz];
    int link,par;
    vector<int> idx;

    node() {
        ending = 0, par = -1, link = -1;
        memset(next, -1, sizeof next);
    }
};
struct aho_corasick {
    vector< node > aho;
    aho_corasick() {
        aho.emplace_back();
    }
    int ID(char ch) {
        if('a'<=ch && ch<='z')
            return ch - 'a';
        return ch - 'A' + 26;
    }
    void ADD(string &s, int id = 0) {
        int now, u = 0;
        for(auto ch : s) {
            now = ID(ch);
            if(aho[u].next[now] == -1) {
                aho[u].next[now] = aho.size();
                aho.emplace_back();
            }
            u = aho[u].next[now];
        }
        aho[u].ending++;
        aho[u].idx.push_back(id);//kun string sesh hoise?
    }
    int transition(int u, int i) { //from,by
        if(u == -1) return 0; //root
        if(~aho[u].next[i]) return aho[u].next[i];
        return aho[u].next[i] = transition(aho[u].link, i);
    }
    void push_links() {
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int i = 0; i < t_sz; i++) {
                int v = aho[u].next[i];
                if(v == -1) continue;

                aho[v].par = u;
                aho[v].link = transition(aho[u].link, i);
                aho[v].ending += aho[aho[v].link].ending;
                for(auto &id : aho[aho[v].link].idx)
                    aho[v].idx.push_back(id);
                q.push(v);
            }
        }
    }
    void process(string &s, vector<string> &v) {
        int u = 0;
        vector< int > st[s.size() + 10];
        pref[0] = 1;
        for(int i = 0; i < s.size(); i++) {
            int x = ID(s[i]);
            u = transition(u, x);
            //end in i
            pref[i + 1] = 0;
            for(auto id : aho[u].idx) {
                st[i - (int)v[id].size() + 1].push_back(v[id].size());
                pref[i + 1] += pref[i + 2 - (int)v[id].size()];
                pref[i + 1] %= MOD;
                // cout << i + 1 - v[id].size() << " --> " << i << endl;
            }
        }
        suff[s.size() + 1] = 1;
        for(int i = (int)s.size() - 1; i >= 0; i--) {
            //start in i
            suff[i + 1] = 0;
            for(auto len : st[i]) {
                suff[i + 1] += suff[i + len + 1];
                suff[i + 1] %= MOD;
                // cout << i << " <--> " << i + len << endl;
            }
        }
        ll cnt = 0;
        for(int i = 0; i <= s.size(); i++) {
            cnt += pref[i] * suff[i + 1] % MOD;
            cnt %= MOD;
            // cout << i << " " << pref[i] << " " << suff[i + 1] << endl;
        }

        cout << cnt << endl;
    }
    void clear(){
        aho.clear();
        aho.emplace_back();
    }
};

void solve() {
    string s; cin >> s;
    int n, k;
    n = s.size();
    cin >> k;
    vector<string> v;
    aho_corasick ac;
    for(int i = 0; i < k; i++) {
        string x; cin >> x;
        if(x.size() > n) continue;
        ac.ADD(x, v.size());
        v.push_back(x);
    }
    ac.push_links();
    ac.process(s,v);
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    //cin >> TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
