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
  ll a, b;
  cin >> a >> b;
  ll g = gcd(a, b);
  if (a == 1) {
    cout << b * b << '\n';
    return;
  }
  if (g == 1) {
    cout << a * b << '\n';
    return;
  }
  for (int i = 2; i * i <= b; ++i) {
    if (b % i == 0) {
      cout << b * i << '\n';
      return;
    }
  }
  cout << b * b << '\n';
}

void Solve() {
  int t = 1;
  cin >> t;
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
