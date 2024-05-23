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
  vector<tuple<int, int, int>> p(n);
  for (int i = 0; i < n; ++i) {
    cin >> get<0>(p[i]) >> get<1>(p[i]);
    get<2>(p[i]) = i;
  }
  sort(p.begin(), p.end());
  reverse(p.begin(), p.end());
  vector<tuple<int, int, int>> st;
  for (auto& [i,j,k] : p) {
    if (st.size() and j > get<1>(st.back())) {
      continue;
    }
    st.push_back(make_tuple(i, j, k));
  }
  sort(st.begin(), st.end(), [&](auto x, auto y) -> bool {
    return get<2>(x) < get<2>(y);
  });
  const int m = st.size();
  cout << m << '\n';
  for (int i = 0; i < m; ++i) {
    cout << get<2>(st[i]) + 1 << " \n"[i + 1 == m];
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
