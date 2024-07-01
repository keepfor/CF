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

template<typename T> 
class BfsTreeDiameter {
 public:
  BfsTreeDiameter() {}
  int diameter;
  vector<vector<int>> g;
  int m;
  int n;
  BfsTreeDiameter(vector<vector<int>>& x) {
    m = x.size();
    n = 1 + m;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        g[x[i][0]].push_back(x[i][1]);
        g[x[i][1]].push_back(x[i][0]);
    }

    auto [p, d] = Bfs(0);
    auto [pp, dd] = Bfs(p);
    diameter = dd;
  }
  T get() { return diameter; }
 private:
  pair<int, T> Bfs(int st) {
    vector<int> q{st};
    vector<T> dep(n);
    vector<bool> vis(n);
    vis[st] = 1;
    for (int i = 0; i < q.size(); ++i) {
        int u = q[i];
        for (auto v : g[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                dep[v] = dep[u] + 1ll;
                q.push_back(v);
            }
        }
    }
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        if (dep[i] > dep[mx]) {
            mx = i;
        }
    }
    return {mx, dep[mx]};
  }
};

class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& a, vector<vector<int>>& b) {
        BfsTreeDiameter<int> ct(a);
        BfsTreeDiameter<int> dt(b);
        int c = ct.get();
        int d = dt.get();
        return max({c, d, (c + 1) / 2 + (d + 1) / 2 + 1});
    }
};

void Solver::Solve() const {
  vector<vector<int>> a{{0,1},{0,2},{0,3}};
  vector<vector<int>> b{{0,1}};
  Solution sol;
  debug(sol.minimumDiameterAfterMerge(a, b));
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
