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
    int n; cin >> n;
    vector<int> x(5 + 1);
    vector<int> y(5 + 1);
    for (int i = 0; i < n; ++i) {
      int t; cin >> t;
      ++x[t];
    }
    for (int i = 0; i < n; ++i) {
      int t; cin >> t;
      ++y[t];
    }
    int ans = 0;
    for (int i = 1; i <= 5; ++i) {
      if ((x[i] + y[i]) & 1) {
        cout << -1 << '\n';
        return;
      }
      ans += abs(x[i] - (x[i] + y[i]) / 2);
    }
    cout << ans / 2 << '\n';
  };

  {
    int TC = 1;

    for (int i = 1; i <= TC; ++i) {
      solve();
    }
  }

  return 0;
}
