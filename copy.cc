#include <bits/stdc++.h>

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

using namespace std;

void SolveOne() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto& i : v) {
    cin >> i;
  }
  using ll = long long;
  vector<ll> dp(n);
  dp[0] = 1;
  const ll mod = 998244353;
  const int z = 401;
  vector<vector<ll>> b(z + 1, vector<ll>(z + 1));
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < z; ++j) {
      dp[i] = (dp[i] + b[j][i % j]) % mod;
    }
    ans = (ans + dp[i]) % mod;
    if (v[i] < z) {
      b[v[i]][i % v[i]] = (b[v[i]][i % v[i]] + dp[i]) % mod;
    } else {
      for (int j = i + v[i]; j < n; j += v[i]) {
        dp[j] = (dp[j] + dp[i]) % mod;
      }
    }
  }
  cout << ans << '\n';
};

void SolveAll() {
  int test_case_num = 1;
  // cin >> test_case_num;
  while (test_case_num--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}
