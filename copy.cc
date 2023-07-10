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
    string s;
    cin >> s;
    int n = (int) s.size();
    vector<vector<int>> nx(n + 1, vector<int>(10, n));
    for (int i = n - 1; i >= 0; --i) {
      nx[i] = nx[i + 1];
      nx[i][s[i] - '0'] = i;
    }
      
    int m;
    cin >> m;
    string x, y;
    cin >> x >> y;

    int p = 0;
    for (int i = 0; i < m; ++i) {
      int l = x[i] - '0';
      int r = y[i] - '0';
      int pp = p;
      for (int j = l; j <= r; ++j) {
        pp = max(pp, nx[p][j]);
        if (pp >= n) break;
      }
      p = pp + 1;
      if (p >= n + 1) break;
    }
    if (p >= n + 1) cout << "YES\n";
    else cout << "NO\n";
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
