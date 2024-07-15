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

template<typename T> 
vector<T> Dijkstra(vector<vector<pair<T, T>>>& g, int st=0) {
  const int n = g.size();
  vector<T> dist(n, std::numeric_limits<T>::max());
  dist[st] = 0;
  multiset<pair<T, T>> mn;
  mn.emplace(0, st);
  while (mn.size()) {
    auto [now, u] = *mn.begin();    
    mn.erase(mn.begin());
    if (dist[u] != now) {
      continue;
    }
    for (auto& [v, w] : g[u]) {
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        mn.emplace(dist[v], v);
      }
    }
  }
  return dist;
}

void Solver::Solve() const {
  using ll = long long;
  const ll inf = 1e18;
  int n, m;
  cin >> n >> m;
  vector<ll> a(n);
  for (auto& i : a) {
    cin >> i;
  }
  vector<vector<pair<ll, ll>>> g(n);
  for (int i = 0; i < m; ++i) {
    ll u, v, b;
    cin >> u >> v >> b;
    --u; --v;
    g[u].emplace_back(v, a[v] + b);
    g[v].emplace_back(u, a[u] + b);
  }
  vector<ll> dist = Dijkstra<ll>(g);
  for (int i = 1; i < n; ++i) {
    cout << dist[i] + a[0] << " \n"[i + 1 == n];
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

inline void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}