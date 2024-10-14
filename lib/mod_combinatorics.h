// #pragma GCC diagnostic ignored "-Wshadow"
// #pragma GCC diagnostic ignored "-Wconversion"
// #pragma GCC diagnostic ignored "-Wfloat-equal"
// #pragma GCC diagnostic ignored "-Wfloat-conversion"
// #pragma GCC diagnostic ignored "-Wunused-variable"
// #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
// #pragma GCC diagnostic ignored "-Wsign-compare"

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#pragma GCC target("tune=native")

using namespace std;
// using namespace __gnu_pbds;

template<class Fun>
class y_combinator_result
{
    Fun fun_;
public:
    template<class T> 
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args)
    {return fun_(std::ref(*this), std::forward<Args>(args)...);}
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun)
{return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));}

#define endl " \n"
#define mod (int)(1e9+7)
#define ar array

typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<bool> vb;
typedef vector<char> vc;
typedef vector<string> vs;

struct cException : public std::runtime_error
{
    explicit cException(const string& message)
        :runtime_error(message) {}
};

template<int P>
struct MInt
{
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll val) : x{norm(static_cast<int>(val % getMod()))} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int val) const {
        if (val < 0) {
            val += getMod();
        }
        if (val >= getMod()) {
            val -= getMod();
        }
        return val;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    explicit constexpr operator ll() const {
        return x;
    }
    friend constexpr MInt power(MInt a, ll b) {
        MInt res = 1;
        for (; b; b /= 2, a *= a) {
            if (b % 2) {
                res *= a;
            }
        }
        return res;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt& operator++(int) {
        *this += 1;
        return *this;
    }
    constexpr MInt& operator++() {
        *this += 1;
        return *this;
    }
    constexpr MInt& operator--(int) {
        *this -= 1;
        return *this;
    }
    constexpr MInt& operator--() {
        *this -= 1;
        return *this;
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = int(1LL * x * rhs.x % getMod());
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator>(MInt lhs, MInt rhs) {
        return lhs.val() > rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
    friend constexpr bool operator>=(MInt lhs, MInt rhs) {
        return lhs.val() >= rhs.val();
    }
    friend constexpr bool operator<=(MInt lhs, MInt rhs) {
        return lhs.val() <= rhs.val();
    }
};

// constexpr int P = 998244353;
constexpr int P = int(1e9 + 7);
using mint = MInt<P>;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '"' << x << '"';}
void __print(const string &x) {cerr << '"' << x << '"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<int P> void __print(const MInt<P> x) {cerr << x;}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << '}';}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

#ifdef LOCAL
#define debug(x...) cerr<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << endl;
#else
#define debug(x...)
#endif

struct mod_combinatorics
{
    int sz=0;
    vector<mint> fact, invfact, inv;
    
    mod_combinatorics() {}
    
    mod_combinatorics(int _sz) {init(_sz);}
    
    void init(int _sz)
    {
        this->sz = _sz;
        fact.assign(sz+1,1);
        invfact.assign(sz+1,1);
        inv.assign(sz+1,0);
        inv[1]=1;
        for(int i=2; i<=sz; i++)
        {
            inv[i]=mint::getMod()-mint::getMod()/i*inv[mint::getMod()%i];
        }
        for(int i=1; i<=sz; i++)
        {
            fact[i] = fact[i-1] * i;
            invfact[i] = invfact[i-1] * inv[i];
        }
    }
    
    ~mod_combinatorics() {}
    
    mint C(int n, int r) const
    {
        assert(0<=min(n, r) && max(n, r)<=sz && n>=r);
        return fact[n] * invfact[r] * invfact[n-r];
    }
    
    mint P(int n, int r) const
    {
        assert(0<=min(n, r) && max(n, r)<=sz && n>=r);
        return fact[n] * invfact[n - r];
    }
    
    mint H(int n, int r) const
    {
        assert(0<=min(n, r) && max(n+r-1,r)<=sz && n+r-1>=r);
        if(n==0) return 0;
        return C(n+r-1, r);
    }
    
    mint Catalan(int n) const
    {
        if(n==0) return 1;
        return C(2*n, n) - C(2*n, n+1);
    }
    
    mint f(int n) {return fact[n];}
    
    mint fi(int n) {return invfact[n];}
};

mod_combinatorics combi (int(4e6 + 7));

void solve()
{
    int a, b;
    cin >> a >> b;

    int n = a + b;

    int pair1 = n / 4;
    int pair2 = (n + 2) / 4;

    mint ans = 0;
    for(int i = 0; i <= b; i+= 2)
    {
        mint res = 1;

        if(i/2 > pair1 || i/2 > pair2) break;

        res *= combi.C(pair1, i/2) * combi.C(pair2, i/2);
        int rem = b - i;

        if(rem > n / 2) continue;

        res *= combi.C(n/2, rem);
        ans += res;
    }

    cout << ans << endl;
}
 
int main ()
{
    #ifndef ONLINE_JUDGE
    freopen("../input.txt","r",stdin);
    freopen("../output.txt","w",stdout);
    thread([]{
        this_thread::sleep_for(100ms);
        throw cException("TLE");
    }).detach();
    #endif
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}