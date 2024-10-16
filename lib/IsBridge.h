#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...)
#endif

class Solver {
 public:
  void Main() const;

 private:
  void SetIO() const;
  void Run() const;
  void Solve() const;
};

using ll = int64_t;

template <typename T>
vector<T> dijkstra(int s, vector<vector<pair<int, T>>> g) {
  const T inf = std::numeric_limits<T>::max();
  const int n = (int)g.size();
  vector<T> dis(n, inf);
  vector<int> vis(n);
  priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
  dis[s] = 0, pq.push({0, s});
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto &[v, w] : g[u])
      if (d + w < dis[v]) {
        dis[v] = d + w;
        pq.push({dis[v], v});
      }
  }
  return dis;
}

class IsBridge {
 public:
  map<int, map<int, int>> is_bridge;
  void IS_BRIDGE(int v,int to) {
    is_bridge[v][to] = is_bridge[to][v] = 1; 
  }
  int n;
  vector<vector<int>> adj; 

  vector<bool> visited;
  vector<int> tin, low;
  int timer;

  IsBridge(int n_, vector<vector<int>> adj_) : 
    n(n_),
    adj(adj_) {}

  void dfs(int v, int p = -1) {
      visited[v] = true;
      tin[v] = low[v] = timer++;
      bool parent_skipped = false;
      for (int to : adj[v]) {
          if (to == p && !parent_skipped) {
              parent_skipped = true;
              continue;
          }
          if (visited[to]) {
              low[v] = min(low[v], tin[to]);
          } else {
              dfs(to, v);
              low[v] = min(low[v], low[to]);
              if (low[to] > tin[v])
                  IS_BRIDGE(v, to);
          }
      }
  }

  void find_bridges() {
      timer = 0;
      visited.assign(n, false);
      tin.assign(n, -1);
      low.assign(n, -1);
      for (int i = 0; i < n; ++i) {
          if (!visited[i])
              dfs(i);
      }
  }
};

void Solver::Solve() const {
  int n, m;
  cin >> n >> m;
  vector<int> a(m);
  vector<int> b(m);
  vector<int> c(m);
  vector<vector<pair<int, ll>>> g(n);
  for (int i = 0; i < m; ++i) {
    cin >> a[i] >> b[i] >> c[i];
    --a[i];
    --b[i];
    g[a[i]].emplace_back(b[i], c[i]);
    g[b[i]].emplace_back(a[i], c[i]);
  }
  auto d0 = dijkstra(0, g);
  auto dn = dijkstra(n - 1, g);
  auto in = [&](int idx) -> bool {
    int u = a[idx];
    int v = b[idx];
    int w = c[idx];
    if (d0[n - 1] == d0[u] + w + dn[v]) return true;
    if (d0[n - 1] == d0[v] + w + dn[u]) return true;
    return false;
  };
  vector<vector<int>> bb(n);
  for (int i = 0; i < m; ++i) {
    if (in(i)) {
      bb[a[i]].push_back(b[i]);
      bb[b[i]].push_back(a[i]);
    }
  }
  IsBridge isb(n, bb);
  isb.find_bridges();
  for (int i = 0; i < m; ++i) {
    if (in(i) && isb.is_bridge[a[i]][b[i]]) {
      cout << "Yes" << '\n';
    } else {
      cout << "No" << '\n';
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
