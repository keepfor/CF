#include <bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...)
#endif

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(0);

  auto solve = [&]() {
    using ll = long long;
    const long long mod = 998244353;
    int n;
    cin >> n;
    string s;
    cin >> s;
    long long ans = 0;
    char p = '1';
    for (int i = n - 1; i >= 0; --i) {
      ++ans;
      if (p > '1' and s[i] > '1') {
        cout << -1 << '\n';
        return;
      }
      if (i and s[i] > '1') ans = ans * ll(s[i] - '0') % mod;
      p = s[i];
    }
    cout << ans - 1 << '\n';
  };

  {
    int tt = 1;
    while (tt--) solve();
  }
  return 0;
}
