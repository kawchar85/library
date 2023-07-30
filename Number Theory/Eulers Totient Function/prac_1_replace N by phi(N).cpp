/*
    Given prime factorization of N.
    In one operation, set N = phi(N)
    How many operation(min) need to make N = 1?

    sol:
    count power of 2.
    phi(P^k) = P^(k-1) * (P-1)

    P-1 will produce new 2...

    https://toph.co/arena?practice=64c662ced1a3e891f412fb70#!/p/64c018d37339732fcbaeebab
*/

#include<bits/stdc++.h>
using namespace std;

#define endl "\n"
#define MOD 998244353
#define MAX 1000002

typedef long long ll;

bool siv[MAX];
vector<ll>prime;
ll cnt[MAX]; // count power of prime

void sieve() {
    for(ll i = 3; i*i < MAX; i += 2)
        if(!siv[i])
            for(ll j = i*i; j < MAX; j += i+i)
                siv[j]=1;
    prime.push_back(2);
    for(int i = 3; i < MAX; i += 2)
        if(!siv[i]) prime.push_back(i);
}

vector< pair< pair<int, int>, int > > fact; // {{p, cnt}, original_power}
void Factorization(ll n, int k) {
    for(auto p : prime) {
        if(p * p > n) break;
        if(n % p == 0) {
            int c = 0;
            while(n % p == 0) {
                c++; n /= p;
            }
            fact.push_back({{p, c},k});
        }
    }
    if(n>1)
        fact.push_back({{n, 1},k});
}

void solve() {
    int k, x;
    vector<int> pr;
    set<int> cur_p;
    ll ans = 0;

    cin >> k;
    for(int i = 0; i < k; i++) {
        cin >> x;
        pr.push_back(x);
        cur_p.insert(x);
    }
    for(int i = 0; i < k; i++) {
        cin >> x;
        cnt[pr[i]] += x;
    }

    if(cnt[2] == 0)
        ans++; //1st operation but no 2 available

    while(true) {
        if(!cur_p.size()) break;
        fact.clear();
        pr.clear();

        for(auto it : cur_p) {
            pr.push_back(it);
        }
        cur_p.clear();

        ans = (ans + cnt[2]) % MOD;

        for(auto p : pr) {
            if(cnt[p]) {
                // cout << p << " --> " << cnt[p] << endl;
                Factorization(p - 1, cnt[p]);
                cnt[p] = 0;
            }
        }

        for(auto cur : fact) {
            auto p = cur.first.first;
            auto c = cur.first.second;
            auto k = cur.second;

            cnt[p] += 1LL * c * k;
            if(cnt[p])
                cur_p.insert(p);
            cnt[p] %= MOD;
        }

    }

    cout << ans << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    sieve();

    int TC = 1;

    //cin>>TC;

    for(int cs = 1; cs <= TC; cs++) {
        //cout << "Case " << cs << ": ";
        solve();
    }

    return 0;
}
