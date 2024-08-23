#include <bits/stdc++.h>
using namespace std;


template <typename T> T mod_inv_in_range(T a, T m) {
	// assert(0 <= a && a < m);
	T x = a, y = m;
	// coeff of a in x and y
	T vx = 1, vy = 0;
	while (x) {
		T k = y / x;
		y %= x;
		vy -= k * vx;
		std::swap(x, y);
		std::swap(vx, vy);
	}
	assert(y == 1);
	return vy < 0 ? m + vy : vy;
}

template <typename T> struct extended_gcd_result {
	T gcd;
	T coeff_a, coeff_b;
};
template <typename T> extended_gcd_result<T> extended_gcd(T a, T b) {
	T x = a, y = b;
	// coeff of a and b in x and y
	T ax = 1, ay = 0;
	T bx = 0, by = 1;
	while (x) {
		T k = y / x;
		y %= x;
		ay -= k * ax;
		by -= k * bx;
		std::swap(x, y);
		std::swap(ax, ay);
		std::swap(bx, by);
	}
	return {y, ay, by};
}

template <typename T> T mod_inv(T a, T m) {
	a %= m;
	a = a < 0 ? a + m : a;
	return mod_inv_in_range(a, m);
}


template <typename tag> struct dynamic_modnum {
private:
#if __cpp_inline_variables >= 201606
	// C++17 and up
	inline static int MOD_ = 0;
	inline static uint64_t BARRETT_M = 0;
#else
	// NB: these must be initialized out of the class by hand:
	//   static int dynamic_modnum<tag>::MOD = 0;
	//   static int dynamic_modnum<tag>::BARRETT_M = 0;
	static int MOD_;
	static uint64_t BARRETT_M;
#endif

public:
	// Make only the const-reference public, to force the use of set_mod
	static constexpr int const& MOD = MOD_;

	// Barret reduction taken from KACTL:
	/**
	 * Author: Simon Lindholm
	 * Date: 2020-05-30
	 * License: CC0
	 * Source: https://en.wikipedia.org/wiki/Barrett_reduction
	 * Description: Compute $a \% b$ about 5 times faster than usual, where $b$ is constant but not known at compile time.
	 * Returns a value congruent to $a \pmod b$ in the range $[0, 2b)$.
	 * Status: proven correct, stress-tested
	 * Measured as having 4 times lower latency, and 8 times higher throughput, see stress-test.
	 * Details:
	 * More precisely, it can be proven that the result equals 0 only if $a = 0$,
	 * and otherwise lies in $[1, (1 + a/2^64) * b)$.
	 */
	static void set_mod(int mod) {
		assert(mod > 0);
		MOD_ = mod;
		BARRETT_M = (uint64_t(-1) / MOD);
	}
	static uint32_t barrett_reduce_partial(uint64_t a) {
		return uint32_t(a - uint64_t((__uint128_t(BARRETT_M) * a) >> 64) * MOD);
	}
	static int barrett_reduce(uint64_t a) {
		int32_t res = int32_t(barrett_reduce_partial(a) - MOD);
		return (res < 0) ? res + MOD : res;
	}

	struct mod_reader {
		friend std::istream& operator >> (std::istream& i, mod_reader) {
			int mod; i >> mod;
			dynamic_modnum::set_mod(mod);
			return i;
		}
	};
	static mod_reader MOD_READER() {
		return mod_reader();
	}

private:
	int v;

public:

	dynamic_modnum() : v(0) {}
	dynamic_modnum(int64_t v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const dynamic_modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, dynamic_modnum& n) { int64_t v_; in >> v_; n = dynamic_modnum(v_); return in; }

	friend bool operator == (const dynamic_modnum& a, const dynamic_modnum& b) { return a.v == b.v; }
	friend bool operator != (const dynamic_modnum& a, const dynamic_modnum& b) { return a.v != b.v; }

	dynamic_modnum inv() const {
		dynamic_modnum res;
		res.v = mod_inv_in_range(v, MOD);
		return res;
	}
	friend dynamic_modnum inv(const dynamic_modnum& m) { return m.inv(); }
	dynamic_modnum neg() const {
		dynamic_modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	friend dynamic_modnum neg(const dynamic_modnum& m) { return m.neg(); }

	dynamic_modnum operator- () const {
		return neg();
	}
	dynamic_modnum operator+ () const {
		return dynamic_modnum(*this);
	}

	dynamic_modnum& operator ++ () {
		v ++;
		if (v == MOD) v = 0;
		return *this;
	}
	dynamic_modnum& operator -- () {
		if (v == 0) v = MOD;
		v --;
		return *this;
	}
	dynamic_modnum& operator += (const dynamic_modnum& o) {
		v -= MOD-o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	dynamic_modnum& operator -= (const dynamic_modnum& o) {
		v -= o.v;
		v = (v < 0) ? v + MOD : v;
		return *this;
	}
	dynamic_modnum& operator *= (const dynamic_modnum& o) {
		v = barrett_reduce(int64_t(v) * int64_t(o.v));
		return *this;
	}
	dynamic_modnum& operator /= (const dynamic_modnum& o) {
		return *this *= o.inv();
	}

	friend dynamic_modnum operator ++ (dynamic_modnum& a, int) { dynamic_modnum r = a; ++a; return r; }
	friend dynamic_modnum operator -- (dynamic_modnum& a, int) { dynamic_modnum r = a; --a; return r; }
	friend dynamic_modnum operator + (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) += b; }
	friend dynamic_modnum operator - (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) -= b; }
	friend dynamic_modnum operator * (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) *= b; }
	friend dynamic_modnum operator / (const dynamic_modnum& a, const dynamic_modnum& b) { return dynamic_modnum(a) /= b; }
};


void solve(){
	int N, K, P;
	cin >> N >> K >> P;
	using num = dynamic_modnum<struct tag>;
	num::set_mod(P);
	vector<num> p2(N+1, 1);
	for(int i = 1; i <= N; i++) p2[i] = p2[i-1] * 2;
	vector<vector<num> > dp(N+1, vector<num>(K+1, 0));
	for(int i = 0; i <= K; i++){
		dp[N-1][i] = 1;
	}
	for(int i = N-2; i >= 0; i--){
		num other = p2[N-1-i]-1;
		vector<num> choose(K+1, 0);
		// (a + other - 1 choose a)
		choose[0] = 1;
		for(int j = 1; j <= K; j++){
			choose[j] = choose[j-1] * (other + j-1) / j;
		}
		for(int j = 0; j <= K; j++){
			for(int l = 0; l < j-l; l++){
				dp[i][j] += dp[i+1][j-l] * choose[l];
			}
		}
		for(int j = 1; j <= K; j++){
			dp[i][j] += dp[i][j-1];
		}
	}
	num ans = dp[0][K];
	ans *= p2[N-1];
	cout << ans << '\n';
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	while(T--){
		solve();
	}
}
