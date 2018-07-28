#include<bits/stdc++.h>
using namespace std;
#define MAX 30005
typedef pair<int,int> pii;
int BIT[MAX];

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
struct data
{
	int l,r,k,id;
	data(int l_,int r_,int k_,int id_)
	{
		l=l_;r=r_;k=k_;id=id_;
	}
};
bool operator<(data d1,data d2)
{
	return d1.k<d2.k;
}
vector<data> in;
vector<int> ks;
map<int,int> flag;
int ans[200000+5];
vector<data> adj[200000+5];
vector<pii> values;
void solve()
{
	int q,n;
	scanf("%d",&n);
	for(int i=1;i<n+1;i++)
	{
		int t;
		scanf("%d",&t);
		values.push_back(pii(t,i));
	}
	sort(values.begin(),values.end());
	
	scanf("%d",&q);
	int cnt=0;
	for(int i=1;i<=q;i++)
	{
		int l,r,k;
		scanf("%d %d %d",&l,&r,&k);
		if(!flag[k])
		{
			ks.push_back(k);
			flag[k]=++cnt;
		}
		data dd=data(l,r,k,i);
		adj[flag[k]].push_back(dd);
	}
	sort(ks.begin(),ks.end());
	int p=n-1;
	for(int i=ks.size()-1;i>=0;i--)
	{
		int val=ks[i];
		while(p>=0 && val<values[p].first)
		{
			update(values[p].second,1);
		//	cout<<values[p].first<<" "<<values[p].second<<endl;
			p--;
		}
		int id=flag[val];
		for(int j=0;j<adj[id].size();j++)
		{
			data dd=adj[id][j];
			ans[dd.id]=read(dd.r)-read(dd.l-1);
		}
	}
	for(int i=1;i<=q;i++)
	{
		printf("%d\n",ans[i]);
	}
}
int main()
{
	solve();
}
