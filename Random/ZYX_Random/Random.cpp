#include<bits/stdc++.h>
using namespace std;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    for(int i = 0; i < 10; i++) {
        cout << rnd() << " ";
    }
    return 0;
}
