#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "lib/debug.h"
#else
#define debug(...)
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n;
    cin >> n;
    if (n == 1) {
      cout << 1 << '\n';
      return;
    }
    std::vector<int> v(n);
    v[0] = 2;
    if (n > 2) v.back() = 3;
    for (int j = 4, i = 0; i < n; ++i) {
      if (i == n / 2)
        cout << 1;
      else if (!v[i]) {
        cout << j;
        ++j;
      } else
        cout << v[i];
      if (i + 1 == n)
        cout << '\n';
      else
        cout << ' ';
    }
  };

  {
    // v2
    int tt = 1;
    cin >> tt;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
