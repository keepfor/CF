#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

class ZFunction {
 public:
  ZFunction(string _s) : s(_s) {
    this->n = (int)s.size();
    z.resize(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
      if (i <= r) {
        z[i] = min(r - i + 1, z[i - l]);
      }
      while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
        ++z[i];
      }
      if (i + z[i] - 1 > r) {
        l = i;
        r = i + z[i] - 1;
      }
    }
  }

  vector<int> get() { return z; }

 private:
  string s;
  vector<int> z;
  int n;
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string test = "aaaaaaaaaaaaaaaaaaa";
  ZFunction z(test);
  debug(z.get());
  return 0;
}

// zf[i] = max d, s. t. substr(0, d) == substr(i, d), zf[0] = 0
template <typename I>
vector<int> Z(I first, I last) {
  const size_t n = last - first;
  vector<int> zf(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    zf[i] = max(0, min(r - i, zf[i - l]));
    while (i + zf[i] < n && *(first + zf[i]) == *(first + zf[i] + i)) {
      ++zf[i];
    }
    if (i + zf[i] > r) {
      r = i + zf[i];
      l = i;
    }
  }
  return zf;
}


class Solution {
public:
    int minStartingIndex(string s, string a) {
        string b = a + s;
        auto pre = Z(b.begin(), b.end());
        reverse(s.begin(), s.end());
        reverse(a.begin(), a.end());
        b = a + s;
        auto suf = Z(b.begin(), b.end());
        const int n = s.size();
        const int m = a.size();
        for (int i = m; i < m + n; ++i) {
          if (pre[i] == n) {
            return i - m;
          }
          if (suf[i] + pre[i] == n) {
            return i - m;
          }
        }
        return -1;
    }
};