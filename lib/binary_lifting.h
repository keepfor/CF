#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

class BinaryLifting {
 private:
  int n, l;
  int timer;
  vector<vector<int>> adj;
  vector<int> tin, tout;
  vector<vector<int>> up;

 public:
  void dfs(int v, int p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i) {
      up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto& u : adj[v]) {
      if (u != p) {
        dfs(u, v);
      }
    }
  };

  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] and tout[u] >= tout[v];
  };

  void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
  }
};

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  return 0;
}
