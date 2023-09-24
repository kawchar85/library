//https://codeforces.com/contest/379/problem/F

#include<bits/stdc++.h>
using namespace std;
#define LOG 21
#define MAX 2000006

int lvl[MAX], LCA[MAX][LOG+1];

//0(logN)
int find_lca(int a, int b) {
    if(lvl[a] > lvl[b])   swap(a,b);
    int d = lvl[b] - lvl[a];
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
int dist(int a, int b) {
    return lvl[a] + lvl[b] - 2 * lvl[find_lca(a, b)];
}
void add_edge(int u, int p) {
    LCA[u][0] = p; lvl[u] = 1 + lvl[p];
    for(int i = 1; i <= LOG; i++)
        LCA[u][i] = LCA[LCA[u][i - 1]][i - 1];
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int q, n = 4; cin >> q;
    add_edge(2, 1);
    add_edge(3, 1);
    add_edge(4, 1);

    int dia = 2, a = 2, b = 4;
    while(q--) {
        int x; cin >> x;
        add_edge(n + 1, x);
        add_edge(n + 2, x);
        n += 2;
        int d1 = dist(n, a);
        int d2 = dist(n, b);

        if(d1 >= max(dia, d2)) {
            dia = d1;
            b = n;
        } else if(d2 >= max(dia, d1)) {
            dia = d2;
            a = n;
        }

        cout << dia << "\n";
    }

    return 0;
}
