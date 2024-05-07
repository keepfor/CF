#include <bits/stdc++.h>

using namespace std;

template <typename T, class F = function<T(const T&, const T&)>>
class SparseTable {
 public:
  int n;
  vector<vector<T>> mat;
  F func;

  SparseTable(const vector<T>& a, const F& f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }

  int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
      int n;
      cin >> n;
      vector<long long> a(n);
      for (int i = 0; i < n; i++) {
        cin >> a[i];
      }
      vector<long long> pref(n + 1);
      for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
      }
      vector<int> b(n);
      iota(b.begin(), b.end(), 0);
      SparseTable<int> sa(b, [&](int i, int j) { return a[i] > a[j] ? i : j; });
      SparseTable<long long> smin(
          pref, [&](long long i, long long j) { return min(i, j); });
      SparseTable<long long> smax(
          pref, [&](long long i, long long j) { return max(i, j); });
      bool ok = true;
      function<void(int, int)> Dfs = [&](int l, int r) {
        if (l > r) {
          return;
        }
        int x = sa.get(l, r);
        long long mn = smin.get(l, x);
        long long mx = smax.get(x + 1, r + 1);
        if (a[x] < mx - mn) {
          ok = false;
        }
        Dfs(l, x - 1);
        Dfs(x + 1, r);
      };
      Dfs(0, n - 1);
      cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
  }
};

namespace leetcode {
class SparseTable {
  using F = function<int(int, int)>;
  vector<vector<int>> v;
  F f;

 public:
  SparseTable(vector<int> x, F f) {
    this->f = f;
    const int n = x.size();
    int lg = 32 - __builtin_clz(n);
    v.resize(lg);
    v[0] = x;
    for (int i = 1; i < lg; ++i) {
      const int m = n - (1 << i) + 1;
      v[i].resize(m);
      for (int j = 0; j < m; ++j) {
        v[i][j] = f(v[i - 1][j], v[i - 1][j + (1 << (i - 1))]);
      }
    }
  }
  int get(int l, int r) {
    assert(l <= r and l >= 0 and r < (int)v[0].size());
    int lg = 31 - __builtin_clz(r - l + 1);
    return f(v[lg][l], v[lg][r - (1 << (lg)) + 1]);
  }
  class Solution {
   public:
    vector<int> leftmostBuildingQueries(vector<int>& v,
                                        vector<vector<int>>& q) {
      const int n = q.size();
      const int m = v.size();
      vector<int> ans(n, -1);
      function<int(int, int)> mx = [&](int a, int b) -> int {
        return max(a, b);
      };
      SparseTable spt(v, mx);
      for (int i = 0; i < n; ++i) {
        int x = q[i][0];
        int y = q[i][1];
        if (x > y) {
          swap(x, y);
        }
        if (x == y) {
          ans[i] = x;
        } else if (v[x] < v[y]) {
          ans[i] = y;
        } else {
          int l = y + 1;
          int r = m;
          int z = v[x];
          while (l < r) {
            int mid = (l + r) >> 1;
            int val = spt.get(l, mid);
            if (val > z) {
              r = mid;
            } else {
              l = mid + 1;
            }
          }
          ans[i] = l == m ? -1 : l;
        }
      }
      return ans;
    }
  };
};
}  // namespace leetcode

template <class T>
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

namespace and_min {
class Solution {
 public:
  const int inf = 1e9;
  int minimumValueSum(vector<int>& a, vector<int>& b) {
    const int n = a.size();
    SparseTable<int> an(a, [](int x, int y) -> int { return x & y; });
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
      SparseTable<int> mn(dp, [](int x, int y) -> int { return min(x, y); });
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
}  // namespace and_min