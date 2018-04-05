#include<bits/stdc++.h>
using namespace std;
#define MAXC 1000
char A[MAXC],B[MAXC];
int lenA,lenB;
int dp[MAXC][MAXC];
string dp1[110][110];
bool visited[MAXC][MAXC];
map<string,bool> mp;
string ans;
void printLCS(int i,int j)
{
    if(A[i]=='\0' or B[j]=='\0'){
        cout<<ans<<endl;
        return;
    }
    if(A[i]==B[j]){
        ans+=A[i];
        printLCS(i+1,j+1);
    }
    else
    {
        if(dp[i+1][j]>dp[i][j+1]) printLCS(i+1,j);
        else printLCS(i,j+1);
    }
}
string lexo(int i,int j)
{
	if(A[i]=='\0' or B[j]=='\0') return "";
	if(visited[i][j])return dp1[i][j];

	string ans="";
	if(A[i]==B[j]) ans=ans+A[i]+lexo(i+1,j+1);
	else
	{
		string val1=lexo(i+1,j);
		string val2=lexo(i,j+1);
		if(val1.size()==val2.size()) ans+=min(val1,val2);
		else if(val1.size()>val2.size()) ans+=val1;
		else ans+=val2; 
	}
	visited[i][j]=1;
	dp1[i][j]=ans;
	return dp1[i][j];
}
void printAll(int i,int j)
{
	if(A[i]=='\0' or B[j]=='\0'){
		if(!mp[ans])cout<<ans<<endl;
		mp[ans]=true;
		return;
	}
	if(A[i]==B[j]){
		ans+=A[i];
		printAll(i+1,j+1);
		ans.erase(ans.end()-1); //Delete last character
	}
	else
	{
		if(dp[i+1][j]>dp[i][j+1]) printAll(i+1,j);
		else if(dp[i+1][j]<dp[i][j+1]) printAll(i,j+1);
		else
		{
			printAll(i+1,j);
			printAll(i,j+1);
		}
	}
}
int calcLCS(int i,int j)
{	
	if(A[i]=='\0' or B[j]=='\0') return 0;
	if(visited[i][j])return dp[i][j];

	int ans=0;
	if(A[i]==B[j]) ans=1+calcLCS(i+1,j+1);
	else
	{
		int val1=calcLCS(i+1,j);
		int val2=calcLCS(i,j+1);
		ans=max(val1,val2);
	}
	visited[i][j]=1;
	dp[i][j]=ans;
	return dp[i][j];
}
int main() {
	scanf("%s%s",A,B);
	lenA=strlen(A);
	lenB=strlen(B);
	//printf("%d\n",calcLCS(0,0));
	cout<<lexo(0,0)<<endl;
	//printLCS(0,0);
	return 0;
}
