/*
The set only contain elements from the range 0,…,N
We maintain an array telling us whether each element is in the set.
Now, we divide the array into blocks of length sqrt(N)
For each block, we maintain the number of elements present
in the set in this block. Inserting and deleting an element
can be done in O(1) time — update the array and the block.
To find the minimum element, we iterate over the blocks to
find the first one that isn't empty, then iterate over the
elements of that block to find the minimum one that's present.
The time complexity of doing that in O(sqrt(N))
*/
#include<bits/stdc++.h>
using namespace std;

const int N = 100001, blk = 320;
struct MySet{
    vector<int> cnt[blk], sz;
    MySet() {
        sz.resize(blk, 0);
        for(int i = 0; i < blk; i++) {
            cnt[i].resize(blk, 0);
        }
    }
    void insert(int x) {
        int b = x / blk, idx = x % blk;
        sz[b]++; cnt[b][idx]++;
    }
    void remove(int x) {
        int b = x / blk, idx = x % blk;
        if(!cnt[b][idx]) return;
        sz[b]--; cnt[b][idx]--;
    }
    int findMin() { //sqrt(N)
        for(int i = 0; i < blk; i++) {
            if(sz[i] < 1) continue;
            for(int j = 0; j < blk; j++) {
                if(cnt[i][j] > 0) return i * blk + j;
            }
        }
        return -1;
    }
};

int32_t main() {
    MySet s;

    s.insert(10);
    s.insert(12);
    s.insert(8);
    cout << s.findMin() << endl;
    s.insert(8);
    s.insert(9);
    s.remove(8);
    cout << s.findMin() << endl;
    s.remove(8);
    cout << s.findMin() << endl;
    s.remove(8);
    cout << s.findMin() << endl;

    return 0;
}
