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
FILE *fpw,*fpr,*fpw1;

int n;
int flag;
double e=2.71;
int osf;
double f(double x)
{
	
	double ret=pow(e,x)-5*x*x;
	return ret;
}
double bisection(double a,double b,double tol) {
	flag=true;
	if (f(a)*f(b)>=0) {
		cout << "You have not assumed right a and b\n";
		flag=false;
		return 0;
	}
	int tf=0;
	double c,pc;int it=1;
	while(true) {
		c=(a+b)/2;
		//fprintf(fpw, "%.8lf,%.8lf\n",c,f(c));
		if(tf) {
			double ftol=fabs(pc-c);
			if(ftol<0) {
				ftol*=(-1.00);
			}
			ftol/=fabs(c);
			fprintf(fpw, "%d,%.8lf\n",it,ftol);
			if(ftol<=tol) {
				return c;
			}
		}
		else
		{
			fprintf(fpw, "%d,0.00\n",it);
		}
		if (f(c) == 0.0)
		{
			return c;
		}

		else if (f(c)*f(a)<0.000)
			b=c;
		else
			a=c;
			
			

		
		tf=1;
		pc=c;
		it++;
	}
}
int main() {
	fpw1 = fopen("output311(10).txt", "w+");
	for(double i=-1;i<=1;i+=0.1)
	{
		cout<<"x: "<<i<<" f(x): "<<f(i)<<endl;
		fprintf(fpw1, "%.8lf,%.8lf\n",i,f(i));
	}
	fpw = fopen("output312(10).txt", "w+");
	double a=-5000,b=5000,prec=.0000055;
	cin>>a>>b>>prec;
	double ret=bisection(a,b,prec);
	cout<<"Root : "<<ret<<endl;
	printf("Approximate value : %.8lf\n",f(ret));
	return 0;
}


