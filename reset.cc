#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne(){
  int n;
  cin >> n;
  vector<vector<int>> v(3, vector<int>(n));
  for (int i = 0; i < 3; ++i) {
    for (auto& j : v[i]) {
      cin >> j;
    }
  }
  const int m = 8;
  vector<int> dp(m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      for (int k = 0; k < 3; ++k) {
        if (j >> k & 1 ^ 1) {
          dp[j | (1 << k)] = max(dp[j | (1 << k)], dp[j] + v[k][i]);
        }  
      }
    }
  }
  cout << dp[m - 1] << '\n';
};

void SolveAll() {
  auto t { 1 };
  cin >> t;
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
