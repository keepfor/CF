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
  string s;
  cin >> n >> s;
  string t = s;
  sort(t.begin(), t.end());
  t.resize(unique(t.begin(), t.end()) - t.begin());
  map<char, char> to;
  int l = 0;
  int r = (int) t.size() - 1;
  while (l <= r) {
    to[t[l]] = t[r];
    char tmp = t[l];
    to[t[r]] = tmp;
    ++l;
    --r;
  }
  for (auto& i : s) {
    i = to[i];
  }
  cout << s << '\n';
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
