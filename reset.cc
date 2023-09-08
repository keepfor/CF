#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  auto SolveOne = []() -> void {
  };
  auto Solve = [&SolveOne]() -> void {
    int i = 1;
    while (i--) SolveOne();
  };
  SetIO();
  Solve();
  return 0;
}
