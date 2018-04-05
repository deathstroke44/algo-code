#include<bits/stdc++.h>
using namespace std;
#define MAX 300
#define infs 100000000
#define pp pair<int,int>
#define mclear(a, x) ( memset(a,x,sizeof(a)) )
#define pii pair <int, int>
#define pb push_back
#define sf(a) scanf("%d",&a)
#define sff(a,b) scanf("%d %d",&a,&b)
#define sfff(a,b,c) scanf("%d %d %d",&a,&b,&c)
#define printcase(a,b) printf("Case %d: %d\n",a,b)
#define mp(a,b) make_pair(a,b)
struct edge
{
    int u,v,w;
    edge(int a,int b,int c)
    {
        u=a;
        v=b;
        w=c;   
    }  
};
int dis[MAX];
vector<edge> v;
vector<int> adj[MAX];
bool cycle[MAX];
void dfs(int u)
{
    if(cycle[u]) return;
    cycle[u]=true;
    for(int i=0;i<adj[u].size();i++)
    {
        dfs(adj[u][i]);
    }
}
void belmon_ford(int n)
{
    for(int i=1;i<=n;i++) {
        dis[i]=infs;cycle[i]=false;
    }
    dis[1]=0;
    for(int j=1;j<=n-1;j++){
   
        for(int i=0;i<v.size();i++)
        {
            edge e=v[i];
           
            if(dis[e.u]!=infs) dis[e.v]=min(dis[e.v],dis[e.u]+e.w);
        }
    }
    for(int i=0;i<v.size();i++)
    {
            edge e=v[i];
            if(dis[e.u]!=infs && dis[e.v]>dis[e.u]+e.w)
            {
                dfs(e.v);
            }
    }
}
int main()
{
    int q,t,n,m,a[MAX],s,d;
    sf(t);
    for(int k=1;k<=t;k++)
    {
        printf("Case %d:\n",k);
        sf(n);
        for(int i=1;i<=n;i++) sf(a[i]);
        sf(m);
        for(int i=1;i<=m;i++)
        {
            sff(s,d);
            adj[s].pb(d);
            v.pb(edge(s,d,(a[d]-a[s])*(a[d]-a[s])*(a[d]-a[s])));
        }
        belmon_ford(n);
        sf(q);
        for(int i=0;i<q;i++)
        {
            sf(d);
            if(dis[d]==infs || dis[d]<3 || cycle[d])
            {
                printf("?\n");
            }
            else printf("%d\n",dis[d]);
        }
        for(int i=1;i<=n;i++) adj[i].clear();
        v.clear();
    }
    return 0;
}