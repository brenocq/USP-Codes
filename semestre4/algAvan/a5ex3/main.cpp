#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double solve(double a=0, double b=1);
double f(double x);
int p,q,r,s,t,u;


int main()
{
	while(scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) != EOF)
	{
		// Find a and b where f(a)>0 and fb(b)<0
		double a=-1, b=-1;
		for(double x=0; x<=1 ;x+=0.01)
		{
			double temp = f(x);
			if(temp>=0) a = x;
			if(temp<=0) b = x;
		}
		// Check 1 (double error)
		double temp = f(1);
		if(temp>=0) a = 1;
		if(temp<=0) b = 1;

		// Print impossible or solve
		if(a<0 || b<0)// Impossible
			printf("No solution\n");
		else // Solve
			printf("%.4f\n", solve(a,b));
	}

	return 0;
}

double f(double x)
{
	return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}

double solve(double a, double b)
{
	double mid = (a+b)/2;
	double resMid = f(mid);
	double resA = f(a);
	double resB = f(b);

	// Number rounding problem, increased precision to fix
	if(abs(resA-resB)<0.00000011)
		return mid;

	if(resMid<0)
	{
		return solve(a, mid);
	}
	else
	{
		return solve(mid, b);
	}
}
