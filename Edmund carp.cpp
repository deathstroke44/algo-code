#include<bits/stdc++.h>
using namespace std;
#define MAX 120
#define INF 1<<29
int cap[MAX][MAX],par[MAX],mcap[MAX];
vector<int> adj[MAX];
bool getpath(int s,int d,int n)
{
    memset(par,-1,sizeof(par));
    for(int i=1;i<=n;i++) mcap[i]=INF;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=1;i<=n;i++)
        {
            if(cap[u][i]!=0 && par[i]==-1)
            {
                par[i]=u;
                mcap[i]=min(mcap[u],cap[u][i]);
                if(i==d) return true;
                q.push(i);
            }
        }
    }
    return false;
}
int getflow(int s,int d,int n)
{
    int F=0;
    while(getpath(s,d,n))
    {
        //cout<<"EMD:"<<endl;
        int f=mcap[d];
        F+=f;
        int u=d;
        while(u!=s)
        {
            int v=par[u];
            //if(v==-1) break;
            cap[u][v]+=f;
            cap[v][u]-=f;
            u=v;
        }
    }
    return F;
}
void init()
{
    memset(cap,0,sizeof(cap));
 
}
int main()
{
    int t,s,d,c,u,v,f,n;
    scanf("%d",&t);
    for(int ts=1;ts<=t;ts++)
    {
        init();
        scanf("%d",&n);
        scanf("%d %d %d",&s,&d,&c);
        for(int i=0;i<c;i++)
        {
            scanf("%d %d %d",&u,&v,&f);
            cap[u][v]+=f;
            cap[v][u]+=f;
        }
        //cout<<"EMD:"<<endl;
        printf("Case %d: %d\n", ts ,getflow(s,d,n));
    }
}
