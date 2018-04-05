#include<bits/stdc++.h>
using namespace std;
#define MAX 100000
int node[MAX][55],rote,nnode,root,isWord[MAX];
int gid(const char &c){
  	if(c >= 'A' and c <= 'Z') return c - 'A';
	return (c - 'a') + 26;	
}
void initialize()
{
	root=nnode=0;
	memset(node,-1,sizeof(node));
	memset(isWord,0,sizeof(isWord));
}
void insert(char* str, int len)
{
	int now=root;
	for(int i=0;i<len;i++)
	{
		if(node[now][gid(str[i])]==-1)
		{
			node[now][gid(str[i])]=++nnode;
			for(int j=0;j<26;j++)
			{
				node[nnode][j]=-1;
			}
			
		}
		now=node[now][gid(str[i])];
	}
	isWord[now]++;
}
int search(char* str, int len)
{
    int now = root;
    for (int i = 0; i < len; i++) {
        int id = gid(str[i]);
        if(node[now][gid(str[i])]==-1)
            return -1;
        now=node[now][gid(str[i])];
    }
    return isWord[now];
}
int main() {
       	//cout<<sizeof(node)<<endl;;
       
        int test, cs, i, j, len, n, q, res;
        char str[128], line[10009], *p;
        freopen("in.txt", "r", stdin);
        freopen("out.txt","w",stdout);
        
        scanf("%d", &test);
        for(cs = 1; cs <= test; cs++) {
        	initialize();
            //root = new node();
            scanf("%d", &n);
            gets(str);
            
            //memset(trie[0].next, -1, sizeof(int) * 52);
            for(i = 0; i < n; i++) {
                len = strlen(gets(str));
                if(len > 2) sort(str + 1, str + len - 1);
                //j = func(str, len, 0);
                //cnt[j]++;
                insert(str,strlen(str));
                //cout<<search(str, len)<<endl;
            }
            printf("Case %d:\n", cs);
            scanf("%d", &q);
            gets(str);
            while(q--) {
                gets(line);
                res = 1;
                p = strtok(line, " ");
                while(p) {
                    //printf("Search Call\n");
                   
                    len = strlen(p);
                    if(len > 2) sort(p + 1, p + len - 1);
                    j = search(p, len);
                    ///printf("%s %d\n",p,j);
                    if(j != -1 && j!=0) res *= j;
                    else { res = 0; break; }
                    p = strtok(0, " ");
                }
                printf("%d\n", res);
            }
            //del(root);
        }
        return 0;
    }

