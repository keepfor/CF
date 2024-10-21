/**
 *    author:  tourist
 *    created: 01.06.2024 08:24:33
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
struct TPoint {
  T x;
  T y;
  int id;

  TPoint() : x(0), y(0), id(-1) {}
  TPoint(const T& x_, const T& y_) : x(x_), y(y_), id(-1) {}
  TPoint(const T& x_, const T& y_, int id_) : x(x_), y(y_), id(id_) {}

  static constexpr T eps = static_cast<T>(1e-9);

  inline TPoint operator+(const TPoint& rhs) const { return TPoint(x + rhs.x, y + rhs.y); }
  inline TPoint operator-(const TPoint& rhs) const { return TPoint(x - rhs.x, y - rhs.y); }
  inline TPoint operator*(const T& rhs) const { return TPoint(x * rhs, y * rhs); }
  inline TPoint operator/(const T& rhs) const { return TPoint(x / rhs, y / rhs); }

  friend T smul(const TPoint& a, const TPoint& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend T vmul(const TPoint& a, const TPoint& b) {
    return a.x * b.y - a.y * b.x;
  }

  inline T abs2() const {
    return x * x + y * y;
  }

  inline bool operator<(const TPoint& rhs) const {
    return (x < rhs.x || (x == rhs.x && y < rhs.y));
  }

  inline bool is_upper() const {
    return (y > eps || (abs(y) <= eps && x > eps));
  }

  inline int cmp_polar(const TPoint& rhs) const {
    assert(abs(x) > eps || abs(y) > eps);
    assert(abs(rhs.x) > eps || abs(rhs.y) > eps);
    bool a = is_upper();
    bool b = rhs.is_upper();
    if (a != b) {
      return (a ? -1 : 1);
    }
    long long v = x * rhs.y - y * rhs.x;
    return (v > eps ? -1 : (v < -eps ? 1 : 0));
  }
};

using Point = TPoint<int64_t>;

template <typename T>
string to_string(const TPoint<T>& p) {
  return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Point> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].x >> p[i].y;
  }
  sort(p.begin(), p.end());
  p.insert(p.begin(), Point(0, 0));
  int sz = 1;
  for (int i = 1; i <= n; i++) {
    if (p[i].y <= p[sz - 1].y) {
      continue;
    }
    while (sz >= 2 && vmul(p[sz - 1] - p[sz - 2], p[i] - p[sz - 1]) >= 0) {
      sz -= 1;
    }
    p[sz++] = p[i];
  }
  p.resize(sz);
  p.push_back(Point(p.back().x, 0));
  int tt;
  cin >> tt;
  while (tt--) {
    Point q;
    cin >> q.x >> q.y;
    if (vmul(q, p[1]) < 0) {
      cout << -1 << '\n';
      continue;
    }
    int low = 1, high = sz - 1;
    while (low < high) {
      int mid = (low + high + 1) >> 1;
      if (vmul(q, p[mid]) >= 0) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }
    int64_t a = q.y;
    int64_t b = -q.x;
    int64_t c = 0;
    int64_t A = p[low + 1].y - p[low].y;
    int64_t B = p[low].x - p[low + 1].x;
    int64_t C = -A * p[low].x - B * p[low].y;
    int64_t d = a * B - A * b;
    assert(d != 0);
    long double dy = (long double) (__int128(c) * A - __int128(a) * C) / (long double) d;
    if (low == sz - 1) {
      dy = p[low].y;
    }
    cout << fixed << setprecision(17) << (long double) q.y / dy << '\n';
  }
  return 0;
}
