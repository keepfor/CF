#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 4
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  for (int i = 0; i < 100; ++i) {
    debug(i);
  }
  cout << '\n';
}

void SolveAll() {
  int t = 1;
  // cin >> t;
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
