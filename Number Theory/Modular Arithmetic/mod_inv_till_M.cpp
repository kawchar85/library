#include<bits/stdc++.h>
using namespace std;
#define MAX 500
#define MOD 1000000007

int inv[MAX];

//m must be prime
void calculateInverse(int n, int m = MOD) {
    inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (m - 1LL * (m/i) * inv[m%i]%m)%m;
}

int main() {
    calculateInverse(100);
    cout << inv[3] << endl;
}
