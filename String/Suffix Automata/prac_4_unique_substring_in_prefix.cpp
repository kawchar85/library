/**
    https://vjudge.net/problem/Toph-distinctness
*/
#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MOD 1000000007
#define MAX 200005

typedef long long ll;
#define int long long

vector<int> ans;
struct SuffixAutomata {
	struct node {
		int len, link, firstpos;
		map<char, int> nxt;
	};
	int sz, last;
	vector<node> t;
	SuffixAutomata() {

	}
	SuffixAutomata(string &s) {
		int n = s.size(); sz = 1; last = 0;
		t.resize(2 * n); t[0].len = 0;
		t[0].link = -1; t[0].firstpos = 0;

		int old = 0;
		for(int i = 0; i < n; i++) {
			extend(s[i]);
			ans.push_back(old + i + 1 - t[t[last].link].len);
			old = ans.back();
		}
	}

	void extend(char c) {
		int p = last;
		if(t[p].nxt.count(c)) {
			int q = t[p].nxt[c];
			if(t[q].len == t[p].len + 1) {
				last = q;
				return;
			}
			int clone = sz++; t[clone] = t[q];
			t[clone].len = t[p].len + 1;
			t[q].link = clone; last = clone;
			while(p != -1 && t[p].nxt[c] == q) {
				t[p].nxt[c] = clone; p = t[p].link;
			}
			return;
		}

		int cur = sz++; t[cur].len = t[last].len + 1;
		t[cur].firstpos = t[cur].len; p = last;

		while(p != -1 && !t[p].nxt.count(c)) {
			t[p].nxt[c] = cur;
			p = t[p].link;
		}
		if(p == -1) t[cur].link = 0;
		else {
			int q = t[p].nxt[c];
			if(t[p].len + 1 == t[q].len) t[cur].link = q;
			else {
				int clone = sz++; t[clone] = t[q];
				t[clone].len = t[p].len + 1;
				while(p != -1 && t[p].nxt[c] == q) {
					t[p].nxt[c] = clone; p = t[p].link;
				}
				t[q].link = t[cur].link = clone;
			}
		}
		last = cur;
	}
};

void solve() {
	string s; cin >> s;
	auto sa = SuffixAutomata(s);
	for(auto x : ans)
		cout << x << "\n";
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
