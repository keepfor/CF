#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

class A {
 public:
  static int x;
  A();
  ~A();
};

void Solve() {
  int A::x = 1;
  debug(A::x);
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
