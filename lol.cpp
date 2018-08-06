#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
vector< pii > adj[20];
int loop=0,n,m;
int vis[(1<<15)+10][16];
double dp[(1<<15)+10][16];
void init()
{
	for(int i=0;i<20;i++)
	{
		adj[i].clear();
	}
	loop++;
}

void solve(int t)
{
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		adj[u].push_back(pii(v,w));
		swap(u,v);
		adj[u].push_back(pii(v,w));
	}
}
	
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		init();
		solve(i);
	}
	return 0;
}
