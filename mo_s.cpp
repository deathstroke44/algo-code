#include <bits/stdc++.h>
using namespace std;
#define MAXV 110000
#define MAXSZ 110000
int block,ara[MAXSZ],cnt[MAXV],res[MAXSZ],ans,n,m;
struct data
{
	int l,r,id,b,seg;
	data(int n1,int n2,int n3,int n4)
	{
		l=n1;r=n2;id=n3;b=n4;
		seg=l/b;
	}
};
bool cmp(data a,data b)
{
	if(a.seg==b.seg) return a.r<b.r;
	return a.seg<b.seg;
}
vector<data> q;
void add(int id)
{
	cnt[ara[id]]++;
	if(cnt[ara[id]]==1) ans++;
}
void remove(int id)
{
	cnt[ara[id]]--;
	if(cnt[ara[id]]==0) ans--;
}
void mo()
{
	sort(q.begin(),q.end(),cmp);
	int L=0,R=0,l,r;
	ans=0;
	add(0);
	for(int i=0;i<q.size();i++)
	{
		l=q[i].l;r=q[i].r;
		while(L>l)
		{
			add(L-1);L--;
		}
		while(L<l)
		{
			remove(L);L++;
		}
		while(R>r)
		{
			remove(R);R--;
		}
		while(R<r)
		{
			add(R+1);R++;
		}
		res[q[i].id]=ans;
	}
	
	q.clear();
}
int solve(int t)
{
	scanf("%d %d",&n,&m);
	memset(cnt,0,sizeof(cnt));
	block=(int)sqrt(n);  
	for(int i=0;i<n;i++) scanf("%d",&ara[i]);
	for(int i=0;i<m;i++)
	{
		int x,y;
		scanf("%d %d",&x,&y);
		q.push_back(data(x-1,y-1,i,block));
	}
	//cout<<"Reach"<<endl;
	mo();
	printf("Case %d:\n",t);
	for(int i=0;i<m;i++)
	{
		printf("%d\n",res[i]);
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++) solve(i);
	return 0;
}
