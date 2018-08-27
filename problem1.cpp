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
FILE *fpw1,*fpw2,*fpw3;

int n;
int flag;
double e=2.71;
int osf;
double f(double x)
{
	double b=x+3;
	double ac=(3*x)+(x*x)/2.00;
	double ret=1.00-((400.00*b)/(9.81*ac*ac*ac));
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
			
			fprintf(fpw1, "%lf,%.8lf\n",c,ftol);
			fprintf(fpw2, "%d,%.8lf\n",it,ftol);
			if(ftol<=tol) {
				return c;
			}
		}
		else
		{
			fprintf(fpw2, "%d,0.00\n",it);
			fprintf(fpw1, "%lf,0.00\n",c);
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
double froot(double mtol,double xl,double xh) {
	int flag=0;
	double prev;
	while(true) {
		double up=xh*f(xl)-xl*f(xh);
		double down=f(xl)-f(xh);
		double xm=up/down;
		
		double tol=0;
		if(f(xm)==0) {
			return xm;
		} 
		if(flag) {
			tol=fabs(xm-prev)/fabs(xm);
			if(mtol>=tol) {
				//printf("%d %lf %lf %lf %lf\n",flag+1,xl,xh,xm,tol*100.00);
				return xm;
			}
		}
		
		flag++;
		//printf("%d %lf %lf %lf %lf\n",flag,xl,xh,xm,tol*100.00);
		if(f(xl)*f(xm)<0.000) {
			xh=xm;
		}
		else {
			xl=xm;
		}
		prev=xm;
	}
}
int main() {
	fpw1 = fopen("outputp1g1.txt", "w+");
	fpw2 = fopen("outputp1g2.txt", "w+");
	double a=0.5,b=2.5,prec=.000000055;
	double ret=bisection(a,b,prec);
	cout<<"Root : "<<ret<<endl;
	printf("Approximate value : %.8lf\n",f(ret));
	cout<<"Root: "<<froot(prec,a,b)<<endl;
	
	printf("Approximate value : %.8lf\n",f(ret));
	return 0;
}



