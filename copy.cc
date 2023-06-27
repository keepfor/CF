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
    int n, b, p;
    cin >> n >> b >> p;
    
    int n0 = n;

    int ans = 0;
    while (n > 1) {
      int x = 1;
      while (x * 2 <= n) {
        x <<= 1;
      }
      ans += x / 2 + x * b;
      n -= x / 2;
    }
    cout << ans << ' ' << p * n0 << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
