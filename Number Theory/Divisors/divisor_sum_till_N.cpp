#include<bits/stdc++.h>
#define MAX 100005
#define ll long long
using namespace std;

ll sod[MAX];
//O(NLogN)
void SOD() {
    for(int i = 1; i < MAX; i++) {
        for(int j = i; j < MAX; j += i) {
           sod[j] += i;
        }
    }
}

int main(){

}
