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
    int h, n;
    cin >> h >> n;
    deque<int> d;
    for (int i = 0; i < n; ++i) {
      int t;
      cin >> t;
      d.push_back(t);
    }
    d.push_back(0);
    d.push_back(0);
    d.push_back(0);
    int ans = 0;
    while (d.size()) {
      d.pop_front();
      auto y = d.front();\
      if (!y) break;
      d.pop_front();
      auto z = d.front();
      if (y - z > 1) {
        ++ans;
        d.push_front(h + 1);
      }
    }
    cout << ans << '\n';
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
