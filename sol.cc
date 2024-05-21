#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

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
  int n;
  cin >> n;
  string ans;
  for (int i = 0; i < n; ++i) {
    string t;
    cin >> t;
    t += "@" + ans.substr(max(0, ans.size() - t.size()), t.size());
    const int m = t.size();
    vector<int> lps(m);
    lps[0] = -1;
    for (int j = 1; j < m; ++j) {
      lps[j] = lps[j - 1];
      while (j >= 0 and t[lps[j] + 1] != t[j]) j = lps[j - 1];
      if (t[j] == t[lps[j] + 1]) {
        ++lps[j];
      }
    } 
    for  (int j = lps.back() + 1; 
  }
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
