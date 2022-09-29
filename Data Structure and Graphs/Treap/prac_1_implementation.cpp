//https://codeforces.com/contest/863/problem/D

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 300005
typedef long long ll;

ll F(ll x, ll y){
    return x + y;
}
struct info{
    int l, r, prt, sz, val, ans;
    int rev;
};

//1-Based index
int N, treap;
info tree[MAX];

void init(){ N = 0; treap = -1; srand(time(0));}

int get_node(int val){
    tree[N].val = val;
    tree[N].ans = val;
    tree[N].sz = 1;
    tree[N].l = -1;
    tree[N].r = -1;
    tree[N].rev = 0;
    tree[N].prt = rand() % 1000000000;

    return N++;
}

void propagate(int t){
    if(t == -1 || !tree[t].rev) return;
    int l = tree[t].l, r = tree[t].r;

    if(~l) tree[l].rev ^= 1; 
    if(~r) tree[r].rev ^= 1;
    swap(tree[t].l, tree[t].r);
    tree[t].rev = 0;
}
void calibrate(int i){
    propagate(i);
    if(i == -1) return;
    tree[i].sz = 1;
    int l = tree[i].l, r = tree[i].r;
    tree[i].ans = tree[i].val;
    if(~l){
        tree[i].sz += tree[l].sz;
        tree[i].ans = F(tree[l].ans,  tree[i].ans);
    }
    if(~r){
        tree[i].sz += tree[r].sz;
        tree[i].ans = F(tree[i].ans, tree[r].ans);
    }
}
pair<int,int> split(int t, int key){
    propagate(t);
    if(t == -1) return {-1, -1};
    if(key == 0) return {-1, t};

    pair<int,int> ret;
    int l = tree[t].l, r = tree[t].r;
    if(l == -1 || tree[l].sz < key){
        ret = split(r, key - (~l ? tree[l].sz : 0) - 1);
        tree[t].r = ret.first;
        ret.first = t;
        calibrate(t);
    }else{
        ret = split(l, key);
        tree[t].l = ret.second;
        ret.second = t;
        calibrate(t);
    }
    return ret;
}
int merge(int a,int b){
    propagate(a); propagate(b);
    if(a == -1) return b;
    if(b == -1) return a;
    if(tree[a].prt > tree[b].prt){
        tree[a].r = merge(tree[a].r, b);
        calibrate(a);
        return a;
    }else{
        tree[b].l = merge(a, tree[b].l);
        calibrate(b);
        return b;
    }
}

int query(int l, int r){
    int a, b, c;
    auto cur = split(treap, l - 1);
    a = cur.first;
    cur = split(cur.second, r - l + 1);
    b = cur.first;
    c = cur.second;
    int ret = tree[b].ans;
    a = merge(a, b);
    a = merge(a, c);
    treap = a;
    return ret;
}

void erase(int l, int r){
    int a, b, c;
    auto cur = split(treap, l - 1);
    a = cur.first;
    cur = split(cur.second, r - l + 1);
    b = cur.first;
    c = cur.second;
    a = merge(a, c);
    treap = a;
}

void update(int i, int val){
    int a, b, c;
    auto cur = split(treap, i - 1);
    a = cur.first;
    cur = split(cur.second, 1);
    b = cur.first;
    tree[b].val = val;
    calibrate(b);
    c = cur.second;
    a = merge(a, b);
    a = merge(a, c);
    treap = a;
}
void insert(int i, int val){
    auto ret = split(treap, i - 1);
    int x = get_node(val);
    int t = merge(ret.first, x);
    t = merge(t, ret.second);
    treap = t;
}
void push_back(int val){
    treap = merge(treap, get_node(val));
}
void reverse(int l, int r){
    int a, b, c;
    auto cur = split(treap, l - 1);
    a = cur.first;
    cur = split(cur.second, r - l + 1);
    b = cur.first;
    c = cur.second;
    tree[b].rev ^= 1;

    a = merge(a, b);
    a = merge(a, c);
    treap = a;
}
void cyclicShift(int l, int r, int cnt = 1, int left_shift = 0){
    int a, b, c;
    auto cur = split(treap, l - 1);
    a = cur.first;
    cur = split(cur.second, r - l + 1);
    b = cur.first;
    c = cur.second;

    if(left_shift) cur = split(b, r - l + 1 - cnt);
    else cur = split(b, cnt);
    
    b = merge(cur.second, cur.first);
    a = merge(a, b);
    a = merge(a, c);
    treap = a;
}
void print(int i = treap, int last = 1){
    if(i == -1) return;
    propagate(i);
    print(tree[i].l, 0);
    cout << tree[i].val << ' ';
    print(tree[i].r, 0);
    if(last) cout << "\n";
}

void solve(){
    init();
    int n, q, m, x, y, z;

    cin >> n >> q >> m;
    for(int i = 0; i < n; i++){
        cin >> x;
        push_back(x);
    }

    //print();
    while(q--){
        cin >> x >> y >> z;
        if(x == 1) cyclicShift(y, z, 1, 1);
        else reverse(y, z);
        //print();
    }

    while(m--){
        cin >> x;
        cout << query(x, x) << " ";
    } cout << endl;
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
