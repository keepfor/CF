#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else 
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n, T, c;
    cin >> n >> T >> c;

    int x = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
      int t; cin >> t;
      if (t > T) {
        ans += max(0, x - c + 1);
        x = 0;
      } else {
        ++x;
      }
    }
    if (x >= c) ans += x - c + 1;
    cout << ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
