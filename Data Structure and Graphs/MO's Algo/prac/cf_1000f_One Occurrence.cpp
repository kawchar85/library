//https://codeforces.com/contest/1000/problem/F
#include<bits/stdc++.h>
using namespace std;
#define MAX 500005
#define B_SIZE 710 ///sqrt(MAX)

const int N = 500001, blk = 710;
struct DS{
    vector<int> cnt[blk], occOne;
    DS() {
        occOne.resize(blk, 0); //count how many number in this block has exacly one occurrence
        for(int i = 0; i < blk; i++) {
            cnt[i].resize(blk, 0);
        }
    }
    void insert(int x) {
        int b = x / blk, idx = x % blk;
        cnt[b][idx]++;
        if(cnt[b][idx] == 1) occOne[b]++;
        if(cnt[b][idx] == 2) occOne[b]--;
    }
    void remove(int x) {
        int b = x / blk, idx = x % blk;
        if(!cnt[b][idx]) return;
        cnt[b][idx]--;
        if(cnt[b][idx] == 1) occOne[b]++;
        if(cnt[b][idx] == 0) occOne[b]--;
    }
    int find() { //sqrt(N)
        for(int i = 0; i < blk; i++) {
            if(occOne[i] < 1) continue;
            for(int j = 0; j < blk; j++) {
                if(cnt[i][j] == 1) return i * blk + j;
            }
        }
        return 0;
    }
};
struct query{
    int l, r, id;
};
query Q[MAX];
int ar[MAX], ans[MAX];
DS vec;

bool cmp(query &a, query &b) {
    if(a.l/B_SIZE != b.l/B_SIZE)
        return a.l<b.l;
    return a.l/B_SIZE%2?a.r>b.r:a.r<b.r;
}
void add(int pos) {
    vec.insert(ar[pos]);
}
void sub(int pos) {
    vec.remove(ar[pos]);
}
int get_ans() {
    return vec.find();
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
    for(int i = 0; i < q; i++)
        cout << ans[i] << "\n";
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, q, L, R;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> ar[i];
    }
    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> L >> R;
        Q[i].id = i;
        Q[i].l = L - 1;
        Q[i].r = R - 1;
    }
    MO(q);
    return 0;
}
