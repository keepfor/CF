#include <bits/stdc++.h>

using i64 = long long;
template<class T>
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
    explicit operator double() const {
        return 1. * num / den;
    }
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
    friend Frac operator+(Frac lhs, const Frac &rhs) {
        return lhs += rhs;
    }
    friend Frac operator-(Frac lhs, const Frac &rhs) {
        return lhs -= rhs;
    }
    friend Frac operator*(Frac lhs, const Frac &rhs) {
        return lhs *= rhs;
    }
    friend Frac operator/(Frac lhs, const Frac &rhs) {
        return lhs /= rhs;
    }
    friend Frac operator-(const Frac &a) {
        return Frac(-a.num, a.den);
    }
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
            if (x < 0 && a[0] * x + a[2] == b[0] * x + b[2] && a[1] * x + a[3] == b[1] * x + b[3]) {
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
        