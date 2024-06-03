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
  string t;
  cin >> n >> t;
  auto F = [](string& a, string& b) -> bool {
    if (a == b) {
      return true;
    }
    const int x = a.size();
    const int y = b.size();
    if (abs(x - y) > 1) {
      return false;
    }
    int i = 0;
    int j = 0;
    while (i < x and i < y and a[i] == b[i]) {
      ++i;
    }
    while (x - j - 1 >= 0 and y - j - 1 >= 0 and a[x - j - 1] == b[y - j - 1]) {
      ++j;
    }
    return i + j >= (max(x, y) - 1);
  };
  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (F(s, t)) {
      ans.push_back(i + 1);
    }
  }
  const int m = ans.size();
  cout << m << '\n';
  for (int i = 0; i < m; ++i) {
    cout << ans[i] << " \n"[i + 1 == m];
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
