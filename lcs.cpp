#include<bits/stdc++.h>
#define MAX 1007
using namespace std;
int dp[MAX][MAX];
int l1,l2;
char a[MAX],b[MAX];
int solve(int i,int j)
{
    if(i==l1 || j==l2)  return 0;
    int &ret = dp[i][j];
    if(ret==-1)
    {
        int x=0,y=0,z=0;
        if(a[i]==b[j])
            x = 1 + solve(i+1,j+1);
        y = solve(i+1,j);
        z = solve(i,j+1);
        ret = max(x,max(y,z));
    }
    return ret;
}
int main ()
{
    while(gets(a)!=NULL)
    {
        gets(b);
        l1 = strlen(a);
        l2 = strlen(b);
        memset(dp,-1,sizeof(dp));
        int res = solve(0,0);
        printf("%d\n",res);
    }
    return 0;
}
