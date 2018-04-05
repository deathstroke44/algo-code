#include<bits/stdc++.h>
using namespace std;
#define MAX     100000
#define D(x)    cerr << #x " = " << x << '\n'
int n, q, A[MAX+10];
struct bucket{
    int st, ed;
    int lazy;
    int freq[MAX+2];
}B[320];
int bucketSize;
void propagate(int idx)
{
    for(int i = B[idx].st; i<=B[idx].ed; i++)
    {
        B[idx].freq[A[i]]--;
        A[i]+=B[idx].lazy;
        B[idx].freq[A[i]]++;
    }
    B[idx].lazy = 0;
}
void update(int st, int ed, int v)
{
    int LB = st/bucketSize;
    if(B[LB].lazy)
        propagate(LB);
    for(int i = st; i<= min(B[LB].ed, ed); i++)
    {
        B[LB].freq[A[i]]--;
        A[i] += v;
        B[LB].freq[A[i]]++;
    }
 
    int RB = ed/bucketSize;
    if(LB == RB)
        return;
    if(B[RB].lazy)
        propagate(RB);
    for(int i = B[RB].st; i<= ed; i++)
    {
        B[RB].freq[A[i]]--;
        A[i] += v;
        B[RB].freq[A[i]]++;
    }
 
    for(int i = LB+1; i< RB; i++)
        B[i].lazy += v;
}
 
int query(int st, int ed, int k)
{
    int ret = 0;
    int LB = st/bucketSize;
    if(B[LB].lazy)
        propagate(LB);
    for(int i = st; i<= min(B[LB].ed, ed); i++)
        ret += (A[i] == k);
 
    int RB = ed/bucketSize;
    if(LB == RB)
        return ret;
    if(B[RB].lazy)
        propagate(RB);
    for(int i = B[RB].st; i<= ed; i++)
        ret += (A[i] == k);
 
    for(int i = LB+1; i< RB; i++)
    {
        int nw = k-B[i].lazy;
        if(nw >= 0 && nw <= MAX)
            ret += B[i].freq[nw];
    }
    return ret;
}
 
void pre()
{
    int curBucket = 0;
    for(int i = 0, cnt = 0; i<n; i++, cnt++)
    {
        if(cnt == bucketSize)
        {
            cnt = 0;
            B[curBucket].ed = i-1;
            curBucket++;
            B[curBucket].st = i;
        }
        B[curBucket].freq[A[i]]++;
    }
    B[curBucket].ed = n;
}
 
int main()
{
  //  freopen("sample.txt", "r", stdin);
    //freopen("outputSample.txt", "w", stdout);
//    freopen("input2.txt", "r", stdin);
//    freopen("output2_Setter.txt", "w", stdout);
//    freopen("input1.txt", "r", stdin);
//    freopen("output1_Setter.txt", "w", stdout);
    int t;
    scanf("%d",&t);
    for(int cs = 1; cs<=t; cs++)
    {
        scanf("%d %d",&n,&q);
        memset(B,0,sizeof(B));
        bucketSize = sqrt(n);
        for(int i = 0; i<n; i++)
            scanf("%d",&A[i]);
        pre();
        printf("Case %d:\n",cs);
        int cnt = 0;
        while(q--)
        {
            int type, L, R, v;
            scanf("%d %d %d %d",&type, &L, &R, &v);
            L--,R--;
            if(type == 1)
                update(L,R,v);
            else
                printf("%d\n",query(L,R,v));
        }
    }
}
