#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
// #define ordered_set tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update>
// #define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

//usefull functions: find_by_order(),order_of_key()

int main() {
    // Create an ordered set
    ordered_set s;

    // Insert elements into the ordered set
    s.insert(2);
    s.insert(7);
    s.insert(3);
    s.insert(3);
    s.insert(9);

    // Erase an element from the ordered set
    s.erase(9);

    // Find the element at the k-th position (0-based index)
    auto x = s.find_by_order(2); // Find the element at index 2 (3rd element)
    if (x != s.end()) {
        cout << *x << "\n"; // Output the element if it exists
    } else {
        cout << "None\n"; // Output "None" if no such element exists
    }

    // Try to find an element at an out-of-bounds index
    x = s.find_by_order(10); // Find the element at index 10
    if (x == s.end()) {
        cout << "None\n"; // Output "None" if no such element exists
    }

    // Find the position where a given element would be inserted
    cout << s.order_of_key(7) << "\n"; // Position of the element 7
    cout << s.order_of_key(8) << "\n"; // Position where 8 would be inserted

    //Print full set
    for(auto x : s) {
        cout << x << " ";
    }
    return 0;
}
