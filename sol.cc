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
    int n, k;
    cin >> n >> k;
    if (k > 30) {
      cout << n + 1 << '\n';
    } else {
      cout << min(n + 1, 1 << k) << '\n';
    }
  };

  {
    int tt = 1;
    cin >> tt;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
