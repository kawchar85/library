//https://cses.fi/problemset/task/1139/

#include<bits/stdc++.h>
using namespace std;
 
#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define MOD 1000000007
#define MAX 200005
#define B_SIZE 450 ///sqrt(MAX)
 
typedef long long ll;
int val[MAX];
vector<int> adj[MAX];
 
int ft[MAX], in[MAX], out[MAX];
int Timer = 1;

//child of x = (in[x], out[x]]
void DFS(int u, int p) {
    ft[Timer] = u;
    in[u] = Timer++;

    for(auto v : adj[u]) {
        if(v == p) continue;
        DFS(v, u);
    }
    out[u] = Timer - 1;
}

struct query{
    int l, r, id;
};
query Q[MAX];
int ans[MAX], fre[MAX],cnt = 0;

bool cmp(query &a, query &b) {
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
void add(int pos) {
    fre[val[ft[pos]]]++;
    if(fre[val[ft[pos]]] == 1)
        cnt++;
}
void sub(int pos) {
    fre[val[ft[pos]]]--;
    if(!fre[val[ft[pos]]])
        cnt--;
}
int get_ans() {
    return cnt;
}
void MO(int q) {
    sort(Q, Q+q, cmp);
    int cur_l = 0, cur_r = -1;
    for(int i = 0; i < q; i++) {
        int L = Q[i].l;
        int R = Q[i].r;
        while(cur_l > L)  add(--cur_l);
        while(cur_r < R)  add(++cur_r);
        while(cur_l < L)  sub(cur_l++);
        while(cur_r > R)  sub(cur_r--);
        ans[Q[i].id] = get_ans();
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> v;
    for(int i = 1; i <= n; i++) {
        cin >> val[i];
        v.push_back(val[i]);
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    sort(v.begin(), v.end());
    map<int,int> mp;
    int id = 1;
    for(auto &x : v) {
        if(!mp[x]) mp[x] = id++;
    }
    for(int i = 1; i <= n; i++) {
        val[i] = mp[val[i]];
    }
    DFS(1, -1);
    // for(int i = 1; i <= n; i++) {
    //     cout << i << " : {";
    //     for(int j = in[i]; j <= out[i]; j++) {
    //         cout << ft[j] << ",";
    //     } cout << "}\n";
    // }
    for(int i = 1; i <= n; i++) {
        Q[i - 1].id = i - 1;
        Q[i - 1].l = in[i]; //including i
        Q[i - 1].r = out[i];
    }
    MO(n);
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
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
