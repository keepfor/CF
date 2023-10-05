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
    tuple<int, int, int> t(1, 2, 3);
    int a, b, c;
    tie(a, b, c) = t;
    cout << a << ' ' << b << ' ' << c << '\n';
    ++a;
    ++b;
    ++c;
    cout << a << ' ' << b << ' ' << c << '\n';
    cout << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << '\n';
  };
  auto Solve = [&SolveOne]() -> void {
    int t = 1;
    while (t--) {
      SolveOne();
    }
  };
  SetIO();
  Solve();
  return 0;
}
