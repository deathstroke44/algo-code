#include<bits/stdc++.h>
using namespace std;
#define sf(x) scanf("%d",&x)
int MAX=1002;
int BIT[1005][1005];

void update(int x,int y,int v)
{
	int y1;
	while(x<=MAX)
	{
		y1=y;
		while(y1<=MAX)
		{
			BIT[x][y1]+=v;
			y1+=(y1 & -y1);
		}
		x+=(x & -x);
	}
}
int read(int x,int y)
{
	int y1,v=0;
	while(x>0)
	{
		y1=y;
		while(y1>0)
		{
			v+=BIT[x][y1];
			y1-=(y1 & -y1);
		}
		x-=(x & -x);
	}
	return v;
}

int main()
{
    
}

