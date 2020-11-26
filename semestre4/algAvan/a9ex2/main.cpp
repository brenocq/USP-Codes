#include <vector>
#include <iostream>

std::string str1;
std::string str2;
int solve();

int main()
{
	std::cin >> str1;
	std::cin >> str2;

	// Solve and print
	std::cout << solve() << std::endl;

	return 0;
}

int solve()
{
	int s1 = str1.size();
	int s2 = str2.size();
    int memo[s1+1][s2+1];
 
    for(int i=0; i <= s1; i++)
	{
        for(int j=0; j <= s2; j++)
		{
            if(i == 0)// If empty, remove all from the other
			{
				int sum=0;
				for(int s=0; s<j; s++)
					sum+=str2[s]-'a'+1;
                memo[i][j] = sum;
			}
            else if(j == 0)// If empty, remove all from the other
			{
				int sum=0;
				for(int s=0; s<i; s++)
					sum+=int(str1[s]-'a'+1);
                memo[i][j] = sum;
			}
            else if(str1[i-1] == str2[j-1])// If last are same, ignore last integer
                memo[i][j] = memo[i-1][j-1];
            else// If last int is different, perform operations
			{
				int sub = memo[i-1][j-1] + std::abs(int(str1[i-1])-int(str2[j-1]));
				int add = memo[i][j-1] + int(str2[j-1]-'a'+1);
				int rem = memo[i-1][j] + int(str1[i-1]-'a'+1);
                memo[i][j] = std::min(std::min(add, rem), sub);// Insert, remove, or replace
			}
        }
    }
 
    return memo[s1][s2];
}
