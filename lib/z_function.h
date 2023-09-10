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
