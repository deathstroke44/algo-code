#include<bits/stdc++.h>
typedef int ll;
using namespace std;
ll n,m=1000000007;
int dp[20000];
int grundy(int n)
{
    if(n<=2) return 0;
    if(dp[n]!=-1) return dp[n];
    int m=(n-1)/2;
    map<int,int> flag;
    for(int i=1;i<=m;i++)
    {
        flag[grundy(n-i)^grundy(i)]=1;
    }
    int v=0;
    while(flag[v]!=0) v++;
    return dp[n]=v;
}
int main()
{
    ll t,i;
    cin>>t;
    memset(dp,-1,sizeof(dp));
    for(ll k=1;k<=t;k++)
    {

        cin>>n;
        int a[n],ans=0;
        for(i=0;i<n;i++)
        {
            cin>>a[i];
        }
        for(i=0;i<n;i++)
        {
            ans^=grundy(a[i]);
        }
        if(ans==0) printf("Case %d: Bob\n",k);
        else printf("Case %d: Alice\n",k);
    }
    return 0;
}
