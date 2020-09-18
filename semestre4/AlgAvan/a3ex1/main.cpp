#include <vector>
#include <stdio.h>

std::vector<int> songs;
int N;

std::pair<std::vector<int>, int> solve(int i, std::vector<int> current, int sum);

int main()
{
	while(scanf("%d", &N)>0)
	{
		songs.clear();
		int qtyTracks;
		scanf("%d", &qtyTracks);
		while(qtyTracks-->0)
		{
			int temp;
			scanf("%d", &temp);
			songs.push_back(temp);
		}

		auto solution = solve(0, {}, 0);

		for(auto song : solution.first)
		{
			printf("%d ", song);
		}
		printf("sum:%d\n", solution.second);
	}

	return 0;
}

std::pair<std::vector<int>, int> solve(int i, std::vector<int> current, int sum)
{
	std::pair<std::vector<int>, int> bestSol = make_pair(current,sum);
	for(int j=i;j<int(songs.size());j++)
	{
		int currSum = sum+songs[j];
		if(currSum<=N)
		{
			auto temp = current;
			temp.push_back(songs[j]);
			auto result = solve(j+1, temp, currSum);
			if(result.second>bestSol.second)
				bestSol = result;
		}
	}
	return bestSol;
}
