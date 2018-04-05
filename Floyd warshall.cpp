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
typedef long long int li;

void init()
{

}

li w[20][20];

void floyd_warshall(li st,li ed,bool inits)
{
	
	li i,j,k;
	if(inits)
	{
		for(i=st;i<=ed;i++)
		{
			for(j=st;j<=ed;j++)
			{
				w[i][j]=20000000;
			}
		}
		for(i=st;i<=ed;i++)
		{
			w[i][i]=0;
		}
	}
	else
	{
		for(k=st;k<=ed;k++)
			for(i=st;i<=ed;i++)
				for(j=st;j<=ed;j++)
					w[i][j]=min(w[i][j],w[i][k]+w[k][j]);	
	}
}

li dp[500010],degree[20],n,m;

li chinese_postman(int mask,int cnt)
{
	if(cnt==0) return 0;
	if(dp[mask]!=-1) return dp[mask];
	int i,j;
	dp[mask]=20000000;
	for(i=1;i<=n;i++)
	{
		if(degree[i] && !check(mask,i))
		{
			for(j=i+1;j<=n;j++)
			{		
				if(degree[j] && !check(mask,j) && w[i][j]!=20000000)
				{
					li tmask=set(mask,i);
					tmask=set(tmask,j);
					dp[mask]=min(w[i][j]+chinese_postman(tmask,cnt-2),dp[mask]);
				}
			}		
		}
	}
	return dp[mask];
}

void solve(int t)
{
	sfl(n);sfl(m);
	li u,v,ws;
	li ans=0;
	
	memset(dp,-1,sizeof(dp));
	memset(degree,0,sizeof(degree));
	floyd_warshall(1,n,true);
	for(int i=1;i<=m;i++)
	{
		sfl(u);sfl(v);sfl(ws);
		w[u][v]=min(w[u][v],ws);
		
		w[v][u]=min(w[v][u],ws);
		ans+=ws;
		degree[u]++;
		degree[v]++;
		degree[u]%=2;
		degree[v]%=2;
	}
	int count=0;
	for(int i=1;i<=n;i++)
	{
		if(degree[i]) {
			count++;
			//cout<<i<<endl;
		}
	}
	floyd_warshall(1,n,false);
	//cout<<w[1][3]<<endl;
	ans+=chinese_postman(0,count);
	pf("Case %d: %lld\n",t,ans);
}

int main()
{
	int t;
	sfi(t);
	init();
	for(int i=1;i<=t;i++)
	{
		solve(i);
	}
	return 0;
}
