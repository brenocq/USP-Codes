#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

double montecarlo(unsigned samples, double a, double b, double* res, double* stdEst);

#define NUM_TESTS 6

typedef struct _test
{
	double a;
	double b;
	unsigned samples;
} Test;

int main()
{
	srand(3141);

	printf("--------------------------------------------------------\n");
	printf("Problema: Resolver integral de arcsin(x*x) com Monte Carlo\n");
	printf("--------------------------------------------------------\n");
	printf("Solução:\n");

	Test tests[NUM_TESTS];
	tests[0].a = -1;
	tests[0].b = 1;
	tests[0].samples = 10;

	tests[1].a = -1;
	tests[1].b = 1;
	tests[1].samples = 100;

	tests[2].a = -1;
	tests[2].b = 1;
	tests[2].samples = 1000;

	tests[3].a = 0;
	tests[3].b = 1;
	tests[3].samples = 1000;

	tests[4].a = 0;
	tests[4].b = .5;
	tests[4].samples = 1000;

	tests[5].a = .5;
	tests[5].b = 1;
	tests[5].samples = 1000;

	for(size_t i=0;i<NUM_TESTS;i++)
	{
		printf("Resolvendo em [%f,%f] com %d amostras\n", tests[i].a, tests[i].b, tests[i].samples);
		double res, stdEst;
		montecarlo(tests[i].samples, tests[i].a, tests[i].b, &res, &stdEst);
		printf("Resultado: %lf (erro do estimador: %lf)\n\n", res, stdEst);
	}
	return 0;
}

double montecarlo(unsigned samples, double a, double b, double* res, double* stdEst)
{
	// E[f(x)] = (b-a)/n * SUM_0^n(f(x_i))
	double sum = 0;
	double* xi = (double*)malloc(samples*sizeof(double));
	for(size_t i=0;i<samples;i++)
	{
		// Generate random between a and b
		double random = (((rand()%2000000)/2000000.0f)*(b-a))+a;
		// Sum result
		xi[i] = asinf(random*random);
		sum += xi[i];
	}
	// Calculating sample standard deviation
	{
		double mean = sum/samples;
		double squaredDiffSum = 0;
		for(size_t i=0;i<samples;i++)
		{
			double a = (xi[i]-mean);
			squaredDiffSum += a*a;
		}
		double sampleVariance = squaredDiffSum/(samples-1);
		*stdEst = sqrt(sampleVariance/samples);
	}
	free(xi);

	*res = ((b-a)/samples)*sum;
}
