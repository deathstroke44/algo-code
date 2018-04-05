#include<bits/stdc++.h>
using namespace std;
void computeLPSArray(char *pat, int M, int *lps);
int KMPSearch(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];
    computeLPSArray(pat, M, lps);
 
    int i = 0;  
    int j  = 0; 
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
 		if (j == M)
        {
            return 1;
            j = lps[j-1];
        }
 		else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    return 0;
}
int KMPcount(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int counter=0;
    int lps[M];
 	computeLPSArray(pat, M, lps);
	int i = 0;  // index for txt[]
    int j  = 0;  // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
 
        if (j == M)
        {
            counter++;
            j = lps[j-1];
        }
 		else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    return counter;
}
void computeLPSArray(char *pat, int M, int *lps)
{
    int len = 0;
 	lps[0] = 0; 
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
            {
                len = lps[len-1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
        cout<<i-1<<" "<<lps[i-1]<<endl;
    }
}
 

int main()
{
    char txt[100];
    char pat[100];
    
 	cin>>pat;
 	int lps[strlen(pat)];
	int i=0,j=strlen(pat)-1;
 	while(i<j)
 	{
 		swap(pat[i],pat[j]);
		i++;j--;	
	}
	cout<<pat<<endl;
	computeLPSArray(pat, strlen(pat), lps);
    
	//cin>>txt>>pat;
    //cout<<KMPSearch(pat, txt)<<endl;
    //cout<<KMPcount(pat, txt)<<endl;
	return 0;
}
