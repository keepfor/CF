/**
 *    author:  tourist
 *    created: 01.06.2024 08:10:03
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

typedef int64_t tp;
typedef tree<tp,null_type,less<tp>,rb_tree_tag,tree_order_statistics_node_update> pbds;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int q;
  int64_t k;
  cin >> q >> k;
  const int64_t inf = int64_t(4e18);
  set<int64_t> starts;
  pbds vals;
  vals.insert(-inf);
  vals.insert(+inf);
  starts.insert(+inf);
  auto Add = [&](int64_t x, int64_t y) {
    assert(x < y);
    if (y - x > k) {
      starts.insert(y);
    }
  };
  auto Remove = [&](int64_t x, int64_t y) {
    assert(x < y);
    if (y - x > k) {
      starts.erase(y);
    }
  };
  for (int iter = 0; iter < q; iter++) {
    int op;
    int64_t x;
    cin >> op >> x;
    if (op == 1) {
      auto it = vals.find(x);
      if (it == vals.end()) {
        it = vals.lower_bound(x);
        Remove(*prev(it), *it);
        Add(*prev(it), x);
        Add(x, *it);
        vals.insert(x);
      } else {
        Remove(*prev(it), *it);
        Remove(*it, *next(it));
        Add(*prev(it), *next(it));
        vals.erase(it);
      }
    } else {
      auto it = starts.upper_bound(x);
      cout << vals.order_of_key(*it) - vals.order_of_key(*prev(it)) << '\n';
    }
  }
  return 0;
}


#include <bits/stdc++.h>

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef int64_t tp;
typedef tree<tp,null_type,less<tp>,rb_tree_tag,tree_order_statistics_node_update> pbds;

using ll = int64_t;
constexpr ll inf = 4e18;

void Solver::Solve() const {
  int q;
  ll k;
  cin >> q >> k;
  set<ll> st;
  st.insert(inf);
  pbds vis;
  vis.insert(inf);
  vis.insert(-inf);
  auto Del = [&](ll l, ll r) -> void {
    if (r - l > k) {
      st.erase(r);
    }
  };
  auto Add = [&](ll l, ll r) -> void {
    if (r - l > k) {
      st.insert(r);
    }
  };
  while (q--) {
    int t;
    ll x;
    cin >> t >> x;
    if (t == 1) {
      auto it = vis.find(x);
      if (it == vis.end()) {
        auto right = vis.upper_bound(x);
        auto pre = *prev(right);
        Del(pre, *right);
        Add(pre, x);
        Add(x, *right);
        vis.insert(x);
      } else {
        auto pre = *prev(it);
        auto nx = *next(it);
        Del(pre, *it);
        Del(*it, nx);
        Add(pre, nx);
        vis.erase(x);
      }
    } else {
      auto it = st.upper_bound(x);
      ll ans = vis.order_of_key(*it) - vis.order_of_key(*prev(it));
      cout << ans << '\n';
    }
  }
}

void Solver::Run() const {
  auto tt{1};
  // cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { 
  cin.tie(0)->sync_with_stdio(0); 
}

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}