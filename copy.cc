#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (!a[i]) {
      continue;
    }
    a[i] += a[i - 1];
  }
  vector<int> b(m + 1);
  for (int i = 1; i <= m; ++i) {
    cin >> b[i];
    if (!b[i]) {
      continue;
    }
    b[i] += b[i - 1];
  }
  using ll = long long;
  ll ans = 0;
  auto G = [&](int x, int y) -> ll {
    if (x > n or y > m) {
      return 0;
    }
    int c = 0;
    for (int i = x; i <= n; ++i) {
      if (a[i] - a[i - x] == x) {
        ++c;
      }
    }
    int d = 0;
    for (int i = y; i <= m; ++i) {
      if (b[i] - b[i - y] == y) {
        ++d;
      }
    }
    return (ll)c * d;
  };
  for (int i = 1; i * i <= k; ++i) {
    if (k % i) {
      continue;
    }
    ans += G(k / i, i);
    if (k / i != i) {
      ans += G(i, k / i);
    }
  }
  cout << ans << '\n';
};

void SolveAll() {
  auto t{1};
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  SolveAll();
  return 0;
}
