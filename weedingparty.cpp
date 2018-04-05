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
typedef pair<long long int,long long int> pii;
typedef long long int li;

void init()
{

}

li w[520][520];
li n,m,s;
li shops[20];
pii dp[1<<16][16];
bool vis[1<<16][16];
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

pii call(li mask,li last,li cnt)
{
    if(vis[mask][last])  return dp[mask][last];
    if(cnt==s)
    {
        return make_pair(0,w[shops[last]][n-1]);
    }
    vis[mask][last]=true;
    dp[mask][last]=make_pair(-100,-100);
    li i;
    pii temp;
    if(w[last][n-1]==20000000) dp[mask][last]=make_pair(-100,-100);
    else dp[mask][last]=make_pair(0,w[last][n-1]);
    for(i=0;i<s;i++)
    {
        if(w[shops[last]][shops[i]]==20000000) continue;
        if(!check(mask,i))
        {
            li x=shops[i];
            if(w[shops[i]][n-1]==20000000) continue;
            pii temp;
            temp=call(set(mask,i),i,cnt+1);
            temp.first+=1;
            temp.second+=w[shops[last]][x];
            if(temp.first>dp[mask][last].first) dp[mask][last]=temp;
            else if(temp.first==dp[mask][last].first && temp.second<dp[mask][last].second) dp[mask][last]=temp;
        }
    }
    return dp[mask][last];
}

void solve(int t)
{
    li n,m,s,i,u,v,ws;
    sfl(n);sfl(m);sfl(s);
    bool check=false;
    floyd_warshall(0,n-1,true);
    memset(vis,0,sizeof(vis));
    for(i=0;i<s;i++) sfl(shops[i]);
    for(i=0;i<m;i++)
    {
        sfl(u);sfl(v);sfl(ws);
        w[u][v]=min(w[u][v],ws);
        check=check || (shops[i]==0);
    }
    pii ans;
    floyd_warshall(1-1,n-1,false);
    if(check) ans=call(1,0,1);
    else ans=call(0,0,0);
	pf("Case %d: %lld %lld\n",t,ans.first,ans.second);
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

