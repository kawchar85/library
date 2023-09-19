//https://vjudge.net/problem/SPOJ-LCS

#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct SuffixAutomata {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last;
    vector<node> t;
    SuffixAutomata() {}
    SuffixAutomata(string &s) {
        int n = s.size(); sz = 1; last = 0;
        t.resize(2 * n); t[0].len = 0;
        t[0].link = -1; t[0].firstpos = 0;
        for (auto x: s) {
            extend(x);
        }
    }
    void extend(char c) {
        int p = last;
        if (t[p].nxt.count(c)) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                last = q;
                return;
            }
            int clone = sz++;
            t[clone] = t[q];
            t[clone].len = t[p].len + 1;
            t[q].link = clone;
            last = clone;
            while (p != -1 && t[p].nxt[c] == q) {
                t[p].nxt[c] = clone;
                p = t[p].link;
            }
            return;
        }
        int cur = sz++;
        t[cur].len = t[last].len + 1;
        t[cur].firstpos = t[cur].len;
        p = last;
        while (p != -1 && !t[p].nxt.count(c)) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        if (p == -1) t[cur].link = 0;
        else {
            int q = t[p].nxt[c];
            if (t[p].len + 1 == t[q].len) t[cur].link = q;
            else {
                int clone = sz++;
                t[clone] = t[q];
                t[clone].len = t[p].len + 1;
                while (p != -1 && t[p].nxt[c] == q) {
                    t[p].nxt[c] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        last = cur;
    }
};

string longest_common_substring(string &S, string &T) {
    SuffixAutomata sa(S);

    int v = 0, l = 0, best = 0, bestpos = 0;
    for(int i = 0; i < T.size(); i++) {
        while(v && !sa.t[v].nxt.count(T[i])) {
            v = sa.t[v].link ;
            l = sa.t[v].len;
        }
        if (sa.t[v].nxt.count(T[i])) {
            v = sa.t [v].nxt[T[i]];
            l++;
        }
        if (l > best) {
            best = l;
            bestpos = i;
        }
    }
    return T.substr(bestpos - best + 1, best);
} 

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s, t; cin >> s >> t;
    cout << longest_common_substring(s, t).size() << '\n';
    return 0;
}
