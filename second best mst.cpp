
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int MAX_N = 105;
const int MAX_M = 205;
const int MAX_P = 10; //lgN
const int INF = 1e9+7;

struct Edge {
    int a,b,c;
} edg[MAX_M];

bool operator<(const Edge &e1,const Edge &e2) {
    return e1.c<e2.c;
}

Edge MP(int _a,int _b,int _c) {
    Edge ret;
    ret.a=_a;
    ret.b=_b;
    ret.c=_c;
    return ret;
}

struct DisjointSet {
    int p[MAX_N];
    void init(int n) {
        for (int x=0;n>=x;x++) p[x]=x;
    }
    int Find(int x) {
        return p[x]==x?x:p[x]=Find(p[x]);
    }
    void Union(int x,int y) {
        p[Find(x)] = Find(y);
    }
} djs;

int parent[MAX_N];
int depth[MAX_N];
pii lca[MAX_P][MAX_N];
vector<pii> tree_edg[MAX_N];  //end, weight
bool visit[MAX_N];
bool in_MST[MAX_M];
int binary[MAX_P];

void init() {
    for (int x=0;MAX_N>x;x++) tree_edg[x].clear();
}

int Kruskal(int n,int m) {
    for (int x=0;m>x;x++) in_MST[x]=false;
    djs.init(n);
    sort(edg,edg+m);
    int cnt=0;
    int ret=0;
    for (int i=0;m>i;i++) {
        while (i<m && djs.Find(edg[i].a) == djs.Find(edg[i].b)) i++;
        if (i==m) break;
        ret += edg[i].c;
        int a=edg[i].a;
        int b=edg[i].b;
        int c=edg[i].c;
        tree_edg[a].push_back(make_pair(b,c));
        tree_edg[b].push_back(make_pair(a,c));
        in_MST[i]=true;
        cnt++;
        djs.Union(edg[i].a,edg[i].b);
    }
    return (cnt==n-1?ret:-1);
}

void build_tree(int id,int cur_depth) {
    visit[id]=true;
    depth[id] = cur_depth;
    for (vector<pii>::iterator i=tree_edg[id].begin();i!=tree_edg[id].end();i++) {
        pii a=*i;
        int t=a.first;
        if (visit[t]==false) {
            build_tree(t,cur_depth+1);
            parent[t]=id;
            lca[1][t] = make_pair(id,a.second);
        }
    }
}

pii walk(int x,int depth) {
//    cout<<"x="<<x<<" , depth="<<depth<<" , ";
    memset(binary,0,sizeof(binary));
    int tmp=depth;
    int id=1;
    while (tmp>0) {
        binary[id++] = tmp%2;
        tmp/=2;
    }
    int mx=0;
    for (int i=1;id>i;i++) {
        if (binary[i]==1) {
            mx=max(mx,lca[i][x].second);
            x = lca[i][x].first;
        }
    }
//    cout<<x<<","<<mx<<endl;
    return make_pair(x,mx);
}

int FFind(int x,int y) {
    int L=1,R=min(depth[x],depth[y]) + 1;
    while (R-L!=1) {
        int mid=(L+R)>>1;
//        cout<<"mid="<<mid<<endl;
        if (walk(x,depth[x]-mid).first == walk(y,depth[y]-mid).first) L=mid;
        else R=mid;
    }
    return max(walk(x,depth[x]-L).second,walk(y,depth[y]-L).second);
}

int main (){
    int T;
    scanf("%d",&T);
    for (int qq=0;T>qq;qq++) {
        int n,m;
        scanf("%d %d",&n,&m);
        for (int x=0;m>x;x++) {
            int i,j,k;
            scanf("%d %d %d",&i,&j,&k);
            edg[x]=MP(i,j,k);
        }
        if (n>m+1) {
            printf("Case #%d : No way\n",qq+1);
            continue;
        }
        init();
        int sum=Kruskal(n,m);
        if (sum==-1) {
            printf("Case #%d : No way\n",qq+1);
            continue;
        }
        if (n==m+1) {
            printf("Case #%d : No second way\n",qq+1);
            continue;
        }
        //seen 1 as root
        for (int x=0;n>=x;x++) lca[0][x] = make_pair(x,0);
        for (int x=0;MAX_P>x;x++) lca[x][1] = make_pair(1,0);
        for (int x=1;n>=x;x++) visit[x]=false;
        parent[1]=1;
        build_tree(1,1);
        for (int x=2;MAX_P>x;x++) {
            for (int y=2;n>=y;y++) {
                lca[x][y] = make_pair(lca[x-1][lca[x-1][y].first].first , max(lca[x-1][y].second,lca[x-1][lca[x-1][y].first].second));
            }
        }
//        for (int x=0;MAX_P>x;x++) {
//            for (int y=0;n>=y;y++) {
//                cout<<lca[x][y].first<<','<<lca[x][y].second<<' ';
//            }
//            cout<<endl;
//        }
        int ans=INF;
        for (int x=0;m>x;x++) {
            if (in_MST[x]==false) {
                int ret=FFind(edg[x].a,edg[x].b);
                ans = min(ans,sum -ret + edg[x].c);
            }
        }
        printf("Case #%d : %d\n",qq+1,ans);
    }
}

