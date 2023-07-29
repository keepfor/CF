#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
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

// Warning: this uses nearly 170 MB for N = 500,000. If low on memory use
// memory_rmq_lca.cc or block_rmq_lca.cc instead
template <typename T, bool maximum_mode = false>
struct RMQ {
  static int highest_bit(unsigned x) {
    return x == 0 ? -1 : 31 - __builtin_clz(x);
  }

  int n = 0;
  vector<T> values;
  vector<vector<int>> range_low;

  RMQ(const vector<T> &_values = {}) {
    if (!_values.empty()) build(_values);
  }

  // Note: when `values[a] == values[b]`, returns b.
  int better_index(int a, int b) const {
    return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a
                                                                          : b;
  }

  void build(const vector<T> &_values) {
    values = _values;
    n = int(values.size());
    int levels = highest_bit(n) + 1;
    range_low.resize(levels);

    for (int k = 0; k < levels; k++) range_low[k].resize(n - (1 << k) + 1);

    for (int i = 0; i < n; i++) range_low[0][i] = i;

    for (int k = 1; k < levels; k++)
      for (int i = 0; i <= n - (1 << k); i++)
        range_low[k][i] = better_index(range_low[k - 1][i],
                                       range_low[k - 1][i + (1 << (k - 1))]);
  }

  // Note: breaks ties by choosing the largest index.
  int query_index(int a, int b) const {
    assert(0 <= a && a < b && b <= n);
    int level = highest_bit(b - a);
    return better_index(range_low[level][a],
                        range_low[level][b - (1 << level)]);
  }

  T query_value(int a, int b) const { return values[query_index(a, b)]; }
};
