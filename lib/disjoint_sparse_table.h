#ifndef CP
#define CP
#include <bits/stdc++.h>
using namespace std;
#endif

template <class S, S (*op)(S, S)>
struct DisjointSparseTable {
  const int n;
  const vector<unsigned char> msb;
  const vector<vector<S>> d;
  DisjointSparseTable(vector<S> a) : n(a.size()), msb(build_msb_table(n)), d(build_table(move(a))) {}
 
  vector<unsigned char> build_msb_table(int n) {
    if (n <= 1) return {};
    unsigned char k_max = 32 - __builtin_clz(n - 1);
    vector<unsigned char> res(1 << k_max);
    unsigned char* p = res.data();
    for (unsigned char k = 0; k < k_max; k++) {
      memset(p + (1U << k), k, 1U << k);
    }
    return res;
  }
  vector<vector<S>> build_table(vector<S> a) {
    const int n = a.size();
    vector<vector<S>> res(1);
    if (n >= 2) {
      const int i_max = n - 1, k_max = 32 - __builtin_clz(i_max);
      res.resize(k_max);
      for (int k = 1; k < k_max; k++) {
        vector<S> t(i_max >> k & 1 ? n : i_max & ~0U << k);
        for (int c = 1 << k; c < n; c += 1 << (k + 1)) {
          int l = c - (1 << k);
          int r = min(n, c + (1 << k));
          t[c - 1] = a[c - 1];
          for (int i = c - 2; i >= l; i--) t[i] = op(a[i], t[i + 1]);
          t[c] = a[c];
          for (int i = c + 1; i < r; i++) t[i] = op(t[i - 1], a[i]);
        }
        res[k] = move(t);
      }
    }
    res[0] = move(a);
    return res;
  }
 
  S query(int l, int r) { return query_closed(l, r - 1); }
  S query_closed(int l, int r) {
    assert(0 <= l && l <= r && r < n);
    if (l == r) return d[0][l];
    auto k = msb[l ^ r];
    return op(d[k][l], d[k][r]);
  }
};
