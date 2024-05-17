namespace qin{
#include <bits/stdc++.h>

using namespace std;
const int N = 250;
const int M = 1e5 + 50;
const long long inf = 1e18;

int n, m, s, t, cur[N], d[N], a[N], b[N], ans[N][N];
int head[N], nxt[M], ver[M], edge[M], tot = 1;

inline void add(int u, int v, int w) {
	nxt[++tot] = head[u], ver[tot] = v, edge[tot] = w, head[u] = tot;
	nxt[++tot] = head[v], ver[tot] = u, edge[tot] = 0, head[v] = tot;
}

bool bfs() {
	queue<int> que;
	memcpy(cur, head, sizeof head);
	memset(d, 0x3f, sizeof d);
	d[s] = 0;
	que.emplace(s);
	while (!que.empty()) {
		int x = que.front(); que.pop();
		for (int i = head[x]; i; i = nxt[i]) {
			int y = ver[i], w = edge[i];
			if (w && d[y] > d[x] + 1) {
				d[y] = d[x] + 1;
				if (y == t) return true;
				que.emplace(y);
			}
		}
	}
	return false;
}

long long dinic(int x, long long flow) {
	if (x == t) return flow;
	long long rest = flow;
	for (int &i = cur[x]; i; i = nxt[i]) {
		int y = ver[i], w = edge[i];
		if (w && d[y] == d[x] + 1) {
			long long k = dinic(y, min((long long)w, rest));
			if (!k) d[y] = 0;
			edge[i] -= k;
			rest -= k;
			edge[i ^ 1] += k;
			if (!rest) break;
		}
	}
	return flow - rest;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	s = 2 * n + 1; t = s + 1;
	int suma = 0, sumb = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		add(s, i, a[i]);
		suma += a[i];
	}	
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		add(i + n, t, b[i]);
		sumb += b[i];
	}
	if (suma != sumb) {
		puts("NO");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		add(i, i + n, 0x3f3f3f3f);
	}
	for (int i = 1; i <= m; ++i) {
		int p, q;
		cin >> p >> q;
		add(p, q + n, 0x3f3f3f3f);
		add(q, p + n, 0x3f3f3f3f);
	}
	long long maxflow = 0, flow;
	while (bfs())
		while (flow = dinic(s, inf))
			maxflow += flow;
	if (maxflow != suma) {
		puts("NO");
		return 0;
	}
	cout << "YES\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = head[i + n]; j; j = nxt[j]) {
			int y = ver[j];
			if (1 <= y && y <= n) {
				ans[y][i] += edge[j];				
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << ans[i][j] << " \n"[j == n];
		}
	}
	return 0;
}
}
	
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<cassert>
#define PB push_back
#define MP make_pair
#define sz(v) (in((v).size()))
#define forn(i,n) for(in i=0;i<(n);++i)
#define forv(i,v) forn(i,sz(v))
#define fors(i,s) for(auto i=(s).begin();i!=(s).end();++i)
#define all(v) (v).begin(),(v).end()
using namespace std;
typedef long long in;
typedef vector<in> VI;
typedef vector<VI> VVI;

struct eg{
  in dest,c,f,rev;
};
struct flow{
  vector<bool> vtd;
  vector<vector<eg> > egs;
  vector<vector<in> > ept;
  vector<in> dtt;
  in n,s,t,tot,inf;
  void ini(in pn, in ps, in pt){
    n=pn;s=ps;t=pt;
    egs.resize(0);
    ept.resize(0);
    ept.resize(n,vector<in>(0));
    egs.resize(n,vector<eg>(0));
    dtt.resize(0);
    dtt.resize(n);
    tot=0;
    inf=1000000000000000LL;
    vtd.resize(n);
  }
  void add(in a, in b, in c1, in c2=0){
    eg ta,tb;
    ta.dest=b;
    tb.dest=a;
    ta.f=tb.f=0;
    ta.c=c1;
    tb.c=c2;
    ta.rev=egs[b].size();
    tb.rev=egs[a].size();
    egs[a].push_back(ta);
    egs[b].push_back(tb);
  }
  in doit(in u, in lim){
    if(u==t)
      return lim;
    in cfl=0;
    in dlm;
    in pl;
    while(cfl<lim && ept[u].size()>0){
      eg& tp=egs[u][ept[u].back()];
      dlm=lim-cfl;
      if(dlm>tp.c-tp.f)
	dlm=tp.c-tp.f;
      pl=doit(tp.dest,dlm);
      tp.f+=pl;
      egs[tp.dest][tp.rev].f-=pl;
      if(pl<dlm || dlm==0)
	ept[u].pop_back();
      cfl+=pl;
    }
    return cfl;
  }
  in dinic(){
    while(true){
      for(in i=0;i<n;i++){
	ept[i].resize(0);
	dtt[i]=inf;
      }
      queue<in> q;
      dtt[t]=0;
      q.push(t);
      while(!q.empty()){
	in u=q.front();
	q.pop();
	for(in i=0;i<egs[u].size();i++){
	  eg& tp=egs[u][i];
	  if(dtt[tp.dest]<inf)
	    continue;
	  if(egs[tp.dest][tp.rev].c==egs[tp.dest][tp.rev].f)
	    continue;
	  dtt[tp.dest]=dtt[u]+1;
	  q.push(tp.dest);
	}
      }
      for(in i=0;i<n;i++)
	vtd[i]=0;
      vtd[s]=1;
      q.push(s);
      while(!q.empty()){
	in u=q.front();
	q.pop();
	for(in i=0;i<egs[u].size();i++){
	  eg& tp=egs[u][i];
	  if(dtt[tp.dest]+1>dtt[u])
	    continue;
	  if(tp.f==tp.c)
	    continue;
	  ept[u].push_back(i);
	  if(!vtd[tp.dest])
	    q.push(tp.dest);
	  vtd[tp.dest]=1;
	}
      }
      in pl=doit(s,inf);
      if(pl==0)
	break;
      tot+=pl;
    }
    return tot;
  }
};
in n,m;
VI a,b;
in sma=0;
in smb=0;
flow mfl;
VVI sol;
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin>>n>>m;
  a.resize(n);
  b.resize(n);
  forn(i,n){
    cin>>a[i];
    sma+=a[i];
  }
  forn(i,n){
    cin>>b[i];
    smb+=b[i];
  }
  if(sma!=smb){
    cout<<"NO"<<endl;return 0;
  }
  in s=2*n;
  in t=2*n+1;
  mfl.ini(t+1,s,t);
  in ta,tb;
  forn(z,m){
    cin>>ta>>tb;
    ta--;
    tb--;
    mfl.add(ta,n+tb,1000000000LL);
    mfl.add(tb,n+ta,1000000000LL);
  }
  forn(i,n){
    mfl.add(i,n+i,1000000000LL);
    mfl.add(s,i,a[i]);
    mfl.add(n+i,t,b[i]);
  }
  if(mfl.dinic()!=sma){
    cout<<"NO"<<endl;return 0;
  }
  sol.resize(n,VI(n,0));
  in tt;
  forn(i,n){
    forv(j,mfl.egs[i]){
      tt=mfl.egs[i][j].dest;
      if(tt>=n && tt<2*n)
	sol[i][tt-n]+=mfl.egs[i][j].f;
    }
  }
  cout<<"YES"<<endl;
  forn(i,n){
    forn(j,n){
      cout<<sol[i][j]<<" ";
    }
    cout<<"\n";
  }
  return 0;
}
