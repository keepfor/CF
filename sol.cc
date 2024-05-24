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

template<int MAXN, typename T>
class MaxFlow {
 public: 
  class E {
   public:
    T x, inv, cap, flow;
    E(T t, T c, T z) : x(t), inv(z), cap(c), flow(0) {}
    T rest() const { return cap - flow; }
  };

  vector <E> g[MAXN];
  MaxFlow(T v_) : v(v_) {}
  void addEdge(T a, T b, T ab, T ba = 0) {
    T as = g[a].size(), bs = g[b].size();
    g[a].push_back({ b, ab, bs });
    g[b].push_back({ a, ba, as });
  }
  
  T go(T s, T t) {
    T res = 0, tmp = 0;
    while (bfs(s, t)) {
      memset(e_try, 0, sizeof(e_try));
      do {
        tmp = dfs(s, t, numeric_limits<T>::max());
        res += tmp;
      } while (tmp);
    }
    return res;
  }
 private:
  T v, d[MAXN], e_try[MAXN];
  bool bfs(T s, T t) {
    memset(d, -1, sizeof(d));
    queue <T> q; q.push(s);
    d[s] = 0;
    while (!q.empty()) {
      T x = q.front(); q.pop();
      for (auto &e : g[x]) {
        if (d[e.x] == -1 && e.rest() > 0) {
          d[e.x] = d[x] + 1;
          q.push(e.x);
        }
      }
    }
    return d[t] != -1;
  }
  T dfs(T x, T t, T flow) {
    if (x == t) return flow;
    for (T& i = e_try[x]; i < g[x].size(); i++) {
      E &e = g[x][i];
      if (e.rest() > 0 && d[e.x] == d[x] + 1) {
        T tmp = dfs(e.x, t, min(flow, e.rest()));
        if (tmp > 0) {
          E &re = g[e.x][e.inv];
          e.flow += tmp;
          re.flow = -e.flow;
          return tmp;
        }
      }
    }
    return 0;
  }
};

constexpr ll inf = 1e18;
constexpr int mxn = 1e18;

void Solver::Solve() const {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& i : s) {
        cin >> i;
    }
    vector<int> a(n);
    MaxFlow<mxn, ll> mf;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];

    }

}

void Solver::Run() const {
  auto tt{1};
  cin >> tt;
  while (tt--) {
    Solve();
  }
}

signed main() {
  Solver solver;
  solver.Main();
  return 0;
}