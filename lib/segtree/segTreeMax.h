#include <bits/stdc++.h>

using namespace std;

class segTreeMax {
 public:
  const int MAXN;
  vector<pair<int, int>> t;
  const int INF = (int)1e9;

  segTreeMax(int MAXN) : MAXN(MAXN) { t.resize(MAXN); }

  // pair<int, int> t[4*MAXN];

  pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if (a.first > b.first) return a;
    if (b.first > a.first) return b;
    return make_pair(a.first, a.second + b.second);
  }

  void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = make_pair(a[tl], 1);
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
  }

  void build(vector<int> a, int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = make_pair(a[tl], 1);
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
  }

  pair<int, int> get_max(int v, int tl, int tr, int l, int r) {
    if (l > r) return make_pair(-INF, 0);
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    return combine(get_max(v * 2, tl, tm, l, min(r, tm)),
                   get_max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
      t[v] = make_pair(new_val, 1);
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
        update(v * 2, tl, tm, pos, new_val);
      else
        update(v * 2 + 1, tm + 1, tr, pos, new_val);
      t[v] = combine(t[v * 2], t[v * 2 + 1]);
    }
  }
};

#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;
vector <vector <int>> g;
vector <int> p, tin, gl, sz;
int cur_time = 0;

void dfs(int v) {
    tin[v] = cur_time++;
    sz[v] = 1;
    for (int i : g[v]) {
        if (i == p[v]) continue;
        p[i] = v;
        gl[i] = gl[v] + 1;
        dfs(i);
        sz[v] += sz[i];
    }
}
const int INF = 1e9;
struct SegTreeMax {
    int len;
    vector <int> t;

    SegTreeMax(int n, const vector <int>& a) {
        len = 1 << (int)ceil(log2(n));
        t.resize(2 * len);
        for (int i = 2 * len - 1; i > 0; --i) {
            if (i >= len) {
                if (i - len < n) t[i] = a[i - len];
            } else {
                t[i] = max(t[2 * i], t[2 * i + 1]);
            }
        }
    }

    inline int get_max(int l, int r) {
        l += len;
        r += len;
        int ans = -INF;
        while (l <= r) {
            if (l & 1) ans = max(ans, t[l++]);
            if (!(r & 1)) ans = max(ans, t[r--]);
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

inline void solve() {
    int n;
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y; --x; --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int x;
    cin >> x >> x; --x;
    tin.assign(n, 0);
    sz.assign(n, 0);
    gl.assign(n, 0);
    p.assign(n, 0);
    cur_time = 0;
    dfs(0);
    vector <int> r(n);
    for (int i = 0; i < n; ++i) {
        r[tin[i]] = gl[i];
    }

    SegTreeMax t(n, r);

    vector <int> max_d(n);
    int cha = x;
    int prv = -1;
    multiset<int> values;
    vector <int> path;

    while (cha > 0) {
        if (prv == -1) {
            max_d[cha] = t.get_max(tin[cha], tin[cha] + sz[cha] - 1) - 2 * gl[cha];
        } else {
            max_d[cha] = max(t.get_max(tin[cha], tin[prv] - 1) - 2 * gl[cha], t.get_max(tin[prv] + sz[prv], tin[cha] + sz[cha] - 1) - 2 * gl[cha]);
        }
        path.push_back(cha);
        values.insert(max_d[cha]);
        prv = cha;
        cha = p[cha];
    }
    path.push_back(0);
    reverse(path.begin(), path.end());
    int cur_alice = 0;
    int cur_bob = (int)path.size() - 1;
    int move = 0;

    while (true) {
        if (move == 0) {
            int alice1 = path[cur_alice];
            int alice2 = path[cur_alice + 1];
            int cnt_alice = max(t.get_max(tin[alice1], tin[alice2] - 1), t.get_max(tin[alice2] + sz[alice2], tin[alice1] + sz[alice1] - 1));
            cnt_alice -= gl[alice1];

            int cnt_bob = gl[path[cur_bob]] + *values.rbegin();
            if (cnt_alice > cnt_bob) {
                cout << "Alice\n";
                return;
            }
            if (cur_alice + 1 == cur_bob) {
                cout << "Bob\n";
                return;
            }
            cur_alice++;
            values.erase(values.find(max_d[path[cur_alice]]));
        } else {
            int alice1 = path[cur_alice];
            int alice2 = path[cur_bob];
            int cnt_alice = max(t.get_max(tin[alice1], tin[alice2] - 1), t.get_max(tin[alice2] + sz[alice2], tin[alice1] + sz[alice1] - 1));
            cnt_alice -= gl[alice1];

            int cnt_bob = max_d[path[cur_bob]] + gl[path[cur_bob]];
            if (cnt_bob > cnt_alice) {
                cout << "Bob\n";
                return;
            }
            if (cur_alice + 1 == cur_bob) {
                cout << "Alice\n";
                return;
            }
            values.erase(values.find(max_d[path[cur_bob]]));
            cur_bob--;
        }

        move ^= 1;
    }
}

int32_t main() {
    if (1) {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
