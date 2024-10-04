#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")

// T: monoid representing information of an interval.
//   T()  should return the identity.
//   T(S s)  should represent a single element of the array.
//   T::pull(const T &l, const T &r)  should pull two intervals.
template <class T> struct SegmentTreePoint {
  int logN, n;
  vector<T> ts;
  SegmentTreePoint() : logN(0), n(0) {}
  explicit SegmentTreePoint(int n_) {
    for (logN = 0, n = 1; n < n_; ++logN, n <<= 1) {}
    ts.resize(n << 1);
  }
  template <class S> explicit SegmentTreePoint(const vector<S> &ss) {
    const int n_ = ss.size();
    for (logN = 0, n = 1; n < n_; ++logN, n <<= 1) {}
    ts.resize(n << 1);
    for (int i = 0; i < n_; ++i) at(i) = T(ss[i]);
    build();
  }
  T &at(int i) {
    return ts[n + i];
  }
  void build() {
    for (int u = n; --u; ) pull(u);
  }

  inline void pull(int u) {
    ts[u].pull(ts[u << 1], ts[u << 1 | 1]);
  }

  // Changes the value of point a to s.
  template <class S> void change(int a, const S &s) {
    assert(0 <= a); assert(a < n);
    ts[a += n] = T(s);
    for (; a >>= 1; ) pull(a);
  }

  // Applies T::f(args...) to point a.
  template <class F, class... Args>
  void ch(int a, F f, Args &&... args) {
    assert(0 <= a); assert(a < n);
    (ts[a += n].*f)(args...);
    for (; a >>= 1; ) pull(a);
  }

  // Calculates the product for [a, b).
  T get(int a, int b) {
    assert(0 <= a); assert(a <= b); assert(b <= n);
    if (a == b) return T();
    T prodL, prodR, t;
    for (a += n, b += n; a < b; a >>= 1, b >>= 1) {
      if (a & 1) { t.pull(prodL, ts[a++]); prodL = t; }
      if (b & 1) { t.pull(ts[--b], prodR); prodR = t; }
    }
    t.pull(prodL, prodR);
    return t;
  }

  // Calculates T::f(args...) of a monoid type for [a, b).
  //   op(-, -)  should calculate the product.
  //   e()  should return the identity.
  template <class Op, class E, class F, class... Args>
#if __cplusplus >= 201402L
  auto
#else
  decltype((std::declval<T>().*F())())
#endif
  get(int a, int b, Op op, E e, F f, Args &&... args) {
    assert(0 <= a); assert(a <= b); assert(b <= n);
    if (a == b) return e();
    auto prodL = e(), prodR = e();
    for (a += n, b += n; a < b; a >>= 1, b >>= 1) {
      if (a & 1) prodL = op(prodL, (ts[a++].*f)(args...));
      if (b & 1) prodR = op((ts[--b].*f)(args...), prodR);
    }
    return op(prodL, prodR);
  }

  // Find min b s.t. T::f(args...) returns true,
  // when called for the partition of [a, b) from left to right.
  //   Returns n + 1 if there is no such b.
  template <class F, class... Args>
  int findRight(int a, F f, Args &&... args) {
    assert(0 <= a); assert(a <= n);
    if ((T().*f)(args...)) return a;
    if (a == n) return n + 1;
    a += n;
    for (; ; a >>= 1) if (a & 1) {
      if ((ts[a].*f)(args...)) {
        for (; a < n; ) {
          if (!(ts[a <<= 1].*f)(args...)) ++a;
        }
        return a - n + 1;
      }
      ++a;
      if (!(a & (a - 1))) return n + 1;
    }
  }

  // Find max a s.t. T::f(args...) returns true,
  // when called for the partition of [a, b) from right to left.
  //   Returns -1 if there is no such a.
  template <class F, class... Args>
  int findLeft(int b, F f, Args &&... args) {
    assert(0 <= b); assert(b <= n);
    if ((T().*f)(args...)) return b;
    if (b == 0) return -1;
    b += n;
    for (; ; b >>= 1) if ((b & 1) || b == 2) {
      if ((ts[b - 1].*f)(args...)) {
        for (; b <= n; ) {
          if (!(ts[(b <<= 1) - 1].*f)(args...)) --b;
        }
        return b - n - 1;
      }
      --b;
      if (!(b & (b - 1))) return -1;
    }
  }
};  // SegmentTreePoint<T>

////////////////////////////////////////////////////////////////////////////////

constexpr Int INF = 1001001001001001001LL;

struct Node {
  int sz;
  Int a[2][2][2];
  Node() : sz(0) {
    init();
  }
  Node(Int val) : sz(1) {
    init();
    chmax(a[0][0][0], 0LL);
    if (val >= 0) {
      chmax(a[1][1][0], 1LL);
      chmax(a[1][1][1], 1LL + val);
    }
  }
  void init() {
    for (int u = 0; u < 2; ++u) for (int v = 0; v < 2; ++v) for (int k = 0; k < 2; ++k) {
      a[u][v][k] = -INF;
    }
  }
  void pull(const Node &l, const Node &r) {
    if (!l.sz) { *this = r; return; }
    if (!r.sz) { *this = l; return; }
    sz = l.sz + r.sz;
    init();
    for (int u = 0; u < 2; ++u) for (int v = 0; v < 2; ++v) {
      for (int w = 0; w < 2; ++w) if (!(v && w)) for (int x = 0; x < 2; ++x) {
        chmax(a[u][x][0], l.a[u][v][0] + r.a[w][x][0]);
        chmax(a[u][x][1], l.a[u][v][0] + r.a[w][x][1]);
        chmax(a[u][x][1], l.a[u][v][1] + r.a[w][x][0]);
      }
    }
  }
};


int N;
vector<Int> A;

int main() {
  for (int numCases; ~scanf("%d", &numCases); ) { for (int caseId = 1; caseId <= numCases; ++caseId) {
    scanf("%d", &N);
    A.resize(N);
    for (int i = 0; i < N; ++i) {
      scanf("%lld", &A[i]);
    }
    
    vector<pair<Int, int>> ais(N);
    for (int i = 0; i < N; ++i) ais[i] = make_pair(A[i], i);
    sort(ais.begin(), ais.end(), greater<pair<Int, int>>{});
    
    SegmentTreePoint<Node> seg(vector<Int>(N, -1));
    Int ans = -INF;
    for (const auto &ai : ais) {
      seg.change(ai.second, ai.first);
      Int score = -INF;
      for (int u = 0; u < 2; ++u) for (int v = 0; v < 2; ++v) {
        chmax(score, seg.ts[1].a[u][v][1]);
      }
// cerr<<ai<<": "<<score<<endl;
      chmax(ans, ai.first + score);
    }
    printf("%lld\n", ans);
  }
#ifndef LOCAL
  break;
#endif
  }
  return 0;
}
