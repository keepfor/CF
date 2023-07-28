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
    int n;
    cin >> n;
    cerr << n;
    debug(n);
    debug(n);
    debug(n);
    //vector<vector<long long>> b(n, vector<long long>(n));
    //vector<vector<long long>> s(n, vector<long long>(n));
    //for (auto& i : b) for (auto& j : i) cin >> j;
    //vector<int> p(n);
    //for (int i = n - 1; i >= 0; --i) cin >> p[i];
    //for (int i = 0; i < n; ++i) {
    //  for (int j = 0; j < n; ++j) {
    //    s[i][j] = b[p[i]][p[j]];
    //  }
    //}
    //for (int k = 0; k < n; ++k) {
    //  for (int i = 0; i < n; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //      if (i != j and s[i][k] + s[k][j] < s[i][j]) {
    //        s[i][j] = s[i][k] + s[k][j];
    //      }
    //    }
    //  }
    //  long long ans = 0;
    //  for (int i = 0; i <= k; ++i) {
    //    ans += s[i][k] + s[k][i];
    //  }
    //  cout << ans << '\n';
    //}
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
