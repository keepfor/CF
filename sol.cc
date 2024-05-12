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

class Solution {
public:
    vector<int> findPermutation(vector<int>& v) {
        const int n = v.size();
        const int inf = 1e9;
        vector<vector<vector<int>>> dp(1 << n, vector<vector<int>>(n, vector<int>(n, -1)));
        vector<vector<vector<int>>> pre(1 << n, vector<vector<int>>(n, vector<int>(n, -1)));
        function<int(int, int, int)> Dfs = [&](int k, int st, int ed) -> int {
            if (__builtin_popcount(k) == n) {
              return abs(ed - v[st]);
            }
            if (~dp[k][st][ed]) {
              return dp[k][st][ed];
            }
            int ans = inf;
            for (int i = 0; i < n; ++i) {
              if (k >> i & 1) {
                continue;
              }
              int kk = k | 1 << i;
              int t = abs(ed - v[i]) + Dfs(kk, st, i);
              if (t < ans) {
                ans = t;
                pre[k][st][ed] = i;
              }
            }
            return dp[k][st][ed] = ans;
        };
        int st = 0;
        int mn = inf;
        for (int i = 0; i < n; ++i) {
            int t = Dfs(1 << i, i, i);
            if (t < mn) {
                mn = t;
                st = i;
            }
        }
        vector<int> ans{st};
        int now = 1 << st;
        int ed = st;
        while (ans.size() != n) {
          int x = pre[now][st][ed];
          ans.push_back(x);
          now |= 1 << x;
          ed = x;
        }
        return ans;
    }
};

void Solver::Solve() const {
  Solution s;
  vector<int> v{3,8,5,7,10,13,9,4,11,6,2,0,12,1};
  debug(s.findPermutation(v));
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
