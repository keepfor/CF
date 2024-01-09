#include <bits/stdc++.h>

#ifdef DEBUG
#include "lib/debug.cc"
#else
#define debug(...) 0
#endif

using namespace std;

void SolveOne() {
  int n, k, x;
  cin >> n >> k >> x;
  vector<int> v(n);
  for (auto& i : v) {
    cin >> i;
  }
  auto get = [&](vector<int> t) -> int {
    vector<pair<int, int>> st;
    int res = 0;
    for (int i = 0; i < n + 1; ++i) {
      if (st.size()) {
        if (st.back().first == t[i]) {
          st.back().second += 1;
        } else {
          if (st.back().second >= 3) {
            res += st.back().second;
            st.pop_back();
          }
          if (st.back().first == t[i]) {
            st.back().second += 1;
          } else {
            st.emplace_back(t[i], 1);
          }
        }
      } else {
        st.emplace_back(t[i], 1);
      }
    }
    while (st.size() and st.back().second >= 3) {
      res += st.back().second;
      st.pop_back();
    }
    return res;
  };
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    vector<int> t;
    for (int j = 0; j < i; ++j) {
      t.push_back(v[j]);
    }
    t.push_back(x);
    for (int j = i; j < n; ++j) {
      t.push_back(v[j]);
    }
    int res = get(t) - 1;
    ans = max(ans, res);
  }
  cout << ans << '\n';
};

void SolveAll() {
  int t = 1;
  // cin >> t;
  while (t--) {
    SolveOne();
  }
}

inline void SetIO() { cin.tie(0)->sync_with_stdio(0); }

int32_t main() {
  SetIO();
  SolveAll();
  return 0;
}