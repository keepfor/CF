#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <bits/stdc++.h>

using namespace std;

void SolveOne() {
  int n;
  cin >> n;
  set<int> x, y;
  for (int i = 0; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    x.insert(a);
    y.insert(b);
  }
  if (x.size() == 2 and y.size() == 2) {
    int dx = *x.begin() - *next(x.begin());
    int dy = *y.begin() - *next(y.begin());
    cout << abs(dx) * abs(dy) << '\n';
  } else {
    cout << -1 << '\n';
  }
};

void SolveAll() {
  int t{1};
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
