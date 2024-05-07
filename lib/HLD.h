#include <bits/stdc++.h>

using i64 = long long;
struct HLD {
  int n;
  std::vector<int> siz, top, dep, parent, in, out, seq;
  std::vector<std::vector<int>> adj;
  int cur;

  HLD() {}
  HLD(int n) { init(n); }
  void init(int n) {
    this->n = n;
    siz.resize(n);
    top.resize(n);
    dep.resize(n);
    parent.resize(n);
    in.resize(n);
    out.resize(n);
    seq.resize(n);
    cur = 0;
    adj.assign(n, {});
  }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void work(int root = 0) {
    top[root] = root;
    dep[root] = 0;
    parent[root] = -1;
    dfs1(root);
    dfs2(root);
  }
  void dfs1(int u) {
    if (parent[u] != -1) {
      adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
    }

    siz[u] = 1;
    for (auto &v : adj[u]) {
      parent[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[adj[u][0]]) {
        std::swap(v, adj[u][0]);
      }
    }
  }
  void dfs2(int u) {
    in[u] = cur++;
    seq[in[u]] = u;
    for (auto v : adj[u]) {
      top[v] = v == adj[u][0] ? top[u] : v;
      dfs2(v);
    }
    out[u] = cur;
  }
  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        u = parent[top[u]];
      } else {
        v = parent[top[v]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }

  int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

  int jump(int u, int k) {
    if (dep[u] < k) {
      return -1;
    }

    int d = dep[u] - k;

    while (dep[top[u]] > d) {
      u = parent[top[u]];
    }

    return seq[in[u] - dep[u] + d];
  }

  bool isAncester(int u, int v) { return in[u] <= in[v] && in[v] < out[u]; }

  int rootedParent(int u, int v) {
    std::swap(u, v);
    if (u == v) {
      return u;
    }
    if (!isAncester(u, v)) {
      return parent[u];
    }
    auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v,
                               [&](int x, int y) { return in[x] < in[y]; }) -
              1;
    return *it;
  }

  int rootedSize(int u, int v) {
    if (u == v) {
      return n;
    }
    if (!isAncester(v, u)) {
      return siz[v];
    }
    return n - siz[rootedParent(u, v)];
  }

  int rootedLca(int a, int b, int c) {
    return lca(a, b) ^ lca(b, c) ^ lca(c, a);
  }
};
template <typename T>
struct Fenwick {
  int n;
  std::vector<T> a;

  Fenwick(int n_ = 0) { init(n_); }

  void init(int n_) {
    n = n_;
    a.assign(n, T{});
  }

  void add(int x, const T &v) {
    for (int i = x + 1; i <= n; i += i & -i) {
      a[i - 1] = a[i - 1] + v;
    }
  }

  T sum(int x) {
    T ans{};
    for (int i = x; i > 0; i -= i & -i) {
      ans = ans + a[i - 1];
    }
    return ans;
  }

  T rangeSum(int l, int r) { return sum(r) - sum(l); }

  int select(const T &k) {
    int x = 0;
    T cur{};
    for (int i = 1 << std::__lg(n); i; i /= 2) {
      if (x + i <= n && cur + a[x + i - 1] <= k) {
        x += i;
        cur = cur + a[x - 1];
      }
    }
    return x;
  }
};

void solve() {
  int q;
  std::cin >> q;

  std::vector<std::array<int, 3>> qry(q);
  std::vector<int> p{-1};
  for (int i = 0; i < q; i++) {
    int o;
    std::cin >> o;

    if (o == 1) {
      int x;
      std::cin >> x;
      x--;
      p.push_back(x);
      qry[i] = {1, int(p.size()) - 1, x};
    } else {
      int x, y;
      std::cin >> x >> y;
      x--;
      qry[i] = {2, x, y};
    }
  }

  int n = p.size();
  HLD t(p.size());
  for (int i = 1; i < p.size(); i++) {
    t.addEdge(p[i], i);
  }

  t.work();

  Fenwick<i64> fen(n);
  for (auto [o, x, y] : qry) {
    if (o == 1) {
      i64 v = fen.sum(t.in[x] + 1);
      fen.add(t.in[x], -v);
      fen.add(t.out[x], v);
    } else {
      fen.add(t.in[x], y);
      fen.add(t.out[x], -y);
    }
  }
  for (int i = 0; i < n; i++) {
    std::cout << fen.sum(t.in[i] + 1) << " \n"[i == n - 1];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
