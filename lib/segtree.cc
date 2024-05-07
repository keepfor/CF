#include <bits/stdc++.h>

using namespace std;

class segtree {
 public:
  struct node {
    int val = -1;
    int mn = -1;

    void apply(int l, int r, int v) {
      val = v;
      mn = v;
    }
  };

  node unite(const node &a, const node &b) const {
    node res;
    res.mn = min(a.mn, b.mn);
    return res;
  }

  inline void push(int x, int l, int r) {}

  inline void pull(int x, int z) { tree[x] = unite(tree[x + 1], tree[z]); }

  int n;
  vector<node> tree;

  void build(int x, int l, int r) {
    if (l == r) {
      return;
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    build(x + 1, l, y);
    build(z, y + 1, r);
    pull(x, z);
  }

  template <typename M>
  void build(int x, int l, int r, const vector<M> &v) {
    if (l == r) {
      tree[x].apply(l, r, v[l]);
      return;
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    build(x + 1, l, y, v);
    build(z, y + 1, r, v);
    pull(x, z);
  }

  node get(int x, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr) {
      return tree[x];
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    push(x, l, r);
    node res{};
    if (rr <= y) {
      res = get(x + 1, l, y, ll, rr);
    } else {
      if (ll > y) {
        res = get(z, y + 1, r, ll, rr);
      } else {
        res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
      }
    }
    pull(x, z);
    return res;
  }

  template <typename... M>
  void modify(int x, int l, int r, int ll, int rr, const M &...v) {
    if (ll <= l && r <= rr) {
      tree[x].apply(l, r, v...);
      return;
    }
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    push(x, l, r);
    if (ll <= y) {
      modify(x + 1, l, y, ll, rr, v...);
    }
    if (rr > y) {
      modify(z, y + 1, r, ll, rr, v...);
    }
    pull(x, z);
  }

  int find_first_knowingly(int x, int l, int r,
                           const function<bool(const node &)> &f) {
    if (l == r) {
      return l;
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res;
    if (f(tree[x + 1])) {
      res = find_first_knowingly(x + 1, l, y, f);
    } else {
      res = find_first_knowingly(z, y + 1, r, f);
    }
    pull(x, z);
    return res;
  }

  int find_first(int x, int l, int r, int ll, int rr,
                 const function<bool(const node &)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[x])) {
        return -1;
      }
      return find_first_knowingly(x, l, r, f);
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res = -1;
    if (ll <= y) {
      res = find_first(x + 1, l, y, ll, rr, f);
    }
    if (rr > y && res == -1) {
      res = find_first(z, y + 1, r, ll, rr, f);
    }
    pull(x, z);
    return res;
  }

  int find_last_knowingly(int x, int l, int r,
                          const function<bool(const node &)> &f) {
    if (l == r) {
      return l;
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res;
    if (f(tree[z])) {
      res = find_last_knowingly(z, y + 1, r, f);
    } else {
      res = find_last_knowingly(x + 1, l, y, f);
    }
    pull(x, z);
    return res;
  }

  int find_last(int x, int l, int r, int ll, int rr,
                const function<bool(const node &)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[x])) {
        return -1;
      }
      return find_last_knowingly(x, l, r, f);
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int z = x + ((y - l + 1) << 1);
    int res = -1;
    if (rr > y) {
      res = find_last(z, y + 1, r, ll, rr, f);
    }
    if (ll <= y && res == -1) {
      res = find_last(x + 1, l, y, ll, rr, f);
    }
    pull(x, z);
    return res;
  }

  segtree(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(2 * n - 1);
    build(0, 0, n - 1);
  }

  template <typename M>
  segtree(const vector<M> &v) {
    n = v.size();
    assert(n > 0);
    tree.resize(2 * n - 1);
    build(0, 0, n - 1, v);
  }

  node get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(0, 0, n - 1, ll, rr);
  }

  node get(int p) {
    assert(0 <= p && p <= n - 1);
    return get(0, 0, n - 1, p, p);
  }

  template <typename... M>
  void modify(int ll, int rr, const M &...v) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    modify(0, 0, n - 1, ll, rr, v...);
  }

  // find_first and find_last call all FALSE elements
  // to the left (right) of the sought position exactly once

  int find_first(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_first(0, 0, n - 1, ll, rr, f);
  }

  int find_last(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_last(0, 0, n - 1, ll, rr, f);
  }
};

class SegTreeLazy {
 public:
  using ll = long long;
  const ll mod = 1e9 + 7;
  const int n = 1e5 + 1;

  vector<ll> tr;
  vector<ll> tag;
  SegTreeLazy() {
    tr.assign(n << 2, 0);
    tag.assign(n << 2, 0);
  }
  void push(int no, int l, int r) {
    tag[2 * no] += tag[no];
    tag[2 * no + 1] += tag[no];
    tr[no] += tag[no] * (r - l + 1);
    tag[no] = 0;
  }
  ll get(int no, int l, int r, int ql, int qr) {
    if (l > r) {
      return 0;
    }
    if (r < ql or qr < l) {
      return 0;
    }
    if (ql <= l and r <= qr) {
      ll res = tr[no] + (r - l + 1) * tag[no];
      return res;
    }
    push(no, l, r);
    int mid = (l + r) >> 1;
    return get(2 * no, l, mid, ql, qr) + get(2 * no + 1, mid + 1, r, ql, qr);
  }
  void pull(int no, int l, int r, int mid) {
    tr[no] = tr[2 * no] + tag[2 * no] * (mid - l + 1) + tr[2 * no + 1] +
             (r - mid) * tag[2 * no + 1];
  }
  void set(int no, int l, int r, int ql, int qr, ll val) {
    if (l > r) {
      return;
    }
    if (r < ql or qr < l) {
      return;
    }
    if (ql == qr and ql == l and l == r) {
      tr[no] += val;
      return;
    }
    if (ql <= l and r <= qr) {
      tag[no] += val;
      return;
    }
    int mid = (l + r) >> 1;
    set(2 * no, l, mid, ql, qr, val);
    set(2 * no + 1, mid + 1, r, ql, qr, 1);
    pull(no, l, r, mid);
  }
  class Solution {
   public:
    int sumCounts(vector<int> &v) {
      using ll = long long;
      const ll mod = 1e9 + 7;
      const int n = v.size();
      int mx = *max_element(v.begin(), v.end());
      SegTreeLazy seg;
      ll ans = 0;
      ll sum = 0;
      vector<int> pre(mx + 1, -1);
      for (int i = 0; i < n; ++i) {
        int p = pre[v[i]];
        int ql = p + 1;
        ll x = seg.get(1, 0, n - 1, ql, i);
        sum = (sum + 2 * x + (i - ql + 1)) % mod;
        ans = (ans + sum) % mod;
        seg.set(1, 0, n - 1, ql, i, 1);
        pre[v[i]] = i;
      }
      return ans;
    }
  };
};

class SegTree {
 public:
  vector<int> seg;
  int n;
  SegTree(vector<int> v) {
    this->n = (int)v.size();
    seg.resize(n << 2);
    for (int i = 0; i < n; ++i) {
      Add(0, 0, n - 1, i, v[i]);
    }
  }
  void Add(int nd, int l, int r, int x, int y) {
    if (l > r) {
      return;
    }
    if (x > r or x < l) {
      return;
    }
    if (x == l and l == r) {
      seg[nd] = y;
      return;
    }
    int mid = (l + r) >> 1;
    Add(2 * nd + 1, l, mid, x, y);
    Add(2 * nd + 2, mid + 1, r, x, y);
    seg[nd] = max(seg[2 * nd + 1], seg[2 * nd + 2]);
  }
  int GetFirstGreater(int nd, int l, int r, int x, int y) {
    if (l > r) {
      return -1;
    }
    if (x > r) {
      return -1;
    }
    if (seg[nd] <= y) {
      return -1;
    }
    if (l == r) {
      return l;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
      int res = GetFirstGreater(2 * nd + 1, l, mid, x, y);
      if (res != -1) {
        return res;
      }
    }
    return GetFirstGreater(2 * nd + 2, mid + 1, r, x, y);
  }

  class Solution {
   public:
    vector<int> leftmostBuildingQueries(vector<int> &v,
                                        vector<vector<int>> &q) {
      const int n = q.size();
      SegTree segtree(v);
      vector<int> ans(n);
      for (int i = 0; i < n; ++i) {
        int x = q[i][0];
        int y = q[i][1];
        if (x > y) {
          swap(x, y);
        }
        if (x == y) {
          ans[i] = x;
        } else if (v[x] < v[y]) {
          ans[i] = y;
        } else {
          ans[i] = segtree.GetFirstGreater(0, 0, segtree.n - 1, y + 1, v[x]);
        }
      }
      return ans;
    }
  };
};
