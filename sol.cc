#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  auto SolveOne = []() -> void {
    using ll = int64_t;
    pair<ll, ll> mx{0, 0};
    pair<ll, ll> x{0, 0};
    pair<ll, ll> y{0, 0};
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
      pair<ll, ll> p;
      cin >> p.first >> p.second;
      if (p.second > mx.second) {
        if (p.first == mx.first) {
          x = mx;
        } else {
          y = mx;
        }
        mx = p;
      } else {
        if (p.first == mx.first) {
          x = p;
        } else {
          y = p;
        }
      }
      if (y.second) ans = max(ans, y.second + mx.second);
      if (x.second) ans = max(ans, mx.second + x.second / 2);
    }
    cout << ans << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int i = 1;
    while (i--) SolveOne();
  };
  SetIO();
  Solve();
  return 0;
}
