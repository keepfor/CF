#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

using ll = long long;

class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
      return 0;
    }
};

class Solver {
 public:
  inline void Main() const {
    SetIO();
    Run();
  }

 private:
  inline void SetIO() const {
    cin.tie(0)->sync_with_stdio(0);
  }
  void Solve() const;
  void Run() const;
};

using ll = long long;

void Solver::Solve() const {
  Solution s;
  vector<vector<int>> t{{3,10},{5,15},{10,2},{4,4}};
  debug(s.minimumDistance(t));
}

void Solver::Run() const {
  auto tt{1};
  //cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
