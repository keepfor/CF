#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
#include<vector>
#include<algorithm>
struct bridge{
    int n;
    vector<int>ord,low;
    vector<bool>art;
    vector<vector<int> >G;
    bridge(int n_=0):n(n_),ord(n_,-1),low(n_),art(n_,false),G(n_){}
    void add_edge(int u,int v)
    {
        G[u].push_back(v);
        G[v].push_back(u);
    }
    bool operator[](int i)const{return art[i];}
    bool is_bridge(int a,int b)const
    {
        if(ord[a]>ord[b])swap(a,b);
        return ord[a]<low[b];
    }
    void dfs(int u,int p,int&k)
    {
        low[u]=ord[u]=k++;
        bool now=false;
        int pc=0;
        for(int v:G[u])
        {
            if(ord[v]==-1)
            {
                dfs(v,u,k);
                low[u]=min(low[u],low[v]);
                now=now||ord[u]<=low[v];
            }
            else if(v!=p||pc++)
            {
                low[u]=min(low[u],ord[v]);
            }
        }
        art[u]=now;
    }
    void build()
    {
        int k=0;
        for(int u=0;u<n;u++)if(ord[u]==-1)
        {
            int cnt=0;
            low[u]=ord[u]=k++;
            for(int v:G[u])if(ord[v]==-1)
            {
                dfs(v,u,k);
                cnt++;
            }
            if(cnt>=2)art[u]=true;
        }
    }
};
int N,M;
int a[2<<17],b[2<<17],c[2<<17];
vector<pair<int,int> >G[2<<17];
vector<long>f(int s)
{
    vector<long>d(N,(long)1e18);
    d[s]=0;
    priority_queue<pair<long,int> >Q;
    Q.push(make_pair(0,s));
    while(!Q.empty())
    {
        int u=Q.top().second;
        long D=-Q.top().first;
        Q.pop();
        if(d[u]<D)continue;
        for(auto[v,nd]:G[u])
        {
            long nD=D+nd;
            if(d[v]>nD)
            {
                d[v]=nD;
                Q.push(make_pair(-nD,v));
            }
        }
    }
    return d;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>N>>M;
    for(int i=0;i<M;i++)
    {
        cin>>a[i]>>b[i]>>c[i];
        a[i]--,b[i]--;
        G[a[i]].push_back(make_pair(b[i],c[i]));
        G[b[i]].push_back(make_pair(a[i],c[i]));
    }
    vector<long>d1=f(0),dn=f(N-1);
    bridge H(N);
    for(int i=0;i<M;i++)
    {
        if(d1[N-1]==d1[a[i]]+c[i]+dn[b[i]]||
            d1[N-1]==d1[b[i]]+c[i]+dn[a[i]])
        {
            H.add_edge(a[i],b[i]);
        }
    }
    H.build();
    for(int i=0;i<M;i++)
    {
        bool ok=true;
        if(d1[N-1]==d1[a[i]]+c[i]+dn[b[i]]||
            d1[N-1]==d1[b[i]]+c[i]+dn[a[i]])
        {
            if(H.is_bridge(a[i],b[i]))ok=false;
        }
        cout<<(!ok?"Yes\n":"No\n");
    }
}
