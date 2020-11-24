#include <iostream>
#include <vector>
#include <algorithm>

struct Doll{
	int w;
	int h;

	bool operator<(const Doll& a) const
	{
		if(w==a.w)
			return h>a.h;
		return (w < a.w);
	}	
};

std::vector<Doll> dolls;
int solve();

int main()
{
	int n;
	std::cin >> n;

	while(n--)
	{
		int qtyDolls;
		std::cin >> qtyDolls;
		dolls.resize(qtyDolls);
		for(int i=0;i<qtyDolls;i++)
		{
			int w,h;
			std::cin >> w >> h;
			dolls[i].w = w;
			dolls[i].h = h;
		}

		std::sort(dolls.begin(), dolls.end());
		std::cout << solve() << std::endl;
	}

	return 0;
}

int solve()
{
	int size = dolls.size();
	std::vector<int> lis(size);

	lis[0] = 1;
	for(int i=1; i<size; i++)
	{
		lis[i] = 1;
		for(int j=0; j<i; j++)
		{
			if((dolls[i].w<=dolls[j].w || dolls[i].h<=dolls[j].h) && 
					lis[i] <= lis[j]+1)
			{
				lis[i] = lis[j]+1;
			}
		}
	}

	int maxLis = 0;
	for(int i=0; i<size; i++)
		if(lis[i]>=maxLis)
			maxLis = lis[i];
	return maxLis;
}
