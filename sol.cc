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
    int n; cin >> n;
    vector<int> a(n);
    for (auto& i : a) cin >> i;
    string s; cin >> s;
    vector<array<int, 3>> pre(n + 1), suf(n + 1);
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i];
      pre[i + 1][a[i]] += int(s[i] == 'M');
    }
    for (int i = n - 1; i >= 0; --i) {
      suf[i] = suf[i + 1];
      suf[i][a[i]] += int(s[i] == 'X');
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] != 'E') continue;
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          int x = 3;
          for (int y = 0; y < 3; ++y) {
            if (a[i] != y and j != y and k != y) {
              x = y;
              break;
            }
          }
          ans += 1ll * x * pre[i][j] * suf[i + 1][k]; 
        }
      }
    }
    cout << ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
