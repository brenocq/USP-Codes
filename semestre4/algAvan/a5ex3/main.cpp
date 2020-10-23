#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

float solve(float a=0, float b=1);
float f(float x);
int p,q,r,s,t,u;


int main()
{
	while(scanf("%d %d %d %d %d %d", &p, &q, &r, &s, &t, &u) != EOF)
	{
		// Find a and b where f(a)>0 and fb(b)<0
		float a=-1, b=-1;
		for(float x=0; x<=1 ;x+=0.01)
		{
			float temp = f(x);
			if(temp>=0) a = x;
			if(temp<=0) b = x;
		}
		// Check 1 (float error)
		float temp = f(1);
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

float f(float x)
{
	return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}

float solve(float a, float b)
{
	float mid = (a+b)/2;
	float resMid = f(mid);
	float resA = f(a);
	float resB = f(b);

	// Number rounding problem, increased precision to fix
	if(abs(resA-resB)<0.000011)
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
