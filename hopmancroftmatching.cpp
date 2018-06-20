#include <bits/stdc++.h>
using namespace std;
#define MAX 100010
#define clr(ar) memset(ar, 0, sizeof(ar))
#define read() freopen("lol.txt", "r", stdin)
#define dbg(x) cout << #x << " = " << x << endl
#define ran(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))
typedef pair<string,string> pss;


/// Hopcroft karp in O(m * sqrt(n))
namespace hc{ /// hash = 393558
	bool visited[MAX];
    vector <int> adj[MAX];
    int n, L[MAX], R[MAX], Q[MAX], len[MAX], dis[MAX], parent[MAX];

    inline void init(int nodes){ /// Number of vertices in the left set, or max(left_set, right_set)
        n = nodes, clr(len);
        for (int i = 0; i < MAX; i++) adj[i].clear();
    }

    inline void add_edge(int u, int v){ /// 0 based index
        len[u]++;
        adj[u].push_back(v);
    }

    bool dfs(int i){
        for (int j = 0; j < len[i]; j++){
            int x = adj[i][j];
            if (L[x] == -1 || (parent[L[x]] == i)){
                if (L[x] == -1 || dfs(L[x])){
                    L[x] = i, R[i] = x;
                    return true;
                }
            }
        }
        return false;
    }

    bool bfs(){
        clr(visited);
        int i, j, x, d, f = 0, l = 0;

        for (i = 0; i < n; i++){
            if (R[i] == -1){
                visited[i] = true;
                Q[l++] = i, dis[i] = 0;
            }
        }

        while (f < l){
            i = Q[f++];
            for (j = 0; j < len[i]; j++){
                x = adj[i][j], d = L[x];
                if (d == -1) return true;

                else if (!visited[d]){
                    Q[l++] = d;
                    parent[d] = i, visited[d] = true, dis[d] = dis[i] + 1;
                }
            }
        }
        return false;
    }

    int hopcroft_karp(){
        int res = 0;
        memset(L, -1, sizeof(L));
        memset(R, -1, sizeof(R));

        while (bfs()){
            for (int i = 0; i < n; i++){
                if (R[i] == -1 && dfs(i)) res++;
            }
        }
        return res;
    }
    
    void pp(int x)
    {
    	for(int i=0;i<=x;i++)
    	{
    		cout<<R[i]<<" "<<L[R[i]]<<endl;
		}
	}
}

vector<pss> votes;

void solve(int t)
{
	votes.clear();
	int n,m,f;
	string s1,s2;
	scanf("%d %d %d",&f,&m,&n);
	for(int i=0;i<n;i++)
	{
		cin>>s1>>s2;
		votes.push_back(pss(s1,s2));
	}
	hc::init(max(n, m)+50);
	for(int i=0;i<n;i++)
	{
		pss u=votes[i];
		if(u.first[0]=='F') continue;
		for(int j=0;j<n;j++)
		{
			pss v=votes[j];
			if(u.first==v.second || u.second==v.first)
			{
				hc::add_edge(i,j);	
			}	
		}
	}
	printf("Case %d: %d\n", t,n-hc::hopcroft_karp());
}

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
    	solve(i+1);
	}
    return 0;
}
