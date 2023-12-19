#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

void SolveOne() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto& i : v) cin >> i;
  const int inf = 1e9;
  vector<int> dp(n + 1, inf);
  dp[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    dp[i] = min(dp[i], 1 + dp[i + 1]);
    if (i + v[i] + 1 <= n) {
      dp[i] = min(dp[i], dp[i + v[i] + 1]);
    }
  }
  cout << dp[0] << '\n';
}

void Solve() {
  int t = 1;
  cin >> t;
  while (t--) {
    SolveOne();
  }
}

void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
