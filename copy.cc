#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  int n;
  cin >> n;
  vector<int> p(n);
  int e = n / 2;
  for (auto& i : p) {
    cin >> i;
  }
  constexpr int inf = 1e9;
  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(n + 1, vector<int>(2, inf)));
  dp[0][0][0] = dp[0][0][1] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      for (int k = 0; k < 2; ++k) {
        int pre = dp[i - 1][j][k];
        if (p[i - 1]) {
          int y = p[i - 1] % 2 == 0;
          dp[i][j + y][y] = min(dp[i][j + y][y], pre + int(k != y));
        } else {
          for (int x = 0; x < 2; ++x) {
            dp[i][j + x][x] = min(dp[i][j + x][x], pre + int(k != x));
          }
        }
      }
    }
  }
  cout << min(dp[n][e][0], dp[n][e][1]) << '\n';
};

void SolveAll() {
  auto t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
