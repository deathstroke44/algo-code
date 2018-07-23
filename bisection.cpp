#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <list>
#include <map>
#include <queue>
#include <sstream>
#include <utility>
#define maxn 1005
using namespace std;
int n;
double co[maxn];
int flag;
double f(double x) {
	double v=1,ans=0;
	for(int i=0; i<=n; i++) {
		ans+=v*co[i];
		v*=x;
	}
	return ans;
}
double bisection(double a,double b,double tol) {
	flag=true;
	if (f(a)*f(b)>=0) {
		cout << "You have not assumed right a and b\n";
		flag=false;
		return 0;
	}
	int tf=0;
	double c,pc;
	while(true) {
		c=(a+b)/2;
		if (f(c) == 0.0)
			break;

		else if (f(c)*f(a)<0.000)
			b=c;
		else
			a=c;

		if(tf) {
			double ftol=fabs(pc-c);
			if(ftol<0) {
				ftol*=(-1.00);
			}
			ftol/=fabs(c);
			if(ftol<=tol) {
				return c;
			}
		}
		tf=1;
		pc=c;
	}
}
int main() {
    FILE *fpw,*fpr;
    fpr = fopen("input.txt", "r+");
    fpw = fopen("output.txt", "w+");
	double a=-5000,b=5000;
	fscanf(fpr, "%d", &n);
	cout<<n<<endl;
	for(int i=n; i>=0; i--) {
		fscanf(fpr, "%lf", &co[i]);
		cout<<co[i]<<" ";
	}
	puts("");
	double ret=bisection(a,b,0.0000005);
	cout<<"Root : "<<ret<<endl;
	printf("Approximate value : %.8lf\n",f(ret));
	fprintf(fpw, "Root : %.8lf \nApproximate value : %.8lf\n",ret,f(ret));
	return 0;
}
