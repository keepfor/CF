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

template<int MAXN>
class MaxFlow {
 public: 
  class E {
   public:
    int x, inv, cap, flow;
    E(int t, int c, int z) : x(t), inv(z), cap(c), flow(0) {}
    int rest() const { return cap - flow; }
  };

  vector <E> g[MAXN];
  MaxFlow(int v_) : v(v_) {}
  void addEdge(int a, int b, int ab, int ba = 0) {
    int as = g[a].size(), bs = g[b].size();
    g[a].push_back({ b, ab, bs });
    g[b].push_back({ a, ba, as });
  }
  
  int go(int s, int t) {
    int res = 0, tmp = 0;
    while (bfs(s, t)) {
      memset(e_try, 0, sizeof(e_try));
      do {
        tmp = dfs(s, t, numeric_limits<int>::max());
        res += tmp;
      } while (tmp);
    }
    return res;
  }
 private:
  int v, d[MAXN], e_try[MAXN];
  bool bfs(int s, int t) {
    memset(d, -1, sizeof(d));
    queue <int> q; q.push(s);
    d[s] = 0;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      for (auto &e : g[x]) {
        if (d[e.x] == -1 && e.rest() > 0) {
          d[e.x] = d[x] + 1;
          q.push(e.x);
        }
      }
    }
    return d[t] != -1;
  }
  int dfs(int x, int t, int flow) {
    if (x == t) return flow;
    for (int& i = e_try[x]; i < g[x].size(); i++) {
      E &e = g[x][i];
      if (e.rest() > 0 && d[e.x] == d[x] + 1) {
        int tmp = dfs(e.x, t, min(flow, e.rest()));
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

using ll = long long;
const int inf = 1e9;

void Solver::Solve() const {
  int n, m;
  cin >> n >> m;
  MaxFlow<205> mf(2 * n + 2);
  int as = 0;
  int bs = 0;
  for (int i = 1; i <= n; ++i) {
    int a;
    cin >> a;
    as += a;
    mf.addEdge(0, i, a);
    mf.addEdge(i, i + n, a);
  } 
  for (int i = 1; i <= n; ++i) {
    int b;
    cin >> b;
    bs += b;
    mf.addEdge(i + n, 2 * n + 1, b);
  }
  if (as != bs) {
    cout << "NO\n";
    return;
  }
  while (m--) {
    int p, q;
    cin >> p >> q;
    mf.addEdge(p, q + n, inf);    
    mf.addEdge(q, p + n, inf);    
  }
  int x = mf.go(0, 2 * n + 1);
  if (x == as and as == bs) {
    cout << "YES\n";
    vector<vector<int>> ans(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
      for (auto& j : mf.g[i]) {
        int b = j.x;
        int w = j.flow;
        if (n + 1 <= b and b <= 2 * n) {
          ans[i][b - n] = w;
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cout << ans[i][j] << " \n"[j == n];
      }
    }
    return;
  } 
  cout << "NO\n";
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
