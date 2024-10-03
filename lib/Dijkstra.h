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

void Solver::Solve() const {
  int n, m, h;
  cin >> n >> m >> h;
  vector<int> a(h);
  vector<vector<pair<int, ll>>> g(n + n);
  for (auto &i : a) {
    cin >> i;
    --i;
    g[i].push_back({i + n, 0});
  }
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    --u;
    --v;
    g[u].push_back({v, w});
    g[v].push_back({u, w});
    g[u + n].push_back({v + n, w / 2});
    g[v + n].push_back({u + n, w / 2});
  }
  auto c = dijkstra<ll>(0, g);
  auto d = dijkstra<ll>(n - 1, g);
  const ll inf = 2e18;
  ll ans = inf;
  for (int i = 0; i < n; ++i) {
    if (c[i] >= inf || d[i] >= inf) continue;
    ans = min(ans, max(min(c[i], c[i + n]), min(d[i], d[i + n])));
  }
  if (ans >= inf) {
    ans = -1;
  }
  cout << ans << '\n';
}

void Solver::Run() const {
  auto tt{1};
  cin >> tt;
  while (tt--) {
    Solve();
  }
}

inline void Solver::SetIO() const { cin.tie(0)->sync_with_stdio(0); }

void Solver::Main() const {
  SetIO();
  Run();
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
  Fun fun_;

 public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}
  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};
template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename... Args>
ostream &operator<<(ostream &os, const tuple<Args...> &t) {
  os << '(';
  apply(
      [&os](const Args &...args) {
        size_t n = 0;
        ((os << args << (++n != sizeof...(Args) ? ", " : "")), ...);
      },
      t);
  return os << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '{';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}
#ifdef NEAL_DEBUG
#define dbg(...)                                                               \
  cerr << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", \
      dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

template <typename T_weight>
struct Dijkstra {
  const T_weight W_INF = numeric_limits<T_weight>::max() / 2;

  struct edge {
    int node = -1;
    T_weight weight = 0;

    edge() {}

    edge(int _node, T_weight _weight) : node(_node), weight(_weight) {}
  };

  struct state {
    T_weight dist;
    int node;

    state() {}

    state(T_weight _dist, int _node) : dist(_dist), node(_node) {}

    bool operator<(const state &other) const { return dist > other.dist; }
  };

  int n;
  vector<vector<edge>> adj;
  vector<T_weight> dist;
  vector<int> parent;

  Dijkstra(int _n = 0) { init(_n); }

  void init(int _n) {
    n = _n;
    adj.assign(n, {});
  }

  void add_directional_edge(int a, int b, T_weight weight) {
    adj[a].emplace_back(b, weight);
  }

  void add_bidirectional_edge(int a, int b, T_weight weight) {
    add_directional_edge(a, b, weight);
    add_directional_edge(b, a, weight);
  }

  void dijkstra_check(priority_queue<state> &pq, int node, int from,
                      T_weight new_dist) {
    if (new_dist < dist[node]) {
      dist[node] = new_dist;
      parent[node] = from;
      pq.emplace(new_dist, node);
    }
  }

  void dijkstra(const vector<int> &source) {
    if (n == 0) return;
    dist.assign(n, W_INF);
    parent.assign(n, -1);
    priority_queue<state> pq;

    for (int src : source) dijkstra_check(pq, src, -1, 0);

    while (!pq.empty()) {
      state top = pq.top();
      pq.pop();

      if (top.dist > dist[top.node]) continue;

      for (edge &e : adj[top.node])
        dijkstra_check(pq, e.node, top.node, top.dist + e.weight);
    }
  }
};

const int64_t INF64 = int64_t(2e18) + 5;

void run_case() {
  int N, M, H;
  cin >> N >> M >> H;
  Dijkstra<int64_t> dijkstra(2 * N);

  for (int i = 0; i < N; i++) dijkstra.add_directional_edge(N + i, i, 0);

  for (int i = 0; i < H; i++) {
    int a;
    cin >> a;
    a--;
    dijkstra.add_directional_edge(a, N + a, 0);
  }

  for (int i = 0; i < M; i++) {
    int u, v;
    int64_t w;
    cin >> u >> v >> w;
    u--;
    v--;
    dijkstra.add_bidirectional_edge(u, v, w);
    dijkstra.add_bidirectional_edge(N + u, N + v, w / 2);
  }

  dijkstra.dijkstra({0});
  vector<int64_t> dist0 = dijkstra.dist;
  dijkstra.dijkstra({N - 1});
  vector<int64_t> dist1 = dijkstra.dist;
  int64_t best = INF64;

  for (int i = 0; i < N; i++) best = min(best, max(dist0[i], dist1[i]));

  cout << (best < INF64 ? best : -1) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
#ifndef NEAL_DEBUG
  cin.tie(nullptr);
#endif

  int tests;
  cin >> tests;

  while (tests-- > 0) run_case();
}
