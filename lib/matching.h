/**
 *    author:  tourist
 *    created: 16.09.2023 08:03:23       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

class matching {
 public:
  vector<vector<int>> g;
  vector<int> pa;
  vector<int> pb;
  vector<int> was;
  int n, m;
  int res;
  int iter;

  matching(int _n, int _m) : n(_n), m(_m) {
    assert(0 <= n && 0 <= m);
    pa = vector<int>(n, -1);
    pb = vector<int>(m, -1);
    was = vector<int>(n, 0);
    g.resize(n);
    res = 0;
    iter = 0;
  }

  void add(int from, int to) {
    assert(0 <= from && from < n && 0 <= to && to < m);
    g[from].push_back(to);
  }

  bool dfs(int v) {
    was[v] = iter;
    for (int u : g[v]) {
      if (pb[u] == -1) {
        pa[v] = u;
        pb[u] = v;
        return true;
      }
    }
    for (int u : g[v]) {
      if (was[pb[u]] != iter && dfs(pb[u])) {
        pa[v] = u;
        pb[u] = v;
        return true;
      }
    }
    return false;
  }

  int solve() {
    while (true) {
      iter++;
      int add = 0;
      for (int i = 0; i < n; i++) {
        if (pa[i] == -1 && dfs(i)) {
          add++;
        }
      }
      if (add == 0) {
        break;
      }
      res += add;
    }
    return res;
  }

  int run_one(int v) {
    if (pa[v] != -1) {
      return 0;
    }
    iter++;
    return (int) dfs(v);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n = 3;
  int m;
  cin >> m;
  vector<string> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  vector<vector<vector<int>>> pos(n, vector<vector<int>>(10));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int d = (int) (s[i][j] - '0');
      pos[i][d].push_back(j);
    }
  }
  int low = 0, high = n * m;
  while (low < high) {
    int mid = (low + high) >> 1;
    bool ok = false;
    for (int dig = 0; dig < 10; dig++) {
      vector<vector<int>> a(n);
      set<int> all;
      bool fail = false;
      for (int i = 0; i < n; i++) {
        int sz = (int) pos[i][dig].size();
        if (sz == 0) {
          fail = true;
          break;
        }
        for (int j = 0; j < n; j++) {
          int at = pos[i][dig][j % sz] + (j / sz) * m;
          if (at <= mid) {
            a[i].push_back(at);
            all.insert(at);
          }
        }
      }
      if (fail) {
        continue;
      }
      vector<int> v(all.begin(), all.end());
      matching mat(n, (int) v.size());
      for (int i = 0; i < n; i++) {
        for (int j : a[i]) {
          int p = (int) (lower_bound(v.begin(), v.end(), j) - v.begin());
          mat.add(i, p);
        }
      }
      if (mat.solve() == n) {
        ok = true;
        break;
      }
    }
    if (ok) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  cout << (low == n * m ? -1 : low) << '\n';
  return 0;
}
