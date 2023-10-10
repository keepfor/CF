#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif
bool isPossible(vector<int>& A) {
  unordered_map<int, int> left, end;
  for (int i : A) {
    left[i]++;
  }
  for (int i : A) {
    cout << i << ',';
    if (left[i] == 0) continue;
    left[i]--;
    if (end[i - 1] > 0) {
      end[i - 1]--;
      end[i]++;
    } else if (left[i + 1] > 0 && left[i + 2] > 0) {
      left[i + 1]--;
      left[i + 2]--;
      end[i + 2]++;
    } else {
      return false;
    }
  }
  return true;
}
int32_t main() {
  auto SetIO = []() -> void { cin.tie(0)->sync_with_stdio(0); };
  SetIO();
  auto SolveOne = []() -> void {
    vector<int> a{4, 4, 3, 3, 2, 2, 1, 1};
    sort(a.begin(), a.end())
    debug(isPossible(a));
  };
  auto Solve = [&SolveOne]() -> void {
    int t = 1;
    while (t--) {
      SolveOne();
    }
  };
  Solve();
  return 0;
}
