#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

int solve(int n, int sum);
std::vector<int> weights;
std::vector<int> memo;

int main()
{
	int n;
	std::string line;
	std::cin >> n;

	getline(std::cin, line);
	while(n--)
	{
		weights.clear();
		memo.clear();

		getline(std::cin, line);
		std::istringstream is(line);
		weights = std::vector<int>(std::istream_iterator<int>(is),std::istream_iterator<int>());

		memo.resize(weights.size()*400);
		for(auto& val : memo)
			val = 200;// Init with impossible value

		//for(auto& val : weights)
		//	printf("%d ", val);

		int result = solve(0,0);
		if(result==0)
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}

int solve(int n, int sum)
{
	if(n==(int)weights.size())
		return sum;
	if(memo[n*400+(sum+200)]!=200)
		return memo[n*400+(sum+200)];

	int toFst = solve(n+1, sum+weights[n]);
	int toSec = solve(n+1, sum-weights[n]);

	if(abs(toFst)<abs(toSec))
	{
		memo[n*400+(sum+200)]=toFst;
		return toFst;
	}
	else
	{
		memo[n*400+(sum+200)]=toSec;
		return toSec;
	}
}
