#include<bits/stdc++.h>
using namespace std;
long long int mul[20][20],x[20][20],ans[20][20],mod,arr1[20],arr2[20],d;
void init()
{
	memset(x,0,sizeof(x));
	memset(ans,0,sizeof(ans));
	int l=0,h=d-1;
	while(l<=h)
	{
		swap(arr2[l],arr2[h]);
		l++;
		h--;
	}
	for(long long int i=0;i<d;i++)
	{
		arr1[d]%=mod;
		arr2[d]%=mod;
	}
	for(long long int i=0;i<d;i++) x[0][i]=arr1[i];
	for(long long int i=1;i<d;i++) x[i][i-1]=1;
	for(long long int i=0;i<d;i++) ans[i][i]=1;
	/*for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++) cout<<ans[i][j]<<" ";
		
		cout<<endl;
	}
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++) cout<<x[i][j]<<" ";
		
		cout<<endl;
	}*/
}
void multiply(long long int a[20][20],long long int b[20][20])
{
	for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            mul[i][j] = 0;
            for (int k = 0; k < d; k++){
                mul[i][j] += (a[i][k]*b[k][j])%mod;
                mul[i][j]%=mod;
            }
        }
    }
    for (int i=0; i<d; i++)
        for (int j=0; j<d; j++)
            a[i][j] = mul[i][j]; 
}

int power(int n)
{
	//long long int ans[2][2]={{1,0},{0,1}};
	//long long int x[2][2]={{1,1},{1,0}};
	//long long int xp[2][2]={{1,0},{0,1}};
	while(n>0)
	{
		
		
		if(n%2==1)
		{
			multiply(ans,x);
		}
		multiply(x,x);
		n=n/2;
	}
	/*for(int i=0;i<d;i++)
	{
		for(int j=0;j<d;j++) cout<<ans[i][j]<<" ";
		
		cout<<endl;
	}*/
	
	//return ans[0][0];
	long long int s=0;
	for(long long i=0;i<d;i++)
	{
		s+=((ans[0][i]%mod*arr2[i]%mod)%mod);
		s%=mod;
	}
	return s;
}
int main()
{
	long long int n;
	
	while(scanf("%lld %lld %lld",&d,&n,&mod)==3)
	{
		
		if(n==0 && mod==0 && d==0) break;
		//cout<<mod<<endl;
		for(long long int i=0;i<d;i++) scanf("%lld",&arr1[i]);
		for(long long int i=0;i<d;i++) scanf("%lld",&arr2[i]);
		init();
		if(n>d)printf("%lld\n",power(n-d)%mod);
		else printf("%lld\n",arr2[n-1]%mod);
	}
	return 0;
}


