#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include"./lib/debug.h"
#else 
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int TESTCASE = 1;
  while (TESTCASE--) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    const long long inf = 1e18;
    vector<long long> dp(m + 1, -inf);
    dp[0] = 0;
    for (auto& i : a) {
      for (int j = m - 1; j >= 0; --j) {
        dp[j + 1] = max(dp[j + 1], dp[j] + 1ll * (j + 1) * i);
      }
    }
    cout << dp[m] << '\n';
  }
  return 0;
}
