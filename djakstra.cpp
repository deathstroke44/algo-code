#include<bits/stdc++.h>
using namespace std;
struct Node
{
    int at,cost;
    Node(int _at,int _cost)
    {
        at= _at;
        cost= _cost;
    }
};
bool operator<(Node A,Node B)
{
    return A.cost>B.cost;
}
struct Edge
{
    int v,w;
    Edge(int x,int y)
    {
        v=x;
        w=y;
    }
};
vector<Edge> adj[600];
priority_queue<Node> PQ;
int dist[600];
int n;
void dijkastra(int s)
{
    for(int i=1;i<=n;i++)
    {
        dist[i]=1000000000;
    }
    dist[s]=0;
    PQ.push(Node(s,0));
    while(!PQ.empty())
    {
        Node u=PQ.top();
        PQ.pop();
        if(u.cost!=dist[u.at])
        {
            continue;
        }
        for(int i=0;i<adj[u.at].size();i++)
        {
            Edge e=adj[u.at][i];
            if(dist[e.v]>u.cost+e.w)
            {
                dist[e.v]=u.cost+e.w;
                PQ.push(Node(e.v,dist[e.v]));
            }
        }
    }
}
int main()
{
    int ts,t=1,m,u,v,w,i;
    cin>>ts;
    for(int k=1;k<=ts;k++)
    {
        cin>>n>>m;
        for(i=1;i<=m;i++)
        {
            cin>>u>>v>>w;
            adj[u].push_back(Edge(v,w));
            adj[v].push_back(Edge(u,w));

        }
        //cin>>t;
        dijkastra(t);
        printf("Case %d: ",k);
        //puts("");

            if(dist[n]==1000000000) cout<<"Impossible"<<endl;
            else cout<<dist[n]<<endl;


        for(i=0;i<=n;i++)
        {
            adj[i].clear();
        }

    }
    return 0;
}

