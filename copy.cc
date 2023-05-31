#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include"lib/debug.h"
#else 
#define debug(...) 
#endif

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  auto solve = [&]() {
    int n, k;
    cin >> n >> k;
    long long sum = 0;
    long long m = 0;
    vector<int> g(n);
    for (auto& i : g) {
      cin >> i;
    }
    for (int i = 0; i < n; ++i) {
      sum += g[i];
      for (int j = i + 1; j < n; ++j) {
        m += 1ll * g[i] * g[j];
      }
    }
    vector<long long> ans(k);
    if (k == 1) {
      if (!sum) {
        if (!m) {
          ans[0] = 0;
        } else {
          cout << "impossible\n";
          return;
        }
      } else {
        if (abs(m) % abs(sum) == 0) {
          ans[0] = -m / sum;
        } else {
          cout << "IMPOSSIBLE\n";
          return;
        }
      }
    } else {
      ans[0] = -sum + 1;
      ans[1] = -sum * 1ll + (1ll * sum * sum - m);
    }
    for (int i = 0; i < k; ++i) {
      cout << ans[i] << " \n"[i + 1 == k];
    }
  };

  int TC = 1;
  cin >> TC;

  for (int i = 1; i <= TC; ++i) {
    cout << "Case #" << i << ": ";
    solve();
  }
  
  return 0;
}
