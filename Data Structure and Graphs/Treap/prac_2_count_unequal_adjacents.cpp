//https://vjudge.net/problem/CodeChef-CHEFC

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL);
#define MAX 300005
typedef long long ll;

struct info{
    int l, r, prt, sz, val, cnt, beg, end;
};

//1-Based index
int N, treap;
info tree[MAX];

void init(){ N = 0; treap = -1; srand(time(0));}

int get_node(int val){
    tree[N].cnt = 1;
    tree[N].val = val;
    tree[N].beg = val;
    tree[N].end = val;
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

    //P: size = 1, cnt = 1, left_val=right_val=val
    tree[i].sz = 1;
    tree[i].cnt = 1;
    tree[i].beg = tree[i].end = tree[i].val;
    if(~l){
        //combine Lft and Parent
        tree[i].sz += tree[l].sz;
        tree[i].cnt += tree[l].cnt;
        tree[i].beg = tree[l].beg;
        
        //Lft er right value and Par er left(that is val) equal hoile cnt--
        if(tree[i].val == tree[l].end){
            tree[i].cnt--;
        }
    }
    if(~r){
        //combine P,R
        tree[i].sz += tree[r].sz;
        tree[i].cnt += tree[r].cnt;
        tree[i].end = tree[r].end;
        if(tree[i].val == tree[r].beg){
            tree[i].cnt--;
        }
    }
}
pair<int,int> split(int t, int key){
    //propagate(t);
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

int query(int l, int r){
    int a, b, c;
    auto cur = split(treap, l - 1);
    a = cur.first;
    cur = split(cur.second, r - l + 1);
    b = cur.first;
    c = cur.second;
    int ret = tree[b].cnt;
    a = merge(a, b);
    a = merge(a, c);
    treap = a;

    return ret ;
}

void move_to_beg(int l, int r){
    int a, b, c;
    auto cur = split(treap, l - 1);
    a = cur.first;
    cur = split(cur.second, r - l + 1);
    b = cur.first;
    c = cur.second;
    a = merge(b, a);
    a = merge(a, c);
    treap = a;
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

    cin >> n;
    init();
    for(int i = 0; i < n; i++){
        cin >> x;
        push_back(x);
    }

    //print();
    cin>>q;
    while(q--){
        cin >> x >> y >> z;
        if(x == 1) cout << query(y, z) << endl;
        else move_to_beg(y, z);
        //print();

    }
}

int32_t main()
{
    FAST
    
    ll TC=1LL,cs=1LL;

    cin>>TC;

    while(TC--){
        //CS(cs++);
        solve();
    }

    return 0;
}
