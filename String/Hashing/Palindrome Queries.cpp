/*
    1. set s[idx] = ch
    2. is_palindrom(L, R)
    https://cses.fi/problemset/task/2420/
*/
#include<bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(),v.end()
#define clean(x,y) memset(x,y,sizeof(x));
#define endl "\n"
#define MOD 1000000007
#define MAX 200005

typedef long long ll;

#define B 2017
#define M 1000004119

ll p[MAX], N;
string s;

struct info {
    ll h, r_h, len;
    info() {
        h = r_h = len = 0;
    }
    info(ll h_, ll r_h_, ll len_) {
        h = h_; r_h = r_h_; len = len_;
    }
    void show(){
        cout << h << " " << r_h << " " << len << endl;
    }
}tree[3*MAX];

info merge(info x, info y){
    info ans;
    ans.len = x.len + y.len;
    ans.h = (x.h * p[y.len] % M + y.h) % M;
    ans.r_h = (y.r_h * p[x.len] % M + x.r_h) % M;
    return ans;
}

void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = info(s[l] - 'a' + 1, s[l] - 'a' + 1, 1);
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = merge(tree[node * 2], tree[2 * node + 1]);
}

info query(int node, int l, int r, int i, int j) {
    if(i > r || j < l)
        return info(0, 0, 0);
    if(l >= i && r <= j)
        return tree[node];
    int mid = (l + r) / 2;
    info x = query(node * 2, l, mid, i, j);
    info y = query(node * 2 + 1, mid + 1, r, i, j);
    return merge(x, y);
}

void update(int node, int l, int r, int pos, int val) {
    if(pos > r || pos < l)
        return;
    if(l == r) {
        tree[node] = info(val, val, 1);
        return;
    }
    int mid = (l + r) / 2;
    if(pos <= mid)
        update(node * 2, l, mid, pos, val);
    else
        update(node * 2 + 1, mid + 1, r, pos, val);
    tree[node] = merge(tree[node * 2], tree[2 * node + 1]);
}
void print(int node, int l,int r) {
    cout << "[" << l << "," << r << "]:--> ";
    tree[node].show();
    if(l == r)
        return;
    int mid = ( l + r) / 2;
    print(node*2,l,mid);
    print(node*2+1,mid+1,r);
}
void print(){
    print(1,0,N-1);
}
void build(int n){
    N = n;
    build(1, 0, N - 1);
}
void update(int pos, char ch){
    update(1, 0, N - 1, pos, ch - 'a' + 1);
}
bool query(int i, int j){
    auto x = query(1, 0, N-1, i, j);
    // cout << x.h << " " << x.r_h << endl;
    return x.h == x.r_h;
}
void solve() {
    int n, m;
    cin >> n >> m >> s;
    
    build(n);
    // print();
    while(m--) {
        int t; cin >> t;
        if(t == 1) {
            int k; char x;
            cin >> k >> x;
            update(k - 1, x);
        } else {
            int l, r; cin >> l >> r;
            if(query(l - 1, r - 1)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int TC = 1;

    //cin >> TC;
    p[0] = 1;
    for(int i = 1; i < MAX; i++) {
        p[i] = (p[i - 1] * B) % M;
    }

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
