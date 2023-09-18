//https://cses.fi/problemset/task/2103

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200005
struct SuffixAutomata {
    struct node {
        int len, link, firstpos;
        map<char, int> nxt;
    };
    int sz, last, cnt[N];
    vector<node> t;
    SuffixAutomata() {}
    SuffixAutomata(string &s) {
        memset(cnt, 0, sizeof cnt);
        int n = s.size(); sz = 1; last = 0;
        t.resize(2 * n); t[0].len = 0;
        t[0].link = -1; t[0].firstpos = 0;
        for (auto x: s) {
            extend(x);
        }
        cal_cnt();
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
        cnt[cur] = 1;
    }
    void cal_cnt() {
        vector< pair<int, int> > order;
        for(int i = 1; i < sz; i++) {
            order.push_back({t[i].len, i});
        }
        sort(order.rbegin(), order.rend());
        for(auto [len, u] : order) {
            cnt[t[u].link] += cnt[u];
        }
    }
    int no_of_occurrences(string &s) {
        int u = 0;
        for(auto ch : s) {
            if(!t[u].nxt.count(ch))
                return 0;
            u = t[u].nxt[ch];
        }
        return cnt[u];
    }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    int n = s.size();
    SuffixAutomata sa(s);
    int k; cin >> k;
    while(k--) {
        cin >> s;
        cout << sa.no_of_occurrences(s) << "\n";
    }
    return 0;
}
