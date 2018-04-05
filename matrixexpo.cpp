#include<bits/stdc++.h>
using namespace std;
long long int mul[2][2],pa[30],mod;
void init()
{
	pa[0]=1;
	for(long long int i=1;i<=20;i++)
	{
		pa[i]=2*pa[i-1];
	}
}
void multiply(long long int a[2][2],long long int b[2][2])
{
	for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            mul[i][j] = 0;
            for (int k = 0; k < 2; k++){
                mul[i][j] += a[i][k]*b[k][j];
                mul[i][j]%=mod;
            }
        }
    }
    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++)
            a[i][j] = mul[i][j]; 
}

int power(int n)
{
	long long int ans[2][2]={{1,0},{0,1}};
	long long int x[2][2]={{1,1},{1,0}};
	long long int xp[2][2]={{1,0},{0,1}};
	while(n>0)
	{
		
		
		if(n%2==1)
		{
			multiply(ans,x);
		}
		multiply(x,x);
		n=n/2;
	}
	//for(int i=0;i<2;i++)
	//{
	//	for(int j=0;j<2;j++) cout<<ans[i][j]<<" ";
		
	//	cout<<endl;
	//}
	
	return ans[0][0];
}
int main()
{
	long long int n,m;
	init();
	while(scanf("%lld %lld",&n,&m)==2)
	{
		mod=pa[m];
		if(n)printf("%lld\n",power(n-1)%mod);
		else printf("0\n");
	}
	return 0;
}

