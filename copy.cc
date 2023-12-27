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
  ll n, s;
  cin >> n >> s;
  int x = -1;
  int xx = -1;
  int cnt = -1;
  int ans = -1;
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    ll t;
    cin >> t;
    sum += t;
    if (t > x) {
      x = t;
      xx = i;
    }
    if (sum <= s and i + 1 > cnt) {
      cnt = i + 1;
      ans = -1;
    }
    if (sum - x <= s and i > cnt) {
      cnt = i;
      ans = xx;
    }
  }
  cout << ans + 1 << '\n';
};

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
