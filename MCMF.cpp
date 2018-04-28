#include <bits/stdc++.h>
 
#define rep(i,n) for(i=0; i<n; i++)
#define repl(i,n) for(i=1; i<=n; i++)
 
#define sz(x) (int) x.size()
#define pb push_back
#define all(x) x.begin(),x.end()
#define uu first
#define vv second
#define mem(x, y) memset(x, y, sizeof(x))
#define un(x) x.erase(unique(all(x)), x.end())
 
#define sdi(x) scanf("%d", &x)
#define sdii(x, y) scanf("%d %d", &x, &y)
#define sdiii(x, y, z) scanf("%d %d %d", &x, &y, &z)
#define sdl(x) scanf("%lld", &x)
#define sdll(x, y) scanf("%lld %lld", &x, &y)
#define sdlll(x, y, z) scanf("%lld %lld %lld", &x, &y, &z)
#define sds(x) scanf("%s", x)
#define pfi(x) printf("%d\n", x)
#define pfii(x, y) printf("%d %d\n", x, y)
#define pfiii(x, y, z) printf("%d %d %d\n", x, y, z)
#define pfl(x) printf("%lld\n", x)
#define pfll(x, y) printf("%lld %lld\n", x, y)
#define pflll(x, y, z) printf("%lld %lld %lld\n", x, y, z)
 
#define eps 1e-9
#define OK cerr << "ok\n"
#define DB(x) cerr << #x << " = " << x << endl
 
using namespace std;
 
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair <int, int> pii;
 
inline int setBit(int N, int pos) { return N=N | (1<<pos); }
inline int resetBit(int N, int pos) { return N= N & ~(1<<pos); }
inline bool checkBit(int N, int pos) { return (bool)(N & (1<<pos)); }
 
//int kx[] = {+2, +1, -1, -2, -2, -1, +1, +2};
//int ky[] = {+1, +2, +2, +1, -1, -2, -2, -1}; //Knight Direction
//int fx[] = {+0, +0, +1, -1, -1, +1, -1, +1};
//int fy[] = {-1, +1, +0, +0, +1, +1, -1, -1}; //Four & Eight Direction
 
 
const int MAXN=105, MAXM=2705, INF=1000000000;
struct Edge {
    int u, v, cap, cost;
    int next;
    Edge(){}
    Edge(int u,int v,int cap,int cost,int next):u(u),v(v),cap(cap),cost(cost),next(next){}
} edge[MAXM*3];
 
int NE, head[MAXN], dist[MAXN], pp[MAXN];
bool vis[MAXN];
 
inline void init(int n) {
    NE = 0;
    fill(head,head+n+1,-1);
}
 
inline void addEdge(int u, int v, int cap, int cost) { // directed edges only
    edge[NE] = Edge(u,v,cap,cost,head[u]);
    head[u] = NE++;
    edge[NE] = Edge(v,u,0,-cost,head[v]);
    head[v] = NE++;
}
 
int qu[300010];
 
inline bool SPFA(int s, int t, int n) {
    int i, u, v , tmp, he=0 , ta=0;
 
    fill(vis,vis+n+1,false);
    fill(pp,pp+n+1,-1);
    fill(dist,dist+n+1,INF);
    vis[s] = true; dist[s] = 0;
    qu[++ta] = s;
 
    while(he!=ta) {
        u = qu[++he];  vis[u] = false;
        if(he >= 250000) he = 0;
        for(i = head[u];~ i; i = edge[i].next) {
            v = edge[i].v;
            tmp = dist[u] + edge[i].cost;
            if(edge[i].cap &&  dist[v] > tmp) {
                dist[v] = tmp;
                pp[v] = i;
                if(!vis[v]) {
                    qu[++ta] = v;
                    if(ta >= 250000) ta = 0;
                    vis[v] = true;
                }
            }
        }
    }
    if(dist[t] == INF) return false;
    return true;
}
 
pii MCMF(int s, int t, int n)
{
    int flow = 0, i, minflow, mincost=0;
    while(SPFA(s, t, n)) {
        minflow = INF + 1;
        for(i = pp[t]; ~i ; i = pp[edge[i].u]) {
            minflow = min(minflow, edge[i].cap);
        }
        flow += minflow;
        for(i = pp[t]; ~i; i = pp[edge[i].u]) {
            edge[i].cap -= minflow;
            edge[i^1].cap += minflow;
        }
        mincost += dist[t] * minflow;
    }
    return make_pair(flow, mincost);
}
 
int n, arr[MAXN][MAXN];
 

void solve(int ts)
{
	scanf("%d",&n);
	int nodes=n+n+2,src=n+n+1,sink=n+n+2;
	init(nodes);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&arr[i][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		addEdge(src,i,1,0);
		addEdge(i+n,sink,1,0);
	}
	for(int li=1;li<=n;li++)
	{
		for(int ri=1;ri<=n;ri++)
		{
			addEdge(li,ri+n,1,-arr[li][ri]);
		}
	}
	int ans=-MCMF(src, sink, nodes).vv;
	printf("Case %d: %d\n",ts,ans);
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		solve(i);
	}
	return 0;
}
