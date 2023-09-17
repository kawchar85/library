//https://cses.fi/problemset/task/2104
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
const int LG = 18;
typedef vector<int> vi;
void induced_sort(const vi &vec, int val_range, vi &SA, const vector<bool> &sl, const vi &lms_idx) {
  vi l(val_range, 0), r(val_range, 0);
  for (int c : vec) {
    if (c + 1 < val_range) ++l[c + 1];
    ++r[c];
  }
  partial_sum(l.begin(), l.end(), l.begin());
  partial_sum(r.begin(), r.end(), r.begin());
  fill(SA.begin(), SA.end(), -1);
  for (int i = lms_idx.size() - 1; i >= 0; --i)
    SA[--r[vec[lms_idx[i]]]] = lms_idx[i];
  for (int i : SA)
    if (i >= 1 && sl[i - 1]) {
      SA[l[vec[i - 1]]++] = i - 1;
    }
  fill(r.begin(), r.end(), 0);
  for (int c : vec)
    ++r[c];
  partial_sum(r.begin(), r.end(), r.begin());
  for (int k = SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
    if (i >= 1 && !sl[i - 1]) {
      SA[--r[vec[i - 1]]] = i - 1;
    }
}

vi SA_IS(const vi &vec, int val_range) {
  const int n = vec.size();
  vi SA(n), lms_idx;
  vector<bool> sl(n);
  sl[n - 1] = 0;
  for (int i = n - 2; i >= 0; --i) {
    sl[i] = (vec[i] > vec[i + 1] || (vec[i] == vec[i + 1] && sl[i + 1]));
    if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
  }
  reverse(lms_idx.begin(), lms_idx.end());
  induced_sort(vec, val_range, SA, sl, lms_idx);
  vi new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
  for (int i = 0, k = 0; i < n; ++i)
    if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
      new_lms_idx[k++] = SA[i];
    }
  int cur = 0;
  SA[n - 1] = cur;
  for (size_t k = 1; k < new_lms_idx.size(); ++k) {
    int i = new_lms_idx[k - 1], j = new_lms_idx[k];
    if (vec[i] != vec[j]) {
      SA[j] = ++cur;
      continue;
    }
    bool flag = 0;
    for (int a = i + 1, b = j + 1;; ++a, ++b) {
      if (vec[a] != vec[b]) {
        flag = 1;
        break;
      }
      if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
        flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
        break;
      }
    }
    SA[j] = (flag ? ++cur : cur);
  }
  for (size_t i = 0; i < lms_idx.size(); ++i)
    lms_vec[i] = SA[lms_idx[i]];
  if (cur + 1 < (int)lms_idx.size()) {
    auto lms_SA = SA_IS(lms_vec, cur + 1);
    for (size_t i = 0; i < lms_idx.size(); ++i) {
      new_lms_idx[i] = lms_idx[lms_SA[i]];
    }
  }
  induced_sort(vec, val_range, SA, sl, new_lms_idx);
  return SA;
}
vector<int> suffix_array(const string &s, const int LIM = 128) {
  vector<int> vec(s.size() + 1);
  copy(begin(s), end(s), begin(vec));
  vec.back() = '$';
  auto ret = SA_IS(vec, LIM);
  ret.erase(ret.begin());
  return ret;
}
struct SuffixArray {
  int n;
  string s;
  vi sa, rank, lcp, lg;
  vector<vi> t;
  SuffixArray() {}
  SuffixArray(string _s) {
    n = _s.size();
    s = _s;
    sa = suffix_array(s);
    rank.resize(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    costruct_lcp();
    prec();
    build();
  }
  void costruct_lcp() {
    //lcp[i] = lcp of suffix started from i and i+1
    int k = 0;
    lcp.resize(n, 0);
    for (int i = 0; i < n; i++) {
      if (rank[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = sa[rank[i] + 1];
      while (i + k < n && j + k < n && s[i + k] == s[j + k])  k++;
      lcp[rank[i]] = k;
      if (k)  k--;
    }
  }
  void prec() {
    lg.resize(n, 0);
    for (int i = 2; i < n; i++) lg[i] = lg[i / 2] + 1;
  }
  void build() {
    int sz = n - 1;
    t.resize(sz);
    for (int i = 0; i < sz; i++) {
      t[i].resize(LG);
      t[i][0] = lcp[i];
    }
    for (int k = 1; k < LG; ++k) {
      for (int i = 0; i + (1 << k) - 1 < sz; ++i) {
        t[i][k] = min(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]);
      }
    }
  }
  int query(int l, int r) { // minimum of lcp[l], ..., lcp[r]
    int k = lg[r - l + 1];
    return min(t[l][k], t[r - (1 << k) + 1][k]);
  }
  int get_lcp(int i, int j) { // lcp of suffix starting from i and j
    if (i == j) return n - i;
    int l = rank[i], r = rank[j];
    if (l > r) swap(l, r);
    return query(l, r - 1);
  }
  int lower_bound(string &t) {
    int l = 0, r = n - 1, k = t.size(), ans = n;
    while (l <= r) {
      int mid = l + r >> 1;
      if (s.substr(sa[mid], min(n - sa[mid], k)) >= t) ans = mid, r = mid - 1;
      else l = mid + 1;
    }
    return ans;
  }
  int upper_bound(string &t) {
    int l = 0, r = n - 1, k = t.size(), ans = n;
    while (l <= r) {
      int mid = l + r >> 1;
      if (s.substr(sa[mid], min(n - sa[mid], k)) > t) ans = mid, r = mid - 1;
      else l = mid + 1;
    }
    return ans;
  }
  // occurrences of s[p, ..., p + len - 1]
  pair<int, int> find_occurrence(int p, int len) {
    p = rank[p];
    pair<int, int> ans = {p, p};
    int l = 0, r = p - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (query(mid, p - 1) >= len) ans.first = mid, r = mid - 1;
      else l = mid + 1;
    }
    l = p + 1, r = n - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (query(p, mid - 1) >= len) ans.second = mid, l = mid + 1;
      else r = mid - 1;
    }
    return ans;
  }
  long long unique_substring() {
    long long cnt = 0;
    for (int i = 0; i < n; i++)
      cnt += (n - sa[i] - lcp[i]);
    return cnt;
  }
};

#define LVL 20 //ceil(log_2(MAXN))+1
int arr[N];
int dst[N][LVL];

int merge(int x, int y) {
    return min(x,y);
}
//0 based
void build(int n){
    for(int i=0; i<n; ++i) dst[i][0] = arr[i];
    for(int k=1; k<LVL; ++k)
        for(int i=0; (i+(1<<k)-1)<n; ++i)
            dst[i][k] = merge(dst[i][k-1], dst[i+(1<<(k-1))][k-1]);
}
int query(int l, int r){
    int k=31-__builtin_clz(r-l+1);
    return merge(dst[l][k], dst[r-(1<<k)+1][k]);
}

int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    string t, s;
    int k;
    cin >> t >> k;
    SuffixArray sa(t);
    for(int i = 0; i < sa.sa.size(); i++) {
        arr[i] = sa.sa[i];
    }
    build(sa.sa.size());
    for(int i = 0; i < k; i++) {
        cin >> s;
        int l = sa.lower_bound(s);
        int r = sa.upper_bound(s);
        if(l == r) cout << "-1\n";
        else cout << query(l, r - 1) + 1<< "\n"; //min query
    }
    return 0;
}
