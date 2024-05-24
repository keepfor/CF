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
    vector<int> a(n);
    for (auto& i : a) {
        cin >> i;
    }
    vector<int> dp;
    vector<int> l(n);
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(dp.begin(), dp.end(), a[i]);
        l[i] = int(it - dp.begin());
        if (it == dp.end()) {
            dp.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    int x = dp.size();
    dp.clear();
    for (int i = n - 1; i >= 0; --i) {
        auto it = lower_bound(dp.begin(), dp.end(), -a[i]);
        r[i] = int(it - dp.begin());
        if (it == dp.end()) {
            dp.push_back(-a[i]);
        } else {
            *it = -a[i];
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (l[i] + r[i] + 1 == x) {
            ans.push_back(i + 1);
        }
    }
    const int z = ans.size();
    cout << z << '\n';
    for (int i = 0; i < z; ++i) {
        cout << ans[i] << " \n"[i + 1 == z];
    }
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
