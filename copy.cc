#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

void SolveOne() {
  // TODO
  ll a, m, l, r;
  cin >> a >> m >> l >> r;
  --l;
  auto f = [&](ll x, ll y) -> ll {
    if (y < 0) {
      y = -y;
      x = -x;
    }
    if (x < 0) {
      return (x - y + 1) / y;
    }
    return x / y;
  };
  cout << f(r - a, m) - f(l - a, m) << '\n';
};

void Solve() {
  int t = 1;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
