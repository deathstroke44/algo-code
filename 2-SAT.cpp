#include<bits/stdc++.h>
using namespace std;
#define sfi(a) scanf("%d",&a)
#define sfl(a) scanf("%lld",&a)
#define sff(a) scanf("%lf",&a)
#define sfs(a) scanf("%s",&a)
#define pf printf
#define MAX 110
#define mymax(a,b,c) max(a,max(b,c))
#define mymin(a,b,c) min(a,min(b,c))
#define mymiddle(a,b,c) a+b+c-max(a,max(b,c))-min(a,min(b,c))
#define check(n, pos) (n & (1<<pos))
#define set(n, pos) (n | (1<<pos))
#define sq(x) ((x)*(x))
#define sf scanf
#define pb push_back
typedef long long int li;

int val[20100],vis[20100],com[20100],cnum,is[20100];
vector<int> adj[20100],adji[20100],adjc[20100],adjcom[20100],lists;

void init(int n)
{
	for(int i=1;i<=n;i++)
	{
		adj[i].clear();
		adji[i].clear();
		adjc[i].clear();
		adjcom[i].clear();
	}
	memset(is,0,sizeof(is));
}

void dfs(int x)
{
    vis[x]=1;
   
    for(int i=0;i<adj[x].size();i++)
    {
        int j=adj[x][i];
        if(!vis[j])
        {
            dfs(j);
        }
    }  
    lists.push_back(x);
}

void dfsscc(int x)
{
    //cout<<x<<" Reach"<<endl;
	vis[x]=1;
   
    for(int i=0;i<adjcom[x].size();i++)
    {
        int j=adjcom[x][i];
        if(!vis[j])
        {
            dfsscc(j);
        }
    }  
    lists.push_back(x);
}

void dfs1(int x,int c)
{
    vis[x]=1;
    com[x]=c;
    adjc[c].pb(x);
    for(int i=0;i<adji[x].size();i++)
    {
        int j=adji[x][i];
        if(!vis[j])
        {
            dfs1(j,c);
        }
    }
}
 
void dfssort(int n)
{
    lists.clear();
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
        if(!vis[i]) dfs(i);
    }
}
void scc(int n)
{
   
    dfssort(n);
    memset(vis,0,sizeof(vis));
    int c=0,i,j;
    for(i=lists.size()-1;i>=0;i--)
    {
        if(!vis[lists[i]]) dfs1(lists[i],++c);
    }
    cnum=c;
    //cout<<"Compo "<<cnum<<endl;
    //for(int i=1;i<=n;i++) cout<<com[i]<<endl;
}

void conversion(int n)
{
	map<pair<int,int>,int> mp;
	for(int i=1;i<=n;i++)
	{
		int u=i,v;
		for(int j=0;j<adj[i].size();j++)
		{
			v=adj[i][j];
			//cout<<com[u]<<" "<<com[v]<<endl;
			if(!mp[make_pair(com[u],com[v])])
			{
				adjcom[com[u]].pb(com[v]);
				mp[make_pair(com[u],com[v])]=1;
			}
		}
	}
	lists.clear();
    memset(vis,0,sizeof(vis));
    //cout<<"Compo "<<cnum<<endl;
    for(int i=1;i<=cnum;i++)
    {
    	//cout<<i<<endl;
        if(!vis[i]) dfsscc(i);
    }
    
	memset(val,-1,sizeof(val));
	for(int i=0;i<lists.size();i++)
    {
    	int setvalue=1;
    	int node=lists[i];
    	//cout<<node<<endl;
    	for(int j=0;j<adjc[node].size();j++)
    	{
    		int u=adjc[node][j],v;
    		if(u<=n/2)
    		{
    			v=u+n/2;
			}
			else
			{
				v=u-n/2;
			}
			if(val[com[v]]==1)
			{
				setvalue=0;
				break;	
			}
		}
		val[node]=setvalue;
	}
}

void solve(int t)
{
	int n,m,u,v;
	sf("%d %d",&m,&n);
	init(2*n);
	for(int i=1;i<=m;i++)
	{
		sf("%d %d",&u,&v);
		if(u>0) is[u]=1;
		if(v>0) is[v]=1;
		if(u>0 && v>0)
		{
			adj[n+u].pb(v);
			adj[n+v].pb(u);
			adji[u].pb(n+v);
			adji[v].pb(n+u);
		}
		else if(u>0 && v<0)
		{
			adj[n+u].pb(n-v);
			adj[-v].pb(u);
			adji[n-v].pb(n+u);
			adji[u].pb(-v);
		}
		else if(u<0 && v>0)
		{
			swap(u,v);
			adj[n+u].pb(n-v);
			adj[-v].pb(u);
			adji[n-v].pb(n+u);
			adji[u].pb(-v);
		}
		else if(u<0 && v<0)
		{
			adj[-u].pb(n-v);
			adj[-v].pb(n-u);
			adji[n-v].pb(-u);
			adji[n-u].pb(-v);
		}
	}
	scc(2*n);
	char *str="Yes";
	for(int i=1;i<=n;i++)
	{
		if(com[i]==com[n+i]) str="No";
	}
	
	pf("Case %d: %s\n",t,str);
	if(str=="Yes")
	{
		conversion(2*n);
	}
	else return;
	vector<int> vs;
	for(int i=1;i<=n;i++)
	{
		if(val[com[i]]==1)
		{
			vs.pb(i);
		}
	}
	pf("%d",vs.size());
	for(int i=0;i<vs.size();i++)
	{
		pf(" %d",vs[i]);
	}
	puts("");
}

int main()
{
	int t;
	sfi(t);
	for(int i=1;i<=t;i++)
	{
		solve(i);
	}
	return 0;
}
