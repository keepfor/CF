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
    long long n;
    cin >> n;

    for (int i = 1;; ++i) {
      if (i >= n) {
        cout << n << '\n';
        return;
      }
      n -= 1ll * i;
    }
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
