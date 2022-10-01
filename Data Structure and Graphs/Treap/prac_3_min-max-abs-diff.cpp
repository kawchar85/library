//https://vjudge.net/problem/SPOJ-TREAP

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 300005
typedef long long ll;

struct info{
    int l, r, prt, sz, val;
    int mn, mx, ans_mn, ans_mx;
};

//1-Based index
int N, treap;
info tree[MAX];

void init(){ N = 0; treap = -1; srand(time(0));}

int get_node(int val){
    tree[N].val = val;
    tree[N].mn = val;
    tree[N].mx = val;
    tree[N].ans_mn = INT_MAX;
    tree[N].ans_mx = INT_MIN;
    tree[N].sz = 1;
    tree[N].l = -1;
    tree[N].r = -1;
    tree[N].prt = rand() % 10114343;

    return N++;
}

void calibrate(int i){
    //propagate(i);
    if(i == -1) return;

    int l = tree[i].l, r = tree[i].r;

    tree[i].sz = 1;
    tree[i].ans_mn = INT_MAX;
    tree[i].ans_mx = INT_MIN;
    tree[i].mn = tree[i].mx = tree[i].val;
    if(~l){
        //combine Lft and Parent
        tree[i].sz += tree[l].sz;
        tree[i].mn = tree[l].mn;
        tree[i].ans_mn = min(tree[i].ans_mn, tree[l].ans_mn);
        tree[i].ans_mn = min(tree[i].ans_mn, tree[i].val - tree[l].mx);
    }
    if(~r){
        //combine P,R
        tree[i].sz += tree[r].sz;
        tree[i].mx = tree[r].mx;
        tree[i].ans_mn = min(tree[i].ans_mn, tree[r].ans_mn);
        tree[i].ans_mn = min(tree[i].ans_mn, tree[r].mn - tree[i].val);
    }

    if(tree[i].sz > 1) tree[i].ans_mx = tree[i].mx - tree[i].mn;

}
pair<int,int> split(int t, int key){
    //propagate(t);
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

//for sorted list
pair<int,int> split_by_value(int t, int val){
    //propagate(t);
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
    //propagate(a); propagate(b);
    if(min(a,b) == -1) return max(a,b);
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
pair<int, int> query(int l, int r){
    auto p = parts(l, r);
    pair<int, int> ret = {tree[ p[1] ].ans_mn, tree[ p[1] ].ans_mx};
    treap = merge(p[0], p[1], p[2]);

    return ret ;
}
void insert(int i, int val){
    auto ret = split(treap, i - 1);
    int x = get_node(val);
    int t = merge(ret.first, x);
    t = merge(t, ret.second);
    treap = t;
}
void erase(int l, int r){
    auto p = parts(l, r);
    treap = merge(p[0], p[2]);
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
int order_ok_key(int val){
    //[<val][val][>val]
    auto p = split_by_value(treap, val);
    auto p2 = split_by_value(p.first, val-1);
    int pos = 1;
    if(~p2.first) pos += tree[p2.first].sz;
    treap = merge(p2.first, p2.second, p.second);
    return pos;
}

void push_back(int val){
    treap = merge(treap, get_node(val));
}

void print(int i = treap, int last = 1){
    if(i == -1) return;
    //propagate(i);
    print(tree[i].l, 0);
    cout << tree[i].val << ' ';
    print(tree[i].r, 0);
    if(last) cout << "\n";
}

void solve(){
    int n, q, m, x, y, z;
    char ch;
    cin >> n;
   
    init();
    //print();
    while(n--){
        cin >> ch;

        if(ch == 'I'){
            cin >> x;
            if(find_pos(x) == -1){
                insert(order_ok_key(x), x);
            }
        }
        else if(ch == 'D'){
            cin >> x;
            x = find_pos(x);
            if(~x) erase(x, x);
        }
        else {
            cin >> x >> y;
            x++, y++;

            auto p = query(x, y);
            if(ch == 'N'){
                cout << p.first << endl;
            }
            else{
                cout << max(-1, p.second) << endl;
            }
        }

    }
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
