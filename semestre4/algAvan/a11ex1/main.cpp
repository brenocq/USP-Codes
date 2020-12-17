#include <iostream>
#include <vector>

std::vector<int> primes;
void findPrimes(int max);
std::vector<int> findFactors(int number);

int main()
{
	findPrimes(100);// Primes until 100 inclusive

	int number;
	std::cin >> number;

	while(number!=0)
	{
		printf("%3d", number);
		std::cout << "! =";

		// Calculate factors
		std::vector<int> result = findFactors(number);

		// Print factors
		for(unsigned i=0; i<result.size(); i++)
		{
			if(result[i]==0)
				break;
			if(i>0 && i%15==0)
				std::cout << "\n      ";

			printf("%3d", result[i]);
		}
		std::cout << std::endl;

		// Read next number
		std::cin >> number;
	}
	

	return 0;
}

void findPrimes(int max)
{
	std::vector<bool> numbers(max+1);// false->check, true->not check

	for(int i=2; i<=max; i++)
	{
		if(!numbers[i])
		{
			primes.push_back(i);
			for(int j=i; j<=max; j+=i)
				numbers[j]=true;
		}
	}
}

std::vector<int> findFactors(int number)
{
	// Factors of number!
	std::vector<int> result(primes.size());
	
	// For each prime p...
	for(unsigned i=0; i<primes.size(); i++)
	{
		// For each p^x<number
		for(unsigned j=primes[i]; j<=(unsigned)number;j*=primes[i])
		{
			result[i]+=number/j;
		}
	}
	return result;
}
