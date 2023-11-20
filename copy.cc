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
    int n;
    cin >> n;
    using ll = long long;
    vector<ll> a(n);
    for (auto& i : a) {
      cin >> i;
    }
    sort(a.begin(), a.end());
    const ll inf = 1e18;
    ll v = inf;
    ll cnt = 0;
    for (int i = 0; i + 1 < n; ++i) {
      ll d = a[i + 1] - a[i];
      if (d < v) {
        v = d;
        cnt = 1;
      } else if (d == v) {
        ++cnt;
      }
    }
    cout << v << ' ' << cnt << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int tt = 1;
    while (tt--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
