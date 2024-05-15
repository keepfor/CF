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
  string s;
  cin >> s;
  const int n = s.size();
  if (count(s.begin(), s.end(), s.front()) != n) {
    cout << "YES\n";
    string t = s;
    sort(s.begin(), s.end());
    if (t != s) {
      cout << s << '\n';
      return;
    }
    reverse(s.begin(), s.end());
    assert(s != t);
    cout << s << '\n';
    return;
  }
  cout << "NO\n";
}

void Solver::Run() const {
  auto tt{1};
  cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}