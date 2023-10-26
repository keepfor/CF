#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    priority_queue<int> q;
    for (int i = 0; i < 10; ++i) {
      q.push(rng() % 100);
    }
    while (q.size()) {
      cout << q.top() << ' ';
      q.pop();
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
