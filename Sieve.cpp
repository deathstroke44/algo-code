#include<bits/stdc++.h>
using namespace std;
typedef long long int li;
#define pc(i) printf("Case %d: ",i+1)
vector<li> primes;
bool mark[1000010+10];
void sieve(li nx)
{
    li i,j,limit=sqrt(nx*1.0)+2;   
    memset(mark,0,sizeof(mark));
    mark[1]=1;
    mark[2]=0;
    primes.push_back(2);
    for(i=4;i<=nx;i+=2) mark[i]=1;
    for(i=3;i<=nx;i+=2)
    {
        if(!mark[i])
        {
            primes.push_back(i);
            if(i<=limit)
            {
                for(j=i*i;j<=nx;j+=2*i)
                {
                    mark[j]=1;
                }
            }
        }
    }
}
int main()
{
	return 0;
}
