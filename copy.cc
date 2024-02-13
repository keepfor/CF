#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  int mn = n;
  for (int x = 1; x < n; ++x) {
    int j = x;
    for (; j < n; ++j) {
      if (s[j] != s[j - x]) {
        break;
      }
    }
    if (j == n) {
      mn = min(mn, x);
    }
  }
  string t = s.substr(n - mn, mn);
  cout << s;
  for (int i = 0; i < k - 1; ++i) {
    cout << t;
  }
  cout << '\n';
}

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
