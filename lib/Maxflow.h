template <typename STRING>  
class IsSubstring {
 public:
  vector<int> z_algorithm(const STRING& s) {
    int n = int(s.size());
    if (n == 0) return {};
    vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
      int& k = z[i];
      k = (j + z[j] <= i) ? 0 : min(j + z[j] - i, z[i - j]);
      while (i + k < n && s[k] == s[i + k]) k++;
      if (j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
  }
  bool is_substring(STRING& S, STRING& T) {
    int n = int(S.size()), m = int(T.size());
    STRING ST;
    for (auto&& x: S) ST.push_back(x);
    for (auto&& x: T) ST.push_back(x);
    auto Z = z_algorithm(ST);
    for (int i = n; i < n + m; ++i) {
      if (Z[i] >= n) return true;
    }
    return false;
  }
};

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

/*
constexpr ll inf = numeric_limits<ll>::max();
constexpr int mxn = 250;

void Solver::Solve() const {
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto& i : s) {
        cin >> i;
    }
    vector<ll> a(n);
    MaxFlow<mxn, ll> mf(2 * n + 2);
    int src = 2 * n;
    int t = 2 * n + 1;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += 1ll * a[i];
        mf.addEdge(src, 2 * i, a[i]);
        mf.addEdge(2 * i + 1, t, a[i]);
    }
    IsSubstring<string> is_substring;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j or !is_substring.is_substring(s[i], s[j])) {
                continue;
            }
            if (s[i] == s[j]) {
                if (i < j) {
                    mf.addEdge(2 * i, 2 * j + 1, inf);
                }
            } else {
                mf.addEdge(2 * i, 2 * j + 1, inf);
            }
        }
    }
    ll mxf = mf.go(src,t);
    cout << sum - mxf << '\n';
}
*/