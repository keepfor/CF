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
  using ull = unsigned long long;
  ull a, b;
  cin >> a >> b;
  ull y = a + b;
  ull x = a - b;
  if (x & 1 or y & 1) {
    cout << -1 << '\n';
  } else {
    cout << x / 2 << ' ' << y / 2 << '\n';
  }
};

void Solve() {
  int t = 1;
  while (t--) {
    SolveOne();
  }
}

void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
