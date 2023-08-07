#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    int n;
    string s;
    cin >> n >> s;
    for (int i = 1; i < n; ++i) {
      if (s[i] != s[i - 1]) {
        rotate(s.begin(), s.begin() + i, s.end());
        break;
      }
    }
    int ans = 0;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      if (i and s[i - 1] != s[i]) {
        if (i == n) ans += (cnt + 2) / 3;
        else ans += cnt / 3;
        cnt = 1;
      } else {
        ++cnt;
      }
    }
    cout << ans << '\n';
  };

  {
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
  }
  return 0;
}
