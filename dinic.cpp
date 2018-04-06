using namespace std;
#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl
#define sf(x) scanf("%d",&x)
#define pf printf
#define light(x) printf("Case %d:",x)
typedef pair<int,int> pii;

int dist[220],cap[220];
int n,m;
int cols[60],rows[60];
const int INF = 2000000000;

struct node {
	int x,y,penn,cap;
	node(int a,int b,int c,int d) {
		x=a;
		y=b;
		penn=c;
		cap=d;
	}
	bool dist(node rr,double range) {
		double d=(x-rr.x)*(x-rr.x)+(y-rr.y)*(y-rr.y);
		//cout<<d<<endl;
		return d<=range*range;
	}
};

struct Edge {
	int from, to, cap, flow, index;
	Edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct Dinic {
	int N;
	map<pii,int> indexmp;
	vector<vector<Edge> > G;
	vector<Edge *> dad;
	vector<int> Q;

	Dinic(int N) : N(N), G(N), dad(N), Q(N) {}

	void addEdge(int from, int to, int cap) {
		indexmp[pii(from,to)]=G[from].size();
		indexmp[pii(to,from)]=G[to].size();
		G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
		if (from == to) G[from].back().index++;
		G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
	}

	long long BlockingFlow(int s, int t) {
		fill(dad.begin(), dad.end(), (Edge *) NULL);
		dad[s] = &G[0][0] - 1;

		int head = 0, tail = 0;
		Q[tail++] = s;
		while (head < tail) {
			int x = Q[head++];
			for (int i = 0; i < G[x].size(); i++) {
				Edge &e = G[x][i];
				if (!dad[e.to] && e.cap - e.flow > 0) {
					dad[e.to] = &G[x][i];
					Q[tail++] = e.to;
				}
			}
		}
		if (!dad[t]) return 0;

		long long totflow = 0;
		for (int i = 0; i < G[t].size(); i++) {
			Edge *start = &G[G[t][i].to][G[t][i].index];
			int amt = INF;
			for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
				if (!e) {
					amt = 0;
					break;
				}
				amt = min(amt, e->cap - e->flow);
			}
			if (amt == 0) continue;
			for (Edge *e = start; amt && e != dad[s]; e = dad[e->from]) {
				e->flow += amt;
				G[e->to][e->index].flow -= amt;
			}
			totflow += amt;
		}
		return totflow;
	}

	long long GetMaxFlow(int s, int t) {
		long long totflow = 0;
		while (long long flow = BlockingFlow(s, t))
			totflow += flow;
		return totflow;
	}

	void ClearFlow() {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < G[i].size(); ++j)
				G[i][j].flow = 0;

	}
	void ClearGraph() {
		for (int i = 0; i < N; ++i) {
			G[i].clear();
		}
		indexmp.clear();
	}
	int GetFlow(int u,int v) {
		for(int i=0; i<G[u].size(); i++) {
			if(G[u][i].to==v) return G[u][i].flow;
		}
		return 0;
	}
	int GetMapFlow(int u,int v) {
		return G[u][indexmp[pii(u,v)]].flow;
		return G[v][indexmp[pii(v,u)]].flow;
	}
	void SetMapFlow(int u,int v,int f) {
		G[u][indexmp[pii(u,v)]].flow=f;
	}
	void decMapFlow(int u,int v,int f) {
		G[u][indexmp[pii(u,v)]].flow-=f;
		G[v][indexmp[pii(v,u)]].flow+=f;
	}
	void inccMapFlow(int u,int v,int f) {
		G[u][indexmp[pii(u,v)]].flow+=f;
		G[v][indexmp[pii(v,u)]].flow-=f;
	}
};
int sumr;
bool isvalid() {
	int range=n*m,sumc=0;
	sumr=0;
	for(int i=1; i<=n; i++) sumr+=rows[i];
	for(int i=1; i<=m; i++) sumc+=cols[i];
	if(sumc>range) return false;
	if(sumc==sumr) return true;
	return false;
}
void solve(int t) {
	sf(n);
	sf(m);
	for(int i=1; i<=n; i++) sf(rows[i]);
	for(int i=1; i<=m; i++) sf(cols[i]);
	int s=0,d=n+m+1;
	Dinic g(d+6);
	if(isvalid()) {


		for(int i=1; i<=n; i++) {
			g.addEdge(s,i,rows[i]);
		}
		for(int i=1; i<=m; i++) {
			g.addEdge(i+n,d,cols[i]);
		}
		for(int i=1; i<=n; i++) {
			for(int j=n+1; j<=n+m; j++) {
				g.addEdge(i,j,1);
			}
		}
		int f=g.GetMaxFlow(s,d);
		if(f==sumr) {
			light(t);
			puts("");
			for(int i=1; i<=n; i++) {
				for(int j=n+1; j<=n+m; j++) {
					if(g.GetMapFlow(i,j)==0) {
						cout<<0;
						g.inccMapFlow(i,j,1);
					} else {

						g.decMapFlow(s,i,1);
						g.decMapFlow(j,d,1);
						int f1=g.GetMaxFlow(s,d);
						if(f1==1) {
							cout<<0;
						} else {
							g.inccMapFlow(s,i,1);
							g.inccMapFlow(j,d,1);
							cout<<g.GetMapFlow(i,j);
						}
					}
					if(j==n+m) puts("");
				
				}
			}
		} else {
			light(t);
			puts(" impossible");
		}
	} else {
		light(t);
		puts(" impossible");
	}
	g.ClearGraph();
}
int main() {
	int t;
	cin>>t;
	for(int i=1; i<=t; i++) {
		solve(i);
	}
}
