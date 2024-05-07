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

template<class T>
class SparseTable {
  int n;
  vector<vector<T>> v;
  function<T(T, T)> op;

  public:
    SparseTable(vector<T> a, function<T(T, T)> op_) : op(op_) {
        n = a.size();
        const int m = log2(n) + 1;
        v.resize(m);
        v[0] = a;
        for (int i = 1; i < m; ++i) {
            v[i].resize(n - (1 << i) + 1);
            for (int j = 0; j + (1 << i) <= n; ++j) {
                v[i][j] = op(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T get(int l, int r) {
        assert(l <= r);
        assert(l >= 0);
        assert(r < n);
        const int len = (r - l + 1);
        const int m = log2(len);
        return op(v[m][l], v[m][r - (1 << m) + 1]);
    }
};

class Solution {
public:
    const int inf = 1e9;
    int minimumValueSum(vector<int>& a, vector<int>& b) {
        const int n = a.size();
        SparseTable<int> an(a, [](int x, int y) -> int {
            return x & y;
        });
        vector<int> dp(n, inf);
        const int m = b.size();
        for (int i = 0; i < n; ++i) {
            if (an.get(i, n - 1) == b[m - 1]) {
                dp[i] = a.back();
            }
        }   
        for (int i = m - 2; i >= 0; --i) {
            for (int j = 1; j < n; ++j) {
                if (dp[j] != inf) {
                    dp[j] += a[j - 1];
                }    
            }
            vector<int> ndp(n, inf);
            SparseTable<int> mn(dp, [](int x, int y) -> int {
                return min(x, y);
            });
            for (int j = 0; j < n; ++j) {
                int l = j;
                int r = n - 1;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (an.get(j, mid) <= b[i]) {
                        r = mid;
                    } else {
                        l = mid + 1;
                    }
                }
                assert(j <= l);
                if (an.get(j, l) != b[i]) {
                    continue;
                }
                int fir = l + 1;
                l = j;
                r = n - 1;
                while (l < r) {
                    int mid = (1 + l + r) >> 1;
                    if (an.get(j, mid) >= b[i]) {
                        l = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                assert(j <= l);
                int lst = min(l + 1, n - 1);
                if (fir <= lst) {
                    ndp[j] = mn.get(fir, lst);
                }
            }
            swap(ndp, dp);
        }
        if (dp[0] >= inf) {
            return -1;
        }
        return dp[0];
    }
};

void Solver::Solve() const {
    Solution s;
    vector<int> a{1,4,3,3,2};
    vector<int> b{0,3,3,2};
    debug(s.minimumValueSum(a, b));
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
