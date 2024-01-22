#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 7
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  using ll = long long;
  int n;
  cin >> n;
  vector<ll> v(n);
  for (auto& i : v) {
    cin >> i;
  }
  if (is_sorted(v.begin(), v.end())) {
    cout << 0 << '\n';
    return;
  }
  if (v[n - 1] < 0 or v[n - 2] > v[n - 1]) {
    cout << -1 << '\n';
    return;
  }
  cout << n - 2 << '\n';
  for (int i = n - 3; i >= 0; --i) {
    cout << i + 1 << ' ' << n - 1 << ' ' << n << '\n';
  }
};

void SolveAll() {
  int t = 1;
  cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}
