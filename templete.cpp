#include<bits/stdc++.h>
using namespace std;
#define check(n, pos) (n & (1<<pos))
#define set(n, pos) (n | (1<<pos))
#define sf(n) scanf("%d", &n)
#define loop(i,x,n) for(int i=x; i<=n; i++)
#define sand(a,b) (a & b)
#define sor(a,b) (a | b)
#define sff(a,b) scanf("%d %d",&a,&b)
#define pc(i) printf("Case %d: ",i+1)
#define pf printf
#define mp make_pair
#define pb(a) push_back(a)
typedef long long int li;
typedef pair<int,int> pii;
li ipow(li base,li e,li mod)
{
	li ans=1LL;
	while(e>0)
	{
		if(e%2==1)
			ans=(ans*base)%mod;
		base=(base*base)%mod;
		e=e/2;
	}
	return ans;
}
struct point {
	int x;
	int y;
	point(){}
	point(int a,int b) {
		x=a;
		y=b;
	}
};
struct line {
	int a,b,c;
	line(){}
	line(int x1,int y1,int x2,int y2) {
		a=y1-y2;
		b=x2-x1;
		c=x1*(y2-y1)+y1*(x1-x2);
	}
	int dir(point p)
	{
		int d=a*p.x+b*p.y+c;
		if(d<0) return -1;
		else if(d>0) return 1;
		return 0;
	}
	bool isCroosed(point p1,point p2)
	{
		int d=dir(p1)+dir(p2);
		if(abs(d)==2) return false;
		return true;
	}
};
int main()
{
	point ps[]={point(8,5),point(7,6),point(1,1),point(6,6),point(4,0)};
	line l=line(ps[0].x,ps[0].y,ps[1].x,ps[1].y);
	cout<<l.isCroosed(ps[2],ps[3])<<endl;
	return 0;
}
