#include <vector>
#include <iostream>

std::vector<int> vec1;
std::vector<int> vec2;
int solve();

int main()
{
	int n;
	std::cin >> n;

	int c = 1;
	while(n--)
	{
		int qtyNumbers;
		std::cin >> qtyNumbers;

		// Populate vectors
		vec1.resize(qtyNumbers);
		vec2.resize(qtyNumbers);
		for(int i=0;i<qtyNumbers;i++)
		{
			int val;
			std::cin >> val;
			vec1[i] = val;
		}

		for(int i=0;i<qtyNumbers;i++)
		{
			int val;
			std::cin >> val;
			vec2[i] = val;
		}

		// Solve and print
		std::cout << "Case " << c++ << ": " << solve() << std::endl;
	}

	return 0;
}

int solve()
{
	int size = vec1.size();
    int memo[size+1][size+1];
 
    for (int i=0; i <= size; i++)
	{
        for (int j=0; j <= size; j++)
		{
            if (i == 0)// If empty, remove all from the other
                memo[i][j] = j;
            else if (j == 0)// If empty, remove all from the other
                memo[i][j] = i;
            else if (vec1[i-1] == vec2[j-1])// If last are same, ignore last integer
                memo[i][j] = memo[i-1][j-1];
            else// If last int is different, perform operations
                memo[i][j]= 1 + std::min(memo[i][j-1], memo[i-1][j]);// Insert or remove
        }
    }
 
    return memo[size][size];
}
