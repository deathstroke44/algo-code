#include<bits/stdc++.h>
using namespace std;
#define MAX 100000
#define inf 200000000
int n,a[MAX],I[MAX],L[MAX],length=0;
int lis()
{
	int i;
	I[i]=-inf;
	for(i=1;i<=n;i++)
	{
		I[i]=inf;
	}
	for(i=0;i<n;i++)
	{
		int low, high, mid; // variables to perform binary search

        low = 0; // minimum position where we to put data in I[]

        high = length; // the maximum position

 

        while( low <= high ) { // binary search to find the correct position
			mid = ( low + high ) / 2;
			if( I[mid] < a[i] ) low = mid + 1;
			else high = mid - 1;
		}
		L[i]=low;
		I[low]=a[i];
		length=max(low,length);
	}
	return length;
}
void print()
{
	int x=length;
	vector<int> vss;
	for(int i=n-1;i>=0;i--)
	{
		if(L[i]==x) 
		{
			vss.push_back(a[i]);
			x--;
		}
		
	}
	for(int i=length-1;i>=0;i--) printf("%d ",vss[i]);
	puts("");
}
void printall()
{
	int x=length;
	vector<int> vss;
	for(int i=n-1;i>=0;i--)
	{
		if(L[i]==x) 
		{
			vss.push_back(a[i]);
			x--;
		}
		
	}
	for(int i=length-1;i>=0;i--) printf("%d ",vss[i]);
	puts("");
}
void solve()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("%d\n",lis());
	print();
}
int main()
{
	solve();
	return 0;
}

