#include<bits/stdc++.h>
using namespace std;
typedef long long li;
string multiply(string s1,string s2)
{
	int i,j,tmp;
	int l1=s1.size();
	int l2=s2.size();
	int ans[l1+l2+1]={0},a[l1+l2+1],b[l1+l2+1];
	
	string ret="";
	for(i = l1-1,j=0;i>=0;i--,j++)
    {
        a[j] = s1[i]-'0';
    }
    for(i = l2-1,j=0;i>=0;i--,j++)
    {
        b[j] = s2[i]-'0';
    }
    for(i = 0;i < l2;i++)
    {
        for(j = 0;j < l1;j++)
        {
            ans[i+j] += b[i]*a[j];
        }
    }
    for(i = 0;i < l1+l2;i++)
    {
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }
    for(i = l1+l2; i>= 0;i--)
    {
        if(ans[i] > 0)
            break;
    }
    for(;i >= 0;i--)
    {
    	//printf("%d",ans[i]);
		ret+=(ans[i]+'0');
    }
    
    return ret;
}
int main()
{
	li t;
	string a,b;
	//cout<<multiply("4096","4")<<endl;
	cin>>t;
	for(int k=1;k<=t;k++)
	{
		string ans="1";
		cin>>a>>b;
		for(int i=1;;i++)
		{
			ans=multiply(ans,a);
			bool flag=true;
			if(ans.size()>=b.size())
			{
				for(int is=0;is<b.size();is++)
				{
					if(ans[is]!=b[is])
					{
						flag=false;
						break;
					}
				}
			}
			else
			{
				flag=false;
			}
			if(flag)
			{
				//cout<<ans<<endl;
				printf("Case %d: %d\n",k,i);
				break;
			}
		}
	}
	return 0;
}
