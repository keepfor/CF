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
    int n;
    cin >> n;
    vector<int> a(n);
    long long s = 0;
    for (auto& i : a) {
      cin >> i;
      s += 1ll * abs(i);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      if (a[i] >= 0) continue;
      int j = i;
      while (j < n and a[j] <= 0) {
        ++j;
      }
      ++ans;
      i = j - 1;
    }
    cout << s << ' ' << ans << '\n';
  };

  {
    int tt = 1;
    cin >> tt;
    while (tt--) {
      solve();
    }
  }

  return 0;
}
