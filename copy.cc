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
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    vector<int> r(n, -1);
    vector<int> l(n, -1);
    for (int i = n - 1; i >= 0; --i) {
      cin >> s[i];
      for (int j = 0; j < m + 2; ++j) {
        if (s[i][j] == '0') continue;
        if (l[i] == -1) l[i] = j;
        r[i] = j;
      }
    }
    int lst = n - 1;
    while (lst >= 0 and r[lst] == -1) --lst;
    if (lst == -1) {
      cout << 0 << '\n';
      return;
    }
    if (lst == 0) {
      cout << r[0] << '\n';
      return;
    }
    vector<int> dp(2);
    for (int i = 0; i <= lst; ++i) {
      if (r[i] == -1) r[i] = 0;
      if (l[i] == -1) l[i] = 0;
    }
    if (r[0]) dp[0] = 2 * r[0];
    dp[1] = m + 1;
 
    for (int i = 1; i < lst; ++i) {
      vector<int> ndp(2);
      if (!r[i]) {
        ++dp[0];
        ++dp[1];
        continue;
      }
      ndp[0] = min(dp[0] + 1 + 2 * r[i], dp[1] + 1 + m + 1);
      ndp[1] = min(dp[1] + 1 + 2 * (m + 1 - l[i]), dp[0] + 1 + m + 1);
      swap(dp, ndp);
    }
    int ans = min(dp[0] + 1 + r[lst], dp[1] + 1 + m + 1 - l[lst]);
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
