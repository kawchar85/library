#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 200005
typedef long long ll;

struct info{
    int l, r, prt, sz, val, ans, rev;
};

//1-Based index
int N, treap;
info tree[MAX];

void init(){ N = 0; treap = -1; srand(time(0));}

int get_node(int val){
    tree[N].val = val;
    tree[N].ans = val;
    tree[N].rev = 0;
    tree[N].sz = 1;
    tree[N].l = -1;
    tree[N].r = -1;
    tree[N].prt = rand() % 1000000000;

    return N++;
}

void propagate(int t){
    //push down: T-->L,R
    if(t == -1 || !tree[t].rev) return;
    int l = tree[t].l, r = tree[t].r;
    if(~l) tree[l].rev ^= 1; 
    if(~r) tree[r].rev ^= 1;
    swap(tree[t].l, tree[t].r);
    tree[t].rev = 0;
}

void calibrate(int t){
    //push up: L,R-->Par
    propagate(t); //need?
    if(t == -1) return;
    tree[t].sz = 1;
    int l = tree[t].l, r = tree[t].r;
    //update values
    tree[t].ans = tree[t].val;
    if(~l){ //Combine Lft,Par
        tree[t].sz += tree[l].sz;
        tree[t].ans = tree[l].ans + tree[t].ans;
    }
    if(~r){ //Combine Par,Rgt
        tree[t].sz += tree[r].sz;
        tree[t].ans = tree[t].ans + tree[r].ans;
    }
}

pair<int,int> split(int t, int key){
    propagate(t);
    if(t == -1) return {-1, -1};
    if(key <= 0) return {-1, t};
    pair<int,int> ret;
    int l = tree[t].l, r = tree[t].r;
    if(l == -1 || tree[l].sz < key){
        ret = split(r, key - (~l ? tree[l].sz : 0) - 1);
        tree[t].r = ret.first;
        ret.first = t;
    }else{
        ret = split(l, key);
        tree[t].l = ret.second;
        ret.second = t;
    }
    calibrate(t);
    return ret;
}
//only for sorted list
pair<int,int> split_by_value(int t, int val){
    propagate(t);
    if(t == -1) return {-1, -1};
    pair<int,int> ret;
    int l = tree[t].l, r = tree[t].r;
    if(tree[t].val <= val){
        ret = split_by_value(r, val);
        tree[t].r = ret.first;
        ret.first = t;
    }else{
        ret = split_by_value(l, val);
        tree[t].l = ret.second;
        ret.second = t;
    }
    calibrate(t);
    return ret;
}
//v[0] = [1, l-1], v[1] = [l, r], v[2] = [r+1, N]
vector<int> parts(int l, int r){
    vector<int> v(3);
    auto cur = split(treap, l - 1);
    v[0] = cur.first;
    cur = split(cur.second, r - l + 1);
    v[1] = cur.first;
    v[2] = cur.second;
    return v;
}
int merge(int a,int b){
    propagate(a); propagate(b);
    if(min(a, b) == -1) return max(a, b);
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
int merge(int a, int b, int c){
    return merge(merge(a, b), c);
}
int query(int l, int r){
    auto p = parts(l, r);
    int ret = tree[ p[1] ].ans;
    treap = merge(p[0], p[1], p[2]);
    return ret ;
}
void move_to_beg(int l, int r){
    auto p = parts(l, r);
    treap = merge(p[1], p[0], p[2]);
}
void erase(int l, int r){
    auto p = parts(l, r);
    treap = merge(p[0], p[2]);
}
void update(int i, int val){
    auto p = parts(i, i);
    tree[ p[1] ].val = val;
    calibrate(p[1]);
    treap = merge(p[0], p[1], p[2]);
}
void reverse(int l, int r){
    auto p = parts(l, r);
    tree[ p[1] ].rev ^= 1;
    treap = merge(p[0], p[1], p[2]);
}
void cyclicShift(int l, int r, int cnt = 1, int left_shift = 0){
    auto p = parts(l, r);
    if(left_shift) cnt = r - l + 1 - cnt;
    auto cur = split(p[1], cnt);
    p[1] = merge(cur.second, cur.first);
    treap = merge(p[0], p[1], p[2]);
}
void insert(int i, int val){
    int x = get_node(val);
    auto p = parts(i, i);
    p[1] = merge(x, p[1]);
    treap = merge(p[0], p[1], p[2]);
}
void push_back(int val){
    treap = merge(treap, get_node(val));
}
void print(int t = treap, int last = 1){
    propagate(t);
    if(t == -1) return;
    print(tree[t].l, 0);
    cout << tree[t].val << ' ';
    print(tree[t].r, 0);
    if(last) cout << "\n";
}
//for sorted list
int lower_bound(int val){
    //[<val][val][>val]
    auto p = split_by_value(treap, val);
    auto p2 = split_by_value(p.first, val-1);
    int pos = 1;
    if(~p2.first) pos += tree[p2.first].sz;
    treap = merge(p2.first, p2.second, p.second);
    return pos;
}
int find_pos(int val){
    //[<val][val][>val]
    auto p = split_by_value(treap, val);
    auto p2 = split_by_value(p.first, val-1);
    int pos = 1;
    if(p2.second == -1) pos = -1;
    else if(~p2.first) pos += tree[p2.first].sz;
    treap = merge(p2.first, p2.second, p.second);
    return pos;
}

void solve(){

    init();
    ll n, x;

    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> x;
        push_back(x);
    }

    print();
    update(3, 10); print();
    insert(3, 15); print();
    cout << query(1, 3) << endl;
    erase(3, 4); print();
    insert(3, 3); print();

    x = 10;
    if(find_pos(x) == -1){
        insert(lower_bound(x), x);
    }
    print();
    
    x = 2;
    x = find_pos(x);
    if(~x) erase(x, x);
    print();
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
/**
5
1 2 3 4 5
*/
