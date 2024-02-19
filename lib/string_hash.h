#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template <class T>
struct H {
  int n;
  vector<T> h;
  vector<T> p;
  const T mod = 1e9 + 7;

  void init(string s) {
    this->n = s.size();
    const T ba = 256;
    h.assign(n + 1, 0);
    p.assign(n + 1, 1);
    for (int i = 0; i < n; ++i) {
      p[i + 1] = p[i] * ba % mod;
      h[i + 1] = ((h[i] * ba % mod) + s[i]) % mod;
    }
    // debug(h);
    // debug(p);
  }
  T get(int left, int right) {
    T len = right - left + 1;
    T ans = h[right + 1] - (h[left] * p[len] % mod);
    if (ans < 0) {
      ans += mod;
    }
    return ans % mod;
  }
};

class Solution {
 public:
  long long countPrefixSuffixPairs(vector<string>& v) {
    H<ll> h;
    h.init("abab");
    // debug(h.get(0, 1));
    // debug(h.get(2, 3));
    const int n = v.size();
    vector<int> len;
    for (auto& i : v) {
      len.push_back(i.size());
    }
    sort(len.begin(), len.end());
    len.resize(unique(len.begin(), len.end()) - len.begin());
    ll ans = 0;
    map<ll, ll> cnt;
    // debug(len);
    for (auto& i : v) {
      H<ll> h;
      h.init(i);
      const int m = i.size();
      for (auto& j : len) {
        if (j > m) {
          break;
        }
        ll x = h.get(0, j - 1);
        ll y = h.get(m - j, m - 1);
        if (x == y) {
          ans += cnt[x];
        }
      }
      ++cnt[h.get(0, m - 1)];
    }
    return ans;
  }
};

void SolveOne() {
  // vector<int> v{2, 1, 5, 1, 1};
  // vector<int> v{8, 10, 6, 12, 9, 12, 2, 3, 13, 19, 11, 18, 10, 16};
  vector<string> v{"abab", "ab"};
  Solution s;
  debug(s.countPrefixSuffixPairs(v));
};

void SolveAll() {
  auto t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
