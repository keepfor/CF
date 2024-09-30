/**
 *    author:  tourist
 *    created: 08.04.2024 10:55:02
 **/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class hungarian {
 public:
  int n;
  int m;
  vector<vector<T>> a;
  vector<T> u;
  vector<T> v;
  vector<int> pa;
  vector<int> pb;
  vector<int> way;
  vector<T> minv;
  vector<bool> used;
  T inf;

  hungarian(int _n, int _m) : n(_n), m(_m) {
    assert(n <= m);
    a = vector<vector<T>>(n, vector<T>(m));
    u = vector<T>(n + 1);
    v = vector<T>(m + 1);
    pa = vector<int>(n + 1, -1);
    pb = vector<int>(m + 1, -1);
    way = vector<int>(m, -1);
    minv = vector<T>(m);
    used = vector<bool>(m + 1);
    inf = numeric_limits<T>::max();
  }

  inline void add_row(int i) {
    fill(minv.begin(), minv.end(), inf);
    fill(used.begin(), used.end(), false);
    pb[m] = i;
    pa[i] = m;
    int j0 = m;
    do {
      used[j0] = true;
      int i0 = pb[j0];
      T delta = inf;
      int j1 = -1;
      for (int j = 0; j < m; j++) {
        if (!used[j]) {
          T cur = a[i0][j] - u[i0] - v[j];
          if (cur < minv[j]) {
            minv[j] = cur;
            way[j] = j0;
          }
          if (minv[j] < delta) {
            delta = minv[j];
            j1 = j;
          }
        }
      }
      for (int j = 0; j <= m; j++) {
        if (used[j]) {
          u[pb[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      j0 = j1;
    } while (pb[j0] != -1);
    do {
      int j1 = way[j0];
      pb[j0] = pb[j1];
      pa[pb[j0]] = j0;
      j0 = j1;
    } while (j0 != m);
  }

  inline T current_score() { return -v[m]; }

  inline T solve() {
    for (int i = 0; i < n; i++) {
      add_row(i);
    }
    return current_score();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
      cin >> s[i];
    }
    vector<int> x(k), y(k), p(k);
    for (int i = 0; i < k; i++) {
      cin >> x[i] >> y[i] >> p[i];
      --x[i];
      --y[i];
    }
    const int MAX = 20;
    hungarian<int64_t> h(MAX, k + MAX);
    int64_t p3 = 1;
    for (int r = 1; r <= MAX; r++) {
      p3 *= 3;
      for (int i = 0; i < k; i++) {
        int64_t v = p3;
        for (int dx = -r; dx <= r; dx++) {
          for (int dy = -r; dy <= r; dy++) {
            if (dx * dx + dy * dy <= r * r) {
              int nx = x[i] + dx;
              int ny = y[i] + dy;
              if (nx >= 0 && ny >= 0 && nx < n && ny < m) {
                if (s[nx][ny] == '#') {
                  v -= p[i];
                }
              }
            }
          }
        }
        h.a[r - 1][i] = v;
      }
    }
    cout << -h.solve() << '\n';
  }
  return 0;
}

namespace ksun {
#include <bits/stdc++.h>
using namespace std;

template <typename T> struct Point {
public:
  T x, y;
  Point() : x(0), y(0) {}
  Point(T x_, T y_) : x(x_), y(y_) {}
  template <typename U> explicit Point(const Point<U>& p) : x(p.x), y(p.y) {}
  Point(const std::pair<T, T>& p) : x(p.first), y(p.second) {}
  Point(const std::complex<T>& p) : x(real(p)), y(imag(p)) {}
  explicit operator std::pair<T, T> () const { return std::pair<T, T>(x, y); }
  explicit operator std::complex<T> () const { return std::complex<T>(x, y); }

  friend std::ostream& operator << (std::ostream& o, const Point& p) { return o << '(' << p.x << ',' << p.y << ')'; }
  friend std::istream& operator >> (std::istream& i, Point& p) { return i >> p.x >> p.y; }
  friend bool operator == (const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
  friend bool operator != (const Point& a, const Point& b) { return !(a==b); }

  Point operator + () const { return Point(+x, +y); }
  Point operator - () const { return Point(-x, -y); }

  Point& operator += (const Point& p) { x += p.x, y += p.y; return *this; }
  Point& operator -= (const Point& p) { x -= p.x, y -= p.y; return *this; }
  Point& operator *= (const T& t) { x *= t, y *= t; return *this; }
  Point& operator /= (const T& t) { x /= t, y /= t; return *this; }

  friend Point operator + (const Point& a, const Point& b) { return Point(a.x+b.x, a.y+b.y); }
  friend Point operator - (const Point& a, const Point& b) { return Point(a.x-b.x, a.y-b.y); }
  friend Point operator * (const Point& a, const T& t) { return Point(a.x*t, a.y*t); }
  friend Point operator * (const T& t ,const Point& a) { return Point(t*a.x, t*a.y); }
  friend Point operator / (const Point& a, const T& t) { return Point(a.x/t, a.y/t); }

  T dist2() const { return x * x + y * y; }
  auto dist() const { return std::sqrt(dist2()); }
  Point unit() const { return *this / this->dist(); }
  auto angle() const { return std::atan2(y, x); }

  T int_norm() const { return __gcd(x,y); }
  Point int_unit() const { if (!x && !y) return *this; return *this / this->int_norm(); }

  // Convenient free-functions, mostly for generic interop
  friend auto norm(const Point& a) { return a.dist2(); }
  friend auto abs(const Point& a) { return a.dist(); }
  friend auto unit(const Point& a) { return a.unit(); }
  friend auto arg(const Point& a) { return a.angle(); }
  friend auto int_norm(const Point& a) { return a.int_norm(); }
  friend auto int_unit(const Point& a) { return a.int_unit(); }

  Point perp_cw() const { return Point(y, -x); }
  Point perp_ccw() const { return Point(-y, x); }

  friend T dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
  friend T cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
  friend T cross3(const Point& a, const Point& b, const Point& c) { return cross(b-a, c-a); }

  // Complex numbers and rotation
  friend Point conj(const Point& a) { return Point(a.x, -a.y); }

  // Returns conj(a) * b
  friend Point dot_cross(const Point& a, const Point& b) { return Point(dot(a, b), cross(a, b)); }
  friend Point cmul(const Point& a, const Point& b) { return dot_cross(conj(a), b); }
  friend Point cdiv(const Point& a, const Point& b) { return dot_cross(b, a) / b.norm(); }

  // Must be a unit vector; otherwise multiplies the result by abs(u)
  Point rotate(const Point& u) const { return dot_cross(conj(u), *this); }
  Point unrotate(const Point& u) const { return dot_cross(u, *this); }

  friend bool lex_less(const Point& a, const Point& b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
  }

  friend bool same_dir(const Point& a, const Point& b) { return cross(a,b) == 0 && dot(a,b) > 0; }

  // check if 180 <= s..t < 360
  friend bool is_reflex(const Point& a, const Point& b) { auto c = cross(a,b); return c ? (c < 0) : (dot(a, b) < 0); }

  // operator < (s,t) for angles in [base,base+2pi)
  friend bool angle_less(const Point& base, const Point& s, const Point& t) {
    int r = is_reflex(base, s) - is_reflex(base, t);
    return r ? (r < 0) : (0 < cross(s, t));
  }

  friend auto angle_cmp(const Point& base) {
    return [base](const Point& s, const Point& t) { return angle_less(base, s, t); };
  }
  friend auto angle_cmp_center(const Point& center, const Point& dir) {
    return [center, dir](const Point& s, const Point& t) -> bool { return angle_less(dir, s-center, t-center); };
  }

  // is p in [s,t] taken ccw? 1/0/-1 for in/border/out
  friend int angle_between(const Point& s, const Point& t, const Point& p) {
    if (same_dir(p, s) || same_dir(p, t)) return 0;
    return angle_less(s, p, t) ? 1 : -1;
  }
};

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

using ld = long double;

ld MAX = 1e18;

pair<ld, vi> hungarian(const vector<vector<ld>> &a) {
  if (a.empty()) return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  vector<ld> u(n), v(m);
  vi p(m), ans(n - 1);
  rep(i,1,n) {
    p[0] = i;
    int j0 = 0; // add "dummy" worker 0
    vector<ld> dist(m, MAX);
    vi pre(m, -1);
    vector<bool> done(m + 1);
    do { // dijkstra
      done[j0] = true;
      int i0 = p[j0], j1;
      ld delta = MAX;
      rep(j,1,m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta) delta = dist[j], j1 = j;
      }
      rep(j,0,m) {
        if (done[j]) u[p[j]] += delta, v[j] -= delta;
        else dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) { // update alternating path
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  rep(j,1,m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans}; // min cost
}

using P = Point<ll>;

int main(){
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int N;
  cin >> N;
  vector<P> A(N), B(N);
  for(int i = 0; i < N; i++) cin >> A[i];
  for(int i = 0; i < N; i++) cin >> B[i];
  vector<vector<ld>> C(N, vector<ld>(N));
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      C[i][j] = (A[i] - B[j]).dist();
    }
  }
  auto [ans, match] = hungarian(C);
  for(int i = 0; i < N; i++){
    cout << (match[i] + 1) << " \n"[i == N-1];
  }
}
}