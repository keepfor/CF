#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef basic_string<int> BI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937_64 mrand(random_device{}()); 
const ll mod=998244353;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=201000;
int n,q;
ll hs[N],sa[N],sb[N];

int main() {
	scanf("%d%d",&n,&q);
	rep(i,1,n+1) hs[i]=mrand();
	rep(i,1,n+1) {
		int a;
		scanf("%d",&a);
		sa[i]=sa[i-1]+hs[a];
	}
	rep(i,1,n+1) {
		int a;
		scanf("%d",&a);
		sb[i]=sb[i-1]+hs[a];
	}
	rep(i,0,q) {
		int l1,r1,l2,r2;
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		puts((sa[r1]-sa[l1-1]==sb[r2]-sb[l2-1])?"Yes":"No");
	}
}
