#include<bits/stdc++.h>
using namespace std;
namespace num_lib {

	double f(double x) {
		double ret;
		ret=(x-4)*(x-4)*(x+2);
		return ret;
	}

	double df(double x) {
		double ret;
		ret=3*(x-4)*x;
		return ret;
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
					printf("%d %lf %lf %lf %lf\n",flag+1,xl,xh,xm,tol*100.00);
					return xm;
				}
			}
			
			flag++;
			printf("%d %lf %lf %lf %lf\n",flag,xl,xh,xm,tol*100.00);
			if(f(xl)*f(xm)<0.000) {
				xh=xm;
			}
			else {
				xl=xm;
			}
			prev=xm;
		}
	}
	double newton(double mtol,double x)
	{
		int it=1;double px;
		while(true)
		{
			if(it<=1)
			{
				//cout<<it<<" "<<x<<" "<<f(x)<<" "<<df(x)<<" "<<0.0000<<endl;
				printf("%d %lf %lf %lf %lf\n",it,x,f(x),df(x),0.0000);
				if(f(x)==0.00) return x;
				px=x;
			}
			else
			{
				x=px-(f(px)/df(px));
				double tol=fabs(px-x)/fabs(x);
				tol*=100;
				printf("%d %lf %lf %lf %lf\n",it,x,f(x),df(x),tol);
				if(f(x)==0.00) return x;
				if(tol<=mtol) return x;
				if(it>=8) return x;
				px=x;
			}
			
			
			it++;
		}
	}
	double secant(double mtol,double x0,double x1)
	{
		double x2;
		int it=1;
		while(true)
		{
			x2=x1-((f(x1)*(x1-x0))/(f(x1)-f(x0)));
			if(it<=1)
			{
				printf("%d %lf lf %lf %lf %lf\n",it,x0,x1,x2,f(x2),0.0000);
			}
			else
			{
				double tol=fabs(x2-x1)/fabs(x2);
				tol*=100;
				printf("%d %lf lf %lf %lf %lf\n",it,x0,x1,x2,f(x2),tol);
				if(mtol>=tol) return x2;
			}
			if(f(x2)==0.00) return x2;
			x0=x1;
			x1=x2;
			it++;
		}
	}
}
using namespace num_lib;
int main()
{
	cout<<froot(0.0003,-2.5,-1.0)<<endl;
	cout<<newton(0.0002,-2.3)<<endl;
	cout<<secant(0.1,2.5,-1.0)<<endl;
}
