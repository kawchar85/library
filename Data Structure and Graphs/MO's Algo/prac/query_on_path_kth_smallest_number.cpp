//https://vjudge.net/problem/SPOJ-COT

#include<bits/stdc++.h>
using namespace std;
 
#define endl "\n"
#define MAX 100005
#define LOG 18
#define B_SIZE 450 ///sqrt(2*MAX) ft[2*max]
 
typedef long long ll;

vector<int> adj[MAX];
int val[MAX];
 
int ft[2 * MAX], in[MAX], out[MAX];
int Timer = 1;

int dep[MAX], LCA[MAX][LOG+1];

void DFS2(int v, int p) {
    LCA[v][0] = p;
    for(auto x : adj[v]) {
        if(x == p) continue;
        dep[x] = dep[v] + 1;
        DFS2(x, v);
    }
}

//0(NlogN)
void init(int N, int root = 1) {
    memset(LCA, -1, sizeof LCA);
    dep[root] = 0;
    DFS2(root, -1);
    for(int j = 1; j <= LOG; j++) {
        for(int i = 1; i <= N; i++) {
            if(~LCA[i][j-1]) {
                int p = LCA[i][j-1];
                LCA[i][j] = LCA[p][j-1];
            }
        }
    }
}

//0(logN)
int find_lca(int a, int b) {
    if(dep[a] > dep[b])   swap(a,b);
    int d = dep[b] - dep[a];
    while(d > 0) {
        int j = log2(d);
        b = LCA[b][j]; 
        d -= (1 << j);
    }
    if(a == b) return a;
    for(int j = LOG; ~j; j--) {
        if(~LCA[a][j] && (LCA[a][j] != LCA[b][j])) {
            a = LCA[a][j];
            b = LCA[b][j];
        }
    }
    return LCA[a][0];
}
void DFS(int u, int p) {
    ft[Timer] = u;
    in[u] = Timer++;

    for(auto v : adj[u]) {
        if(v == p) continue;
        DFS(v, u);
    }

    ft[Timer] = u;
    out[u] = Timer++;
}

const int blk = 450;
struct DS{
    vector<int> cnt[blk], total;
    DS() {
        total.resize(blk, 0);
        for(int i = 0; i < blk; i++) {
            cnt[i].resize(blk, 0);
        }
    }
    void insert(int x) {
        int b = x / blk, idx = x % blk;
        cnt[b][idx]++;
        total[b]++;
    }
    void remove(int x) {
        int b = x / blk, idx = x % blk;
        if(!cnt[b][idx]) return;
        cnt[b][idx]--;
        total[b]--;
    }
    int find(int k) { //sqrt(N), k'th smallest
        for(int i = 0; i < blk; i++) {
            if(total[i] < k) {
                k -= total[i];
                continue;
            }
            for(int j = 0; j < blk; j++) {
                k -= cnt[i][j];
                if(k <= 0) return i * blk + j;
            }
        }
        return 0;
    }
}ds;
struct query{
    int l, r, id, lca, k;
};
query Q[MAX];
int ans[MAX], times[MAX];

bool cmp(query &a, query &b) {
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
void add(int pos) {
    ds.insert(val[ft[pos]]);
}
void sub(int pos) {
    ds.remove(val[ft[pos]]);
}
void calc(int pos) {
    if(!times[ft[pos]]) add(pos);
    else sub(pos);
    times[ft[pos]] ^= 1;
}
int get_ans(int k) {
    return ds.find(k);
}
void MO(int q) {
    sort(Q, Q+q, cmp);
    int cur_l = 0, cur_r = -1;
    for(int i = 0; i < q; i++) {
        int L = Q[i].l;
        int R = Q[i].r;
        while(cur_l > L)  calc(--cur_l);
        while(cur_r < R)  calc(++cur_r);
        while(cur_l < L)  calc(cur_l++);
        while(cur_r > R)  calc(cur_r--);
        if(Q[i].lca) add(Q[i].lca);
        ans[Q[i].id] = get_ans(Q[i].k);
        if(Q[i].lca) sub(Q[i].lca);
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
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
    unique(v.begin(), v.end());

    map<int,int> mp;
    int id = 1;
    for(auto &x : v) {
        if(!mp[x]) mp[x] = id++;
    }
    for(int i = 1; i <= n; i++) {
        val[i] = mp[val[i]];
    }
    // for(auto x : v) cout << x << " --> " << mp[x] << endl;

    DFS(1, -1);
    init(n);

    for(int i = 0; i < m; i++) {
        int x, y, k; cin >> x >> y >> k;
        if(in[x] > in[y]) swap(x, y);
        Q[i].id = i;
        Q[i].k = k;
        int p = find_lca(x, y);
        if(p == x) {
            Q[i].l = in[x];
            Q[i].r = in[y];
            Q[i].lca = 0;
        } else {
            Q[i].l = out[x];
            Q[i].r = in[y];
            Q[i].lca = in[p];
        }
        
    }
    MO(m);
    for(int i = 0; i < m; i++) {
        cout << v[ans[i] - 1] << "\n";
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
