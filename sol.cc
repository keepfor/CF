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
  // hello
  ll n, p, le, t;
  cin >> n >> p >> le >> t;
  debug(n);
  ll l = 0;
  ll r = n;
  while (l < r) {
    ll mid = (l + r) >> 1;
    ll cur = min((n + 6) / 7, mid * 2) * t + le * mid;
    if (cur < p)
      l = mid + 1;
    else
      r = mid;
  }
  cout << n - r << '\n';
};

void Solve() {
  int t = 1;
  cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() {
  cin.tie(0)->sync_with_stdio(0);
}

int32_t main() {
  SetIO();
  Solve();
  return 0;
}
