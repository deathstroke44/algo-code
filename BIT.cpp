#include<bits/stdc++.h>
using namespace std;
#define sf(x) scanf("%d",&x)
int MAX=1002;
int BIT[1005];

void update(int x,int v)
{
	int y1;
	while(x<=MAX)
	{
		BIT[x]+=v;
		x+=(x & -x);
	}
}
int read(int x)
{
	int v=0;
	while(x>0)
	{
		v+=BIT[x];
		x-=(x & -x);
	}
	return v;
}

int main()
{
    
}

