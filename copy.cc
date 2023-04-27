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
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m), b(m), c(m);
    for (int i = 0; i < m; ++i) {
      cin >> a[i] >> b[i] >> c[i];
      --a[i];
      --b[i];
    }
    vector<int> e(k);
    for (auto& i : e) {
      cin >> i;
      --i;
    }
    const long long inf = 1e18;
    vector<long long> dp(n, inf);
    dp[0] = 0;
    for (int i = 0; i < k; ++i) {
      int j = e[i];
      dp[b[j]] = min(dp[b[j]], dp[a[j]] + 1ll * c[j]);
    }
    if (dp[n - 1] >= inf) {
      dp[n - 1] = -1;
    }
    cout << dp[n - 1] << '\n';
  }
  return 0;
}
