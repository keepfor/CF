#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else 
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    char t; 
    cin >> t;
    string x, y;
    cin >> x >> y;
    bool win = false;
    if (x[1] == t and y[1] != t) {
      win = true;
    }
    auto f = [&](char c) -> int {
      if (c == 'T') return 10;
      if (c == 'J') return 11;
      if (c == 'Q') return 12;
      if (c == 'K') return 13;
      if (c == 'A') return 14;
      return int(c - '0');
    };
    if (x[1] == y[1] and f(x[0]) > f(y[0])) {
      win = true;
    }
    cout << (win ? "YES" : "NO") << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
