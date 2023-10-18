#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    int x = 11;
    for (int i = x; i; i -= (i & -i)) {
      cout << i << ' ';
    }
    cout << '\n';
    for (int i = x; i; i = (i - 1) & x) {
      cout << i << ' ';
    }
  };
  auto Solve = [&SolveOne]() -> void {
    int tt = 1;
    while (tt--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
