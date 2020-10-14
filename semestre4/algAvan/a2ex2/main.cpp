#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <numeric>

using namespace std;

bool increasing(int a, int b)
{
	return a>b;
}

int main()
{
	int c, s;
	int count=0;
	while(scanf("%d\n", &c) > 0)
	{
		
		vector<int> specimens;
		scanf("%d\n", &s);

		// Get data
		while(s-->0)
		{
			int val;
			scanf("%d\n", &val);
			specimens.push_back(val);
		}

		// Calculate average
		float avg = 0;
		float imbalance=0;
		for(auto value:specimens)avg+=value;
		avg/=float(c);

		// Organize data
		while(int(specimens.size())<c*2)
			specimens.push_back(0);

		sort(specimens.begin(), specimens.end());

		// Print
		printf("Set #%d\n", ++count);
		for(int i=0; i<c; i++)
		{
			printf(" %d:", i);

			int totalMass=0;

			if(specimens[i])
			{
				printf(" %d", specimens[i]);
				totalMass += specimens[i];
			}
			if(specimens[(c*2-1)-i])
			{
				printf(" %d", specimens[(c*2-1)-i]);
				totalMass += specimens[(c*2-1)-i];
			}
			imbalance+=abs(totalMass-avg);
			printf("\n");
		}
		printf("IMBALANCE = %.5f\n\n", imbalance);
	}

	return 0;
}
