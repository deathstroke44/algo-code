#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,n) for(i=0; i<n; i++)
#define repl(i,n) for(i=1; i<=n; i++)
 
#define sz(x) (int) x.size()
#define pb push_back
#define all(x) x.begin(),x.end()
#define uu first
#define vv second
#define mem(x, y) memset(x, y, sizeof(x))
#define un(x) x.erase(unique(all(x)), x.end())
 
#define sdi(x) scanf("%d", &x)
#define sdii(x, y) scanf("%d %d", &x, &y)
#define sdiii(x, y, z) scanf("%d %d %d", &x, &y, &z)
#define sdl(x) scanf("%lld", &x)
#define sdll(x, y) scanf("%lld %lld", &x, &y)
#define sdlll(x, y, z) scanf("%lld %lld %lld", &x, &y, &z)
#define sds(x) scanf("%s", x)
#define pfi(x) printf("%d\n", x)
#define pfii(x, y) printf("%d %d\n", x, y)
#define pfiii(x, y, z) printf("%d %d %d\n", x, y, z)
#define pfl(x) printf("%lld\n", x)
#define pfll(x, y) printf("%lld %lld\n", x, y)
#define pflll(x, y, z) printf("%lld %lld %lld\n", x, y, z)
 
#define eps 1e-9
#define OK cerr << "ok\n"
#define DB(x) cerr << #x << " = " << x << endl
 
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair <int, int> pii;
 
inline int setBit(int N, int pos) { return N=N | (1<<pos); }
inline int resetBit(int N, int pos) { return N= N & ~(1<<pos); }
inline bool checkBit(int N, int pos) { return (bool)(N & (1<<pos)); }
 
//int kx[] = {+2, +1, -1, -2, -2, -1, +1, +2};
//int ky[] = {+1, +2, +2, +1, -1, -2, -2, -1}; //Knight Direction
//int fx[] = {+0, +0, +1, -1, -1, +1, -1, +1};
//int fy[] = {-1, +1, +0, +0, +1, +1, -1, -1}; //Four & Eight Direction
 
 
const int MAX = 53;
int n, profit[MAX][MAX];
 
#define MAXIMIZE +1
#define MINIMIZE -1
#define inf 1000000000
 
namespace wm {
    bool visited[MAX];
    int U[MAX], V[MAX], P[MAX], way[MAX], minv[MAX], match[MAX], ar[MAX][MAX];
 
    /// n = number of row and m = number of columns in 1 based, flag = MAXIMIZE or MINIMIZE
    /// match[i] contains the column to which row i is matched
    int hungarian(int n, int m, int mat[MAX][MAX], int flag){
        mem(U, 0); mem(V, 0); mem(P, 0); mem(ar, 0); mem(way, 0);
 
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                ar[i][j] = mat[i][j];
                if (flag == MAXIMIZE) ar[i][j] = -ar[i][j];
            }
        }
        if (n > m) m = n;
 
        int i, j, a, b, d, r, w;
        for (i = 1; i <= n; i++){
            P[0] = i, b = 0;
            for (j = 0; j <= m; j++) minv[j] = inf, visited[j] = false;
 
            do{
                visited[b] = true;
                a = P[b], d = 0, w = inf;
 
                for (j = 1; j <= m; j++){
                    if (!visited[j]){
                        r = ar[a][j] - U[a] - V[j];
                        if (r < minv[j]) minv[j] = r, way[j] = b;
                        if (minv[j] < w) w = minv[j], d = j;
                    }
                }
 
                for (j = 0; j <= m; j++){
                    if (visited[j]) {
                        U[P[j]] += w, V[j] -= w;
                        V[j] = min(V[j],  inf); /// delimiter
                        V[j] = max(V[j], -inf); /// delimiter
                    }
                    else minv[j] -= w;
                }
                b = d;
            } while (P[b] != 0);
 
            do{
                d = way[b];
                P[b] = P[d], b = d;
            } while (b != 0);
        }
        for (j = 1; j <= m; j++) match[P[j]] = j;
 
        return (flag == MINIMIZE) ? -V[0] : V[0];
    }
}
 
int main() {
//    assert(freopen("in.txt","r",stdin));
//    assert(freopen("out.txt","w",stdout));
 
    int test, kase=1, i, j;
 
    sdi(test);
    while(test--) {
        sdi(n);
        repl(i, n) {
            repl(j, n) {
                sdi(profit[i][j]);
            }
        }
        printf("Case %d: %d\n", kase++, wm::hungarian(n, n, profit, MAXIMIZE));
    }
 
    return 0;
}
