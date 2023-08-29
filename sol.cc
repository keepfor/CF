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
    using ll = long long;
    int n;
    cin >> n;
    vector<ll> v(n);
    for (auto& i : v) cin >> i;
    ll mx = *max_element(v.begin(), v.end());
    ll mn = *min_element(v.begin(), v.end());
    ll d = (mx - mn + n - 1) / n;
    if (!d) {
      cout << 0 << '\n';
      return;
    }
    vector<vector<ll>> b(n);
    ll ans = 0;
    ll pre;
    for (auto& i : v) {
      int x = (i - mn) / d;
      if (x == n) --x;
      b[x].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
      if (b[i].empty()) continue;
      ll mx = *max_element(b[i].begin(), b[i].end());
      ll mn = *min_element(b[i].begin(), b[i].end());
      if (i) ans = max(ans, mn - pre);
      pre = mx;
    }
    cout << ans << '\n';
  };

  {
    int tt = 1;
    while (tt--) solve();
  }
  return 0;
}
