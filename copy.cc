#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

void SetIO() { cin.tie(0)->sync_with_stdio(0); }

void SolveOne() {
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  int x = 0;
  for (auto& i : v) {
    cin >> i;
    x = max(x, i);
  }
  ll l = 1, r = 1e12;
  while (l < r) {
    ll mid = (l + r + 1) >> 1;
    bool ok = false;
    for (int i = 0; !ok and i < n; ++i) {
      ll t = mid;
      ll cost = 0;
      for (int j = i; !ok and j < n; ++j) {
        if (t <= v[j]) {
          ok = true;
          if (ok) {
            ok &= cost <= k;
          }
          break;
        }
        cost += 1ll * t - v[j];
        --t;
      }
    }
    if (ok) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  cout << l << '\n';
};

void Solve() {
  int t = 1;
  cin >> t;
  while (t--) {
    SolveOne();
  }
}

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
