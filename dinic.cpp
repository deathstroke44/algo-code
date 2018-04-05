using namespace std;
#include <bits/stdc++.h>
#define D(x) cout << #x " = " << (x) << endl
    map<string,int> mp;
    int dist[220],cap[220];

const int INF = 2000000000;
int a[30000000];
struct node
{
	int x,y,penn,cap;
	node(int a,int b,int c,int d)
	{
		x=a;y=b;penn=c;cap=d;
	}
	bool dist(node rr,double range)
	{
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
  vector<vector<Edge> > G;
  vector<Edge *> dad;
  vector<int> Q;

  Dinic(int N) : N(N), G(N), dad(N), Q(N) {}

  void addEdge(int from, int to, int cap) {
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
        if (!e) { amt = 0; break; }
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
  void ClearGraph()
  {
  	for (int i = 0; i < N; ++i)
  	{
  		G[i].clear();
	}
  }
  int GetFlow(int u,int v)
  {
  	for(int i=0;i<G[u].size();i++)
  	{
  		if(G[u][i].to==v) return G[u][i].flow;
	}
	return 0;
  }
};
int main()
{
	int n,m,u,v;
	cin>>n>>m;
	Dinic g(n+m+10);
	int s=0,d=n+m+1;
	vector< pair<int,int> > ed;
	for(int i=0;i<m;i++)
	{
		cin>>u>>v;
		ed.push_back(make_pair(u,v));
	}
	int low=0,high=101010,mid,ans;
	while(low<=high)
	{
		
		mid=(low+high)/2;
		g.ClearGraph();
		for(int i=1;i<=m;i++)
		{
			g.addEdge(s,i,1);
		}
		for(int i=m+1;i<=m+n;i++)
		{
			g.addEdge(i,d,mid);
		}
		for(int i=0;i<m;i++)
		{
			g.addEdge(i+1,ed[i].first+m,1);
			g.addEdge(i+1,ed[i].second+m,1);
		}
		int f=g.GetMaxFlow(s,d);
		//cout<<mid<<" "<<f<<endl;
		if(f==m)
		{
			high=mid-1;
			ans=mid;
			{
			for(int i=0;i<m;i++)
			{		
				u=ed[i].first+m;v=ed[i].second+m;
				//cout<<g.GetFlow(i+1,u)<<" "<<g.GetFlow(i+1,v);
				if(g.GetFlow(i+1,u)) a[i]=1;
				else a[i]=0;
			}}
		}
		else
		{
			low=mid+1;
		}
	}
	cout<<ans<<endl;
	for(int i=0;i<m;i++)
	{		
		u=ed[i].first+m;v=ed[i].second+m;
		if(a[i]==1) cout<<u-m<<" "<<v-m<<endl;
		else cout<<v-m<<" "<<u-m<<endl;
	}
	return 0;
}
