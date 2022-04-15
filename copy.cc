#include<bits/stdc++.h>

#ifdef LOCAL
#include"debug.h"
#else 
#define debug(...) 0
#endif

using namespace std;

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int case_number = 1; case_number <= tt; case_number++) {
    cout << "Case #" << case_number << ": ";
    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        cin >> a[i][j];
      }
    }
    vector<vector<int>> c(m, vector<int>(m));
    for (int i = 0; i < m; ++i) {
      vector<int> t(n, 1e9);
      for (int j = i; j < m; ++j) {
        for (int k = 0; k < n; ++k) {
          t[k] = min(t[k], a[j][k]);
        }
        c[i][j] = accumulate(t.begin(), t.end(), 0);
      }
    }
    vector<vector<int>> dp(m, vector<int>(m));
    for (int i = m - 1; i >= 0; --i) {
      for (int j = i; j < m; ++j) {
        if (i == j) {
          dp[i][j] = c[i][j];
            continue;
        }
        dp[i][j] = 1e9;
        for (int k = i; k < j; ++k) {
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }
        dp[i][j] -= c[i][j];
      }
    }
    cout << dp[0][m - 1] * 2 << '\n';
  }
  return 0;
}
