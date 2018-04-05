#include<bits/stdc++.h>
using namespace std;
#define MAX 10000
int ara[MAX];
struct node
{
	int sum;
}tree[4*MAX];
int lazy[4*MAX];
node merge(node a,node b)
{
	node ret;
	ret.sum=a.sum+b.sum;
	return ret;
}
void lazyUpdate(int n,int st,int ed)
{
	if(lazy[n]==0) return;
	tree[n].sum+=(ed-st+1)*lazy[n];
	if(st!=ed)
	{
		lazy[2*n]+=lazy[n];
		lazy[2*n+1]+=lazy[n];
	}
	lazy[n]=0;
}
void build(int n,int st,int ed)
{
	lazy[n]=0;
	if(st==ed) {
		tree[n].sum=ara[st];return;
	}
	int mid=(st+ed)/2;
	build(2*n,st,mid);
	build(2*n+1,mid+1,ed);
	tree[n]=merge(tree[2*n],tree[2*n+1]);	
}
node query(int n,int st,int ed,int i,int j)
{
	lazyUpdate(n,st,ed);
	if(st>=i && ed<=j) return tree[n];
	int mid=(st+ed)/2;
	if(mid<i) return query(2*n+1,mid+1,ed,i,j);
	else if(mid>=j) return query(2*n,st,mid,i,j);
	else return  merge(query(2*n+1,mid+1,ed,i,j),query(2*n,st,mid,i,j));
}
void update(int n,int st,int ed,int i,int j,int v)
{
	lazyUpdate(n,st,ed);
	if(st>j || ed<i) return;
	if(st>=i && ed<=j)
	{
		lazy[n]+=v;
		lazyUpdate(n,st,ed);
		return;
	}
	int mid=(st+ed)/2;
	update(2*n,st,mid,i,j,v);
	update(2*n+1,mid+1,ed,i,j,v);
	tree[n]=merge(tree[2*n],tree[2*n+1]);	
}
int main()
{
	int i,n,q,c,l,r,v;
	cin>>n>>q;
	for(i=1;i<=n;i++) cin>>ara[i];
	build(1,1,n);
	for(i=0;i<q;i++)
	{
		cin>>c;
		if(c==1)
		{
			cin>>l>>r>>v;
			update(1,1,n,l,r,v);
		}
		else
		{
			cin>>l>>r;
			node x=query(1,1,n,l,r);
			cout<<x.sum<<endl;
		}
	}
}




struct data {
    int minimum, maximum;
} tree[MAX*4];

data Merge(data l, data r) {
    data ret;
    ret.minimum = min(l.minimum, r.minimum);
    ret.maximum = max(l.maximum, r.maximum);
    return ret;
}

void init(int node, int beg, int endd) {
    if(beg == endd) {
        tree[node] = { arr[beg], arr[beg] };
        return;
    }

    int left = node*2;
    int right = node*2+1;
    int mid = (beg+endd) / 2;

    init(left, beg, mid);
    init(right, mid+1, endd);

    tree[node] = Merge(tree[left], tree[right]);
}

// beg, endd = tree range
// x, y = query range
data query(int node, int beg, int endd, int x, int y) {
    if(x > y) return { INT_MAX, INT_MIN }; // dummy
    if(beg == x && endd == y) return tree[node];

    int left = node*2;
    int right = node*2+1;
    int mid = (beg+endd) / 2;

    data l = query(left, beg, mid, x, min(y, mid));
    data r = query(right, mid+1, endd, max(x, mid+1), y);

    return Merge(l, r);
}

void update(int node, int beg, int endd, int x, int val) {
    if(beg == x && endd == x) {
        tree[node] = { val, val };
        return;
    }

    int left = node*2;
    int right = node*2+1;
    int mid = (beg+endd) / 2;

    if(x <= mid) update(left, beg, mid, x, val);
    else update(right, mid+1, endd, x, val);

    tree[node] = Merge(tree[left], tree[right]);
}

void update(int at,int L,int R,int l,int r)
{
	if(r<L || R<l) return;
	if(l<=L && R<=r) { toggle[at]^=1; return; }
	int mid=(L+R)/2;
	update(at*2,L,mid,l,r);
	update(at*2+1,mid+1,R,l,r);
}
int query(int at,int L,int R,int pos)
{
	//cout<<"loop"<<endl;
	if(pos<L || R<pos) return 0;
	if(L==pos && pos==R) {
	return toggle[at];}
	int mid=(L+R)/2;
	//cout<<toggle[at]<<endl;
	if(pos<=mid) return query(at*2,L,mid,pos)^toggle[at];
	else return query(at*2+1,mid+1,R,pos)^toggle[at];
}















Code: (Toggle Highlighting) (Open in Compiler)

    #include <bits/stdc++.h>
    using namespace std;
     
    const int MAX = 100003;
    //int n=7, arr[] = { 0, 2, 3, 7, 8, 6, 5, 11 };
    int n,arr[MAX*4];
    struct data {
        int minimum, maximum;
    } tree[MAX*4];
     
    data Merge(data l, data r) {
        data ret;
        ret.minimum = min(l.minimum, r.minimum);
        ret.maximum = max(l.maximum, r.maximum);
        return ret;
    }
     
    void init(int node, int beg, int endd) {
        if(beg == endd) {
            tree[node] = { arr[beg], arr[beg] };
            return;
        }
     
        int left = node*2;
        int right = node*2+1;
        int mid = (beg+endd) / 2;
     
        init(left, beg, mid);
        init(right, mid+1, endd);
     
        tree[node] = Merge(tree[left], tree[right]);
    }
     
    // beg, endd = tree range
    // x, y = query range
    data query(int node, int beg, int endd, int x, int y) {
        if(x > y) return { INT_MAX, INT_MIN }; // dummy
        if(beg == x && endd == y) return tree[node];
     
        int left = node*2;
        int right = node*2+1;
        int mid = (beg+endd) / 2;
     
        data l = query(left, beg, mid, x, min(y, mid));
        data r = query(right, mid+1, endd, max(x, mid+1), y);
     
        return Merge(l, r);
    }
     
    void update(int node, int beg, int endd, int x, int val) {
        if(beg == x && endd == x) {
            tree[node] = { val, val };
            return;
        }
     
        int left = node*2;
        int right = node*2+1;
        int mid = (beg+endd) / 2;
     
        if(x <= mid) update(left, beg, mid, x, val);
        else update(right, mid+1, endd, x, val);
     
        tree[node] = Merge(tree[left], tree[right]);
    }
     
    int main() {
        /*init(1, 1, n);
        data d = query(1, 1, n, 1, 6);
        cout << d.minimum << " " << d.maximum << endl;
        update(1, 1, n, 4, 11);
        d = query(1, 1, n, 2, 6);
        cout << d.minimum << " " << d.maximum << endl;*/
        int t,d,i,a,b;
        scanf("%d",&t);
        for(int k=1;k<=t;k++)
        {
            int ans=0;
            scanf("%d %d",&n,&d);
     
            for(i=1;i<=n;i++)
            {
                scanf("%d",&arr[i]);
            }
            init(1,1,n);
            printf("Case %d:\n",k);
            for(i=1;i<=d;i++)
            {
                scanf("%d %d",&a,&b);
                data df = query(1, 1, n,a,b);
                printf("%d\n",df.minimum);
            }
           
        }
        return 0;
    }


