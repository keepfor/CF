#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

void Solve() {
  int n, m, x;
  cin >> n >> m >> x;
  vector<bool> dp(n);
  dp[x - 1] = true;
  for (int i = 0; i < m; ++i) {
    vector<bool> ndp(n);
    int r;
    char c;
    cin >> r >> c;
    for (int j = 0; j < n; ++j) {
      if (!dp[j]) {
        continue;
      }
      if (c == '0' or c == '?') {
        ndp[(j + r) % n] = 1;
      }
      if (c == '1' or c == '?') {
        ndp[(n + j - r) % n] = 1;
      }
    }
    swap(dp, ndp);
  }
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (dp[i]) {
      ans.push_back(i);
    }
  }
  const int z = ans.size();
  cout << z << '\n';
  for (int i = 0; i < z; ++i) {
    cout << ans[i] + 1 << " \n"[i + 1 == z];
  }
}

void Main() {
  auto t{1};
  cin >> t;
  while (t--) {
    Solve();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  Main();
  return 0;
}
