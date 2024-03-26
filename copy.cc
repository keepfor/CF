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

const int mxn = 2e5;
vector<ll> f(mxn + 1);

void Solver::Solve() const {
  ll n;
  cin >> n;
  if (n > mxn) {
    ll d = n - mxn;
    d = (d + 14) / 15;
    ll x = n - d * 15;
    cout << d + f[x] << '\n';
  } else {
    cout << f[n] << '\n';
  }
}

void Solver::Run() const {
  f.assign(mxn, mxn);
  f[0] = 0;
  for (int i = 1; i <= mxn; ++i) {
    for (ll j : {1, 3, 6, 10, 15}) {
      if (i - j >= 0) {
        f[i] = min(f[i], f[i - j] + 1);
      }
    }
  }
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
