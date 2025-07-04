#include <bits/stdc++.h>
using namespace std;

const int MAX_PRIME_LIMIT = 1000000;

vector<int> primes;
vector<bool> isPrime;
vector<bool> isPerfectSquareOfPrime;

long long cube(int x) {
    return (long long)x * x * x;
}

void generatePrimesUsingSieve() {
    vector<bool> isComposite(MAX_PRIME_LIMIT, false);
    isPrime.assign(MAX_PRIME_LIMIT, false);
    isPerfectSquareOfPrime.assign((long long)MAX_PRIME_LIMIT * MAX_PRIME_LIMIT + 1, false);
    
    for (int i = 3; i * i < MAX_PRIME_LIMIT; i += 2) {
        if (!isComposite[i]) {
            for (int j = i * i; j < MAX_PRIME_LIMIT; j += 2 * i) {
                isComposite[j] = true;
            }
        }
    }
    
    primes.push_back(2);
    isPrime[2] = true;
    isPerfectSquareOfPrime[4] = true;
    
    for (int i = 3; i < MAX_PRIME_LIMIT; i += 2) {
        if (!isComposite[i]) {
            primes.push_back(i);
            isPrime[i] = true;
            long long primeSquare = (long long)i * i;
            if (primeSquare < isPerfectSquareOfPrime.size()) {
                isPerfectSquareOfPrime[primeSquare] = true;
            }
        }
    }
}

int countDivisors(long long n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    
    int divisorCount = 1;
    long long remainingNumber = n;
    
    for (int i = 0; i < primes.size() && cube(primes[i]) <= remainingNumber; i++) {
        int currentPrime = primes[i];
        int exponent = 0;
        
        while (remainingNumber % currentPrime == 0) {
            exponent++;
            remainingNumber /= currentPrime;
        }
        
        if (exponent > 0) {
            divisorCount *= (exponent + 1);
        }
    }
    
    if (remainingNumber == 1) {
        
    }
    else if (remainingNumber < isPrime.size() && isPrime[remainingNumber]) {
        divisorCount *= 2;
    }
    else if (remainingNumber < isPerfectSquareOfPrime.size() && isPerfectSquareOfPrime[remainingNumber]) {
        divisorCount *= 3;
    }
    else if (remainingNumber != 1) {
        divisorCount *= 4;
    }
    
    return divisorCount;
}
