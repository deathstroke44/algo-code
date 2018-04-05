#include<bits/stdc++.h>
using namespace std;
#define MAX 250010
typedef long long int li;
li marks=-1000000;
li cnt1[4*MAX],cnt2[4*MAX];
struct node
{
	li sum,sets,st,ed;
	node(){
		sets=marks;
		st=marks;
		ed=marks;
	}
	node copy(node a)
	{
		if(sets!=marks){
		
			a.sets=sets;
			a.ed=ed;
			a.st=st;
		}
		else
		{
			if(a.ed==marks) a.ed=0;
			if(a.st==marks) a.st=0;
			a.ed+=ed;
			a.st+=st;
		}
		return a;
	}
	void reset()
	{
		sets=marks;
		st=marks;
		ed=marks;
	}
}tree[4*MAX];
node merge(node a,node b)
{
	node ret;
	ret.sum=a.sum+b.sum;
	return ret;
}
li call(li a)
{
	li n1=a,n2=a+1;
	if(n1%2==0) n1/=2;
	else n2/=2;
	return n1*n2;
}
void lazyUpdate(li n,li st,li ed)
{
	if(tree[n].sets==marks && tree[n].st==marks && tree[n].ed==marks) return;
	if(tree[n].sets!=marks) tree[n].sum=(ed-st+1)*tree[n].sets;
	if(tree[n].st!=marks)
	{
		
		tree[n].sum+=(ed-st+1)*(1-tree[n].st)+cnt1[n]*(call(ed)-call(st-1));
	}
	if(tree[n].ed!=marks)
	{
		
		tree[n].sum+=(ed-st+1)*(1+tree[n].ed)+cnt2[n]*(-call(ed)+call(st-1));
	}
	if(st!=ed)
	{
		
		if(tree[n].sets!=marks){
		
			tree[2*n].sets=tree[n].sets;
			tree[2*n].ed=tree[n].ed;
			tree[2*n].st=tree[n].st;
			tree[2*n+1].sets=tree[n].sets;
			tree[2*n+1].ed=tree[n].ed;
			tree[2*n+1].st=tree[n].st;
			cnt1[2*n]=cnt2[2*n]=cnt1[2*n+1]=cnt2[2*n+1]=0;
			if(tree[n].st!=marks)
			{
				cnt1[2*n]=cnt1[n];
				cnt1[2*n+1]=cnt1[n];
			}
			if(tree[n].ed!=marks)
			{
				cnt2[2*n]=cnt2[n];
				cnt2[2*n+1]=cnt2[n];
			}
		}
		else
		{
			
			if(tree[n].ed!=marks && tree[2*n].ed==marks) tree[2*n].ed=0;
			if(tree[n].st!=marks && tree[2*n].st==marks) tree[2*n].st=0;
			if(tree[n].ed!=marks) tree[2*n].ed+= tree[2*n].ed==0 ?  tree[n].ed : tree[n].ed+1;
			if(tree[n].st!=marks) tree[2*n].st+= tree[2*n].st==0 ?  tree[n].st : -1+tree[n].st;
			if(tree[n].ed!=marks && tree[2*n+1].ed==marks) tree[2*n+1].ed=0;
			if(tree[n].st!=marks && tree[2*n+1].st==marks) tree[2*n+1].st=0;
			if(tree[n].ed!=marks) tree[2*n+1].ed+= tree[2*n+1].ed==0 ?  tree[n].ed : tree[n].ed+1;
			if(tree[n].st!=marks) tree[2*n+1].st+= tree[2*n+1].st==0 ?  tree[n].st : -1+tree[n].st;
			if(tree[n].st!=marks)
			{
				cnt1[2*n]+=cnt1[n];
				cnt1[2*n+1]+=cnt1[n];
			}
			if(tree[n].ed!=marks)
			{
				cnt2[2*n]+=cnt2[n];
				cnt2[2*n+1]+=cnt2[n];
			}
		}
		
	}
	cnt1[n]=cnt2[n]=0;
	tree[n].reset();
}
void build(li n,li st,li ed)
{
	tree[n].reset();
	if(st==ed) {
		tree[n].sum=0;return;
	}
	li mid=(st+ed)/2;
	build(2*n,st,mid);
	build(2*n+1,mid+1,ed);
	tree[n]=merge(tree[2*n],tree[2*n+1]);	
}
node query(li n,li st,li ed,li i,li j)
{
	lazyUpdate(n,st,ed);
	if(st>=i && ed<=j) return tree[n];
	li mid=(st+ed)/2;
	if(mid<i) return query(2*n+1,mid+1,ed,i,j);
	else if(mid>=j) return query(2*n,st,mid,i,j);
	else return  merge(query(2*n+1,mid+1,ed,i,j),query(2*n,st,mid,i,j));
}
void updateC(li n,li st,li ed,li i,li j,li v)
{
	lazyUpdate(n,st,ed);
	if(st>j || ed<i) return;
	if(st>=i && ed<=j)
	{
		tree[n].sets=v;
		tree[n].st=marks;
		tree[n].ed=marks;
		lazyUpdate(n,st,ed);
		return;
	}
	li mid=(st+ed)/2;
	updateC(2*n,st,mid,i,j,v);
	updateC(2*n+1,mid+1,ed,i,j,v);
	tree[n]=merge(tree[2*n],tree[2*n+1]);	
}
void updateB(li n,li st,li ed,li i,li j,li c)
{
	lazyUpdate(n,st,ed);
	if(st>j || ed<i) return;
	if(st>=i && ed<=j)
	{
		
		if(c==1){
			cnt1[n]++;
			if(tree[n].st==marks) tree[n].st=i;
			else tree[n].st+=i;
			
		}
		else
		{
			cnt2[n]++;
			if(tree[n].ed==marks) tree[n].ed=j;
			else tree[n].ed+=j;
		}
		
		lazyUpdate(n,st,ed);
		
		return;
	}
	li mid=(st+ed)/2;
	updateB(2*n,st,mid,i,j,c);
	updateB(2*n+1,mid+1,ed,i,j,c);
	tree[n]=merge(tree[2*n],tree[2*n+1]);	
}
int main()
{
	li t,a,b,c,v,sc;
	scanf("%lld",&t);
	char s[10];
	for(int i=1;i<=t;i++)
	{
		memset(cnt1,0,sizeof(cnt1));
		memset(cnt2,0,sizeof(cnt2));
		scanf("%lld",&sc);
		printf("Case %d:\n",i);
		build(1,1,MAX);
		for(int j=1;j<=sc;j++){
		scanf("%s %lld %lld",s,&a,&b);
		if(s[0]=='A') {
			updateB(1,1,MAX,a,b,1);
			
		}
		else if(s[0]=='B') updateB(1,1,MAX,a,b,0);
		else if(s[0]=='C') {
			scanf("%lld",&v);
			updateC(1,1,MAX,a,b,v);
		}
		else
		{
			printf("%lld\n",query(1,1,MAX,a,b).sum);
		}
		}
	}
	return 0;
}
