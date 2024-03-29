#include<bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

//find_by_order(),order_of_key()
//greater<int>,less_equal<int>

int main()
{

    ordered_set s;
    s.insert(2);
    s.insert(7);
    s.insert(3);
    s.insert(9);
    s.erase(9);
    auto x = s.find_by_order(2); //2nd position
    cout<<*x<<"\n";

    x=s.find_by_order(10);
    if(x==end(s))
        cout<<"None\n";

    cout<<s.order_of_key(7)<<"\n"; //position of 7

    cout<<s.order_of_key(8)<<"\n";

    cout<<s.size()<<endl;
    cout<<*s.find(7)<<endl;
    cout<<*s.find(8)<<endl;
    return 0;
}
