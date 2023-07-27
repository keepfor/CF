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
    double n, m, h;
    cin >> n >> m >> h;
    --h;
    double sum = 0;
    vector<double> b(m);
    for (int i = 0; i < m; ++i) {
      cin >> b[i];
      if (i == h) b[i] -= 1;
      sum += b[i];
    }
    if (sum < n - 1) {
      cout << -1 << '\n';
      return;
    }
    double ans = 1;
    for (int i = 0; i < n - 1; ++i) {
      ans *= (sum - b[h] - i) / (sum - i);
    }
    cout << fixed << setprecision(10) << 1.0 - ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
