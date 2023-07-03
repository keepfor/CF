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
    int n; cin >> n;
    vector<int> a(n); for (auto& i : a) cin >> i;
    int t = min(n, 2);
    int ans = t;

    for (int i = 2; i < n; ++i) {
      if (a[i] == a[i - 1] + a[i - 2]) {
        ++t;
      } else {
        t = 2;
      }
      ans = max(ans, t);
    }
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
