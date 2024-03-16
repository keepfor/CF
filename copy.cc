#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

void Solve() {
  for (int i = 0; i < 1e7; ++i) {
    cout << i << '\n';
  }
}

void Main() {
  auto t{1};
  // cin >> t;
  while (t--) {
    Solve();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

signed main() {
  SetIO();
  Main();
  return 0;
}
