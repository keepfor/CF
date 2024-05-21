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

template <class T, int MOD>
struct StringHashing {
  int n;
  vector<T> h;
  vector<T> p;
  const T mod = MOD;

  void init(string s) {
    this->n = s.size();
    const T ba = 256;
    h.assign(n + 1, 0);
    p.assign(n + 1, 1);
    for (int i = 0; i < n; ++i) {
      p[i + 1] = p[i] * ba % mod;
      h[i + 1] = ((h[i] * ba % mod) + s[i]) % mod;
    }
  }
  T get(int left, int right) {
    T len = right - left + 1;
    T ans = h[right + 1] - (h[left] * p[len] % mod);
    if (ans < 0) {
      ans += mod;
    }
    return ans % mod;
  }
};

const int md1 = 1e9 + 7;
const int md2 = 1e9 + 9;

void Solver::Solve() const {
  int n, m;
  cin >> n >> m;
  multiset<pair<ll, ll>> h;
  for (int i = 0; i < n; ++i) {
    string t;
    cin >> t;
    const int z = t.size();
    StringHashing<ll, md1> now;
    now.init(t);
    StringHashing<ll, md2> now1;
    now1.init(t);
    for (int j = 0; j < z; ++j) {
      for (auto& c : {'a', 'b', 'c'}) {
        if (t[j] != c) {
          ll x = now.get(0, j - 1) * now.p[z - j];          
          ll y = now.get(j + 1, z - 1);          
          ll add = c * now.p[z - 1 - j] % now.mod;
          x = ((x + y) % now.mod + add) % now.mod;

          ll xx = now1.get(0, j - 1) * now1.p[z - j];          
          ll yy = now1.get(j + 1, z - 1);          
          ll add1 = c * now1.p[z - 1 - j] % now1.mod;
          xx = ((xx + yy) % now1.mod + add1) % now1.mod;

          h.emplace(x, xx);
        }
      }
    }
  }
  while (m--) {
    string s;
    cin >> s;
    const int sz = s.size();
    StringHashing<ll, md1> now;
    now.init(s);
    ll x = now.get(0, sz - 1);
    StringHashing<ll, md2> now1;
    now1.init(s);
    ll y = now1.get(0, sz - 1);
    auto p = make_pair(x, y);
    const int n = s.size();
    if (h.count(p)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
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

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
