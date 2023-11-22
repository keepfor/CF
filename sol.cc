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
    vector<int> a(3);
    debug(a);
    a.resize(-1);
    debug(a);
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
