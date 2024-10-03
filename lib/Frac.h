namespace Frac {
#include <bits/stdc++.h>

using i64 = long long;
template <class T>
struct Frac {
  T num;
  T den;
  Frac(T num_, T den_) : num(num_), den(den_) {
    if (den < 0) {
      den = -den;
      num = -num;
    }
  }
  Frac() : Frac(0, 1) {}
  Frac(T num_) : Frac(num_, 1) {}
  explicit operator double() const { return 1. * num / den; }
  Frac &operator+=(const Frac &rhs) {
    num = num * rhs.den + rhs.num * den;
    den *= rhs.den;
    return *this;
  }
  Frac &operator-=(const Frac &rhs) {
    num = num * rhs.den - rhs.num * den;
    den *= rhs.den;
    return *this;
  }
  Frac &operator*=(const Frac &rhs) {
    num *= rhs.num;
    den *= rhs.den;
    return *this;
  }
  Frac &operator/=(const Frac &rhs) {
    num *= rhs.den;
    den *= rhs.num;
    if (den < 0) {
      num = -num;
      den = -den;
    }
    return *this;
  }
  friend Frac operator+(Frac lhs, const Frac &rhs) { return lhs += rhs; }
  friend Frac operator-(Frac lhs, const Frac &rhs) { return lhs -= rhs; }
  friend Frac operator*(Frac lhs, const Frac &rhs) { return lhs *= rhs; }
  friend Frac operator/(Frac lhs, const Frac &rhs) { return lhs /= rhs; }
  friend Frac operator-(const Frac &a) { return Frac(-a.num, a.den); }
  friend bool operator==(const Frac &lhs, const Frac &rhs) {
    return lhs.num * rhs.den == rhs.num * lhs.den;
  }
  friend bool operator!=(const Frac &lhs, const Frac &rhs) {
    return lhs.num * rhs.den != rhs.num * lhs.den;
  }
  friend bool operator<(const Frac &lhs, const Frac &rhs) {
    return lhs.num * rhs.den < rhs.num * lhs.den;
  }
  friend bool operator>(const Frac &lhs, const Frac &rhs) {
    return lhs.num * rhs.den > rhs.num * lhs.den;
  }
  friend bool operator<=(const Frac &lhs, const Frac &rhs) {
    return lhs.num * rhs.den <= rhs.num * lhs.den;
  }
  friend bool operator>=(const Frac &lhs, const Frac &rhs) {
    return lhs.num * rhs.den >= rhs.num * lhs.den;
  }
  friend std::ostream &operator<<(std::ostream &os, Frac x) {
    T g = std::gcd(x.num, x.den);
    if (x.den == g) {
      return os << x.num / g;
    } else {
      return os << x.num / g << "/" << x.den / g;
    }
  }
};

using F = Frac<__int128>;
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int N;
  std::cin >> N;

  std::vector<int> X(N), Y(N), Z(N);
  for (int i = 0; i < N; i++) {
    std::cin >> X[i] >> Y[i] >> Z[i];
  }

  int ans = 0;

  std::map<std::array<F, 4>, i64> line;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (X[i] < X[j]) {
        F ky(Y[j] - Y[i], X[j] - X[i]);
        F kz(Z[j] - Z[i], X[j] - X[i]);
        F by = Y[i] - ky * X[i];
        F bz = Z[i] - kz * X[i];
        line[{ky, kz, by, bz}] |= 1LL << j;
      }
    }
  }

  for (auto [_, v] : line) {
    ans = std::max(ans, __builtin_popcountll(v));
  }

  std::map<std::array<F, 3>, i64> point;

  for (auto [a, va] : line) {
    for (auto [b, vb] : line) {
      if (a == b) {
        break;
      }
      F x = 0;
      if (a[0] != b[0]) {
        x = (a[2] - b[2]) / (b[0] - a[0]);
      } else if (a[1] != b[1]) {
        x = (a[3] - b[3]) / (b[1] - a[1]);
      }
      if (x < 0 && a[0] * x + a[2] == b[0] * x + b[2] &&
          a[1] * x + a[3] == b[1] * x + b[3]) {
        point[{x, a[0] * x + a[2], a[1] * x + a[3]}] |= va | vb;
      }
    }
  }
  for (auto [_, v] : point) {
    ans = std::max(ans, __builtin_popcountll(v));
  }

  ans = N - ans;
  std::cout << ans << "\n";

  return 0;
}
}  // namespace Frac

namespace frac {
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for (ll i = (l); i < (r); i++)

using ll = long long;
using point = array<ll, 3>;
using line = array<point, 2>;

class frac {
 public:
  ll nume, deno;

  frac() : nume(0), deno(1) {}
  frac(ll n) : nume(n), deno(1) {}
  frac(ll n, ll d) {
    // assert(d);
    if (d < 0) {
      nume = -n;
      deno = -d;
    } else {
      nume = n;
      deno = d;
    }
  }
  void reduce() {
    ll d = gcd(nume, deno);
    nume /= d;
    deno /= d;
  }
  frac operator-(ll n) { return frac(nume - n * deno, deno); }
  frac operator+(ll n) { return frac(nume + n * deno, deno); }
  frac operator*(frac &x) { return frac(nume * x.nume, deno * x.deno); }
  bool operator<(ll x) { return nume < x * deno; }

  friend bool operator==(const frac &x, const frac &y) {
    return x.nume * y.deno == x.deno * y.nume;
  }
  friend bool operator<(const frac &x, const frac &y) {
    return x.nume * y.deno < y.nume * x.deno;
  }
};

array<frac, 2> get_vec(point &p, point &q) {
  frac dy = frac(p[1] - q[1], p[0] - q[0]);
  frac dz = frac(p[2] - q[2], p[0] - q[0]);
  return {dy, dz};
}

using point_frac = array<frac, 3>;
pair<point_frac, bool> get_intersect(line l1, line l2) {
  // z=0に射影して交点(x,y)を求める。平行でない、x=aの平面上にない
  ll deno = (l1[0][0] - l1[1][0]) * (l2[0][1] - l2[1][1]) -
            (l2[0][0] - l2[1][0]) * (l1[0][1] - l1[1][1]);
  if (!deno) {
    // 平行でない2直線がz=0に射影して平行⇒射影した結果同一直線上にある、すなわち平面px+qy=0上にある
    // 平面x=aの上にないので、y=0に射影すれば平行でない。y,zをswapしてやりなおし
    swap(l1[0][1], l1[0][2]);
    swap(l1[1][1], l1[1][2]);
    swap(l2[0][1], l2[0][2]);
    swap(l2[1][1], l2[1][2]);
    auto [p, f] = get_intersect(l1, l2);
    swap(p[1], p[2]);
    return {p, f};
  }
  ll xnume = l1[0][0] * l2[0][0] * (l1[1][1] - l2[1][1]) -
             l1[0][0] * l2[1][0] * (l1[1][1] - l2[0][1]) -
             l1[1][0] * l2[0][0] * (l1[0][1] - l2[1][1]) +
             l1[1][0] * l2[1][0] * (l1[0][1] - l2[0][1]);
  ll ynume = -(l1[0][1] * l2[0][1] * (l1[1][0] - l2[1][0]) -
               l1[0][1] * l2[1][1] * (l1[1][0] - l2[0][0]) -
               l1[1][1] * l2[0][1] * (l1[0][0] - l2[1][0]) +
               l1[1][1] * l2[1][1] * (l1[0][0] - l2[0][0]));
  frac x = frac(xnume, deno), y = frac(ynume, deno);
  // z座標が等しいか確認
  frac dz1 = frac(l1[0][2] - l1[1][2], l1[0][0] - l1[1][0]);
  frac dz2 = frac(l2[0][2] - l2[1][2], l2[0][0] - l2[1][0]);
  frac z1 = (x - l1[0][0]) * dz1 + l1[0][2];
  frac z2 = (x - l2[0][0]) * dz2 + l2[0][2];
  if (z1 == z2) return {{x, y, z1}, true};
  return {{}, false};
}

int main() {
  int n;
  cin >> n;
  vector<point> p(n);
  rep(i, 0, n) cin >> p[i][0] >> p[i][1] >> p[i][2];

  // 極大な線分を列挙する
  // その直線の端から見たとき何個の点が隠れるか数えておく
  vector<line> L;
  vector<int> count;
  rep(i, 0, n) rep(j, 0, n) {
    if (p[i][0] >= p[j][0]) continue;
    // pix<pjx
    auto dxdy = get_vec(p[i], p[j]);
    int cnt = 0;
    bool ok = true;
    rep(k, 0, n) {
      if (p[i][0] == p[k][0] || p[k][0] == p[j][0]) continue;
      if (dxdy == get_vec(p[i], p[k])) {
        if (p[i][0] <= p[k][0] && p[k][0] <= p[j][0]) {
          cnt++;
        } else {
          ok = false;
          break;
        }
      }
    }
    if (ok) {
      L.push_back({p[i], p[j]});
      count.push_back(cnt + 1);
    }
  }

  int nn = L.size();
  if (nn == 0) {
    cout << n << endl;
    return 0;
  }

  // 直線の交点をkeyに、その交点を通る直線のsetを持つ
  map<point_frac, set<int>> temp;
  rep(i, 0, nn) rep(j, i + 1, nn) {
    if (get_vec(L[i][0], L[i][1]) == get_vec(L[j][0], L[j][1])) continue;
    auto [p, f] = get_intersect(L[i], L[j]);
    if (!f) continue;
    if (p[0] < 0) {
      temp[p].insert(i);
      temp[p].insert(j);
    }
  }

  int ans = *max_element(count.begin(), count.end());
  for (auto [_, s] : temp) {
    int tans = 0;
    for (auto i : s) tans += count[i];
    ans = max(ans, tans);
  }
  cout << n - ans << endl;
}
}  // namespace frac
