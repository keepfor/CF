#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  cin.tie(0)->sync_with_stdio(0);

  auto solve = [&]() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
      cin >> p[i];
      --p[i];
    }
    int l = 1, r = n - 1;
    while (l < r) {
      int mid = (l + r) >> 1;
      int c = 0;
      vector<int> h(n);
      for (int i = n - 1; i; --i) {
        h[i] += 1;
        if (p[i] and h[i] == mid)
          ++c;
        else
          h[p[i]] = max(h[p[i]], h[i]);
      }
      if (c <= k)
        r = mid;
      else
        l = mid + 1;
    }
    cout << r << '\n';
  };

  {
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
  }
  return 0;
}
