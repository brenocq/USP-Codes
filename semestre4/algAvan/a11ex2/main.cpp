#include <iostream>
#include <vector>

struct Factor {
    int prime, count;
};
std::vector<unsigned int> primes;

void findPrimes(unsigned int max);
std::vector<Factor> findFactors(unsigned int number);
int findPowerFactorial(int number, int prime);
bool dividesFactorial(int fac, int num);

int main()
{
	findPrimes(unsigned(50000));

	unsigned int a, b;
	// a -> number
	// b -> factorial

	while(scanf("%u %u", &b, &a)>0)
	{
		if(dividesFactorial(b, a))
			printf("%d divides %d!\n", a, b);
		else
			printf("%d does not divide %d!\n", a, b);
	}
	

	return 0;
}

void findPrimes(unsigned int max)
{
	std::vector<bool> numbers(max+1);// false->check, true->not check

	for(unsigned int i=2; i<=max; i++)
	{
		if(!numbers[i])
		{
			primes.push_back(i);
			for(unsigned int j=i; j<=max; j+=i)
				numbers[j]=true;
		}
	}
}

bool dividesFactorial(int fac, int num)
{
	if(num==0)// Division by zero
		return false;
	else if(fac>=num)// Fac contains num
		return true;
	else
	{
		std::vector<Factor> numberFactors = findFactors(num);

		if(numberFactors.size()>0 && 
				numberFactors.back().prime > fac)// If prime greater than fac
			return false;

		for(auto factor : numberFactors)
		{
			if(factor.count-findPowerFactorial(fac, factor.prime)>0)
				return false;
		}


		return true;
	}
}

int findPowerFactorial(int number, int prime)
{
	int result=0;
	// For each p^x<number
	for(int j=prime; j<=number;j*=prime)
	{
		result+=number/j;
	}
	return result;
}

std::vector<Factor> findFactors(unsigned int number)
{
	// Returns vector of primes and counts
	
	// Factors of number
	std::vector<Factor> result;

	if(number == 0)
		return result;

	for(unsigned int i=0; i<primes.size(); i++)
	{
		Factor factor = {(int)primes[i], 0};
		while(number%primes[i] == 0)
		{
			number/=primes[i];
			factor.count++;
		}
		if(factor.count>0)
			result.push_back(factor);
	}

	// Check if number is prime
	if(number>1)
	{
		result.push_back((Factor){(int)number, 1});
	}

	return result;
}
