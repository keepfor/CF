//Author: Kevin5307
#include<bits/stdc++.h>
//#pragma GCC optimize("O2")
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(),(x).end()
#define rALL(x) (x).rbegin(),(x).rend()
#define srt(x) sort(ALL(x))
#define rev(x) reverse(ALL(x))
#define rsrt(x) sort(rALL(x))
#define sz(x) (int)(x.size())
#define inf 0x3f3f3f3f
#define pii pair<int,int>
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
#define longer __int128_t
void die(string S){puts(S.c_str());exit(0);}
class MaximumFlow
{
	private:
		struct edge
		{
			int u,v,capa;
		}E[100100];
		edge make_edge(int u,int v,int capa)
		{
			edge e;
			e.u=u;
			e.v=v;
			e.capa=capa;
			return e;
		}
		vector<int> G[10100];
		int p;
		bool inque[10100];
		int dep[10100];
		int head[10100];
		bool bfs(int s,int t)
		{
			for(int i=0;i<10100;i++)
				dep[i]=inf;
			memset(inque,0,sizeof(inque));
			dep[s]=0;
			inque[s]=1;
			queue<int> q;
			q.push(s);
			while(!q.empty())
			{
				int x=q.front();
				q.pop();
				inque[x]=0;
				for(int e:G[x])
				{
					int v=E[e].v;
					if(dep[v]>dep[x]+1&&E[e].capa)
					{
						dep[v]=dep[x]+1;
						if(!inque[v])
						{
							q.push(v);
							inque[v]=1;
						}
					}
				}
			}
			return (dep[t]!=inf);
		}
		int dfs(int u,int t,int aug)
		{
			int naug=0;
			if(u==t)
				return aug;
			for(;head[u]<sz(G[u]);head[u]++)
			{
				int e=G[u][head[u]];
				int v=E[e].v;
				if(E[e].capa&&dep[v]==dep[u]+1)
				{
					if((naug=dfs(v,t,min(aug,E[e].capa))))
					{
						E[e].capa-=naug;
						E[e^1].capa+=naug;
						return naug;
					}
				}
			}
			return 0;
		}
	public:
		void clear()
		{
			p=0;
			for(int i=0;i<10100;i++)
				G[i].clear();
		}
		MaximumFlow()
		{
			clear();
		}
		void addEdge(int u,int v,int capa)
		{
			G[u].pb(p);
			E[p++]=make_edge(u,v,capa);
			G[v].pb(p);
			E[p++]=make_edge(v,u,0);
		}
		int dinic(int s,int t)
		{
			int flow;
			int maxflow=0;
			while(bfs(s,t))
			{
				memset(head,0,sizeof(head));
				while((flow=dfs(s,t,inf)))
					maxflow+=flow;
			}
			return maxflow;
		}
		vector<int> get(int n)
		{
			vector<int> ret;
			for(int i=1;i<=n;i++)
				if(!E[G[i][0]].capa)
					ret.pb(i);
			return ret;
		}
};
MaximumFlow mf;
int a[3030],b[3030];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		scanf("%d",b+i);
	int cnt=n;
	bool vis[3030];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) if(!vis[i])
	{
		int x=i;
		cnt++;
		mf.addEdge(0,cnt,1);
		while(!vis[x])
		{
			vis[x]=1;
			mf.addEdge(cnt,x,1);
			x=a[x];
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) if(!vis[i])
	{
		int x=i;
		cnt++;
		mf.addEdge(cnt,n+n+n+1,1);
		while(!vis[x])
		{
			vis[x]=1;
			mf.addEdge(x,cnt,1);
			x=b[x];
		}
	}
	printf("%d\n",n-mf.dinic(0,n+n+n+1));
	vector<int> vec=mf.get(n);
	for(auto x:vec)
		printf("%d ",x);
	return 0;
}
