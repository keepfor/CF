#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    using ll = long long;
    ll n, k, g;
    cin >> n >> k >> g;
    ll x = (g - 1) >> 1;
    cout << min((x * n) / g, k) * g << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int tt = 1;
    cin >> tt;
    while (tt--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
