#include<bits/stdc++.h>
using namespace std;
#define MAX 100000000
#define sz 10000
vector<int> prime;
int marked[MAX/64 + 2];

#define isOn(x) (marked[x/64] & (1<<((x%64)/2)))
#define setOn(x)  marked[x/64] |= (1<<((x%64)/2))

void sieve()
{
    int i,j;
    for(i=3; i<sz; i+=2)
        if(!isOn(i))
            for(j=i*i; j<MAX; j+=i+i)
                setOn(j);
    prime.push_back(2);
    for(i=3; i<MAX; i+=2)
        if(!isOn(i)) prime.push_back(i);
}

bool isPrime(int num) {
  return num > 1 && (num == 2 || ((num & 1) && !isOn(num)));
}

int main()
{

}
