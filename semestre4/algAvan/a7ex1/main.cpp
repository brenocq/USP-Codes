#include <iostream>
#include <vector>
#define MAX_VAL 100000

using namespace std;

vector<int> coins;
int valueToFinish[MAX_VAL];

int solve(int value);

int main()
{
	int t;
	scanf("%d", &t);
	while(t-->0)
	{
		// Get value and qty of coins
		int v, n;
		scanf("%d", &v);
		scanf("%d", &n);

		// Reset to new problem
		coins.clear();
		for(int i=0;i<MAX_VAL;i++)
			valueToFinish[i] = -1;
		
		// Read coins
		while(n-->0)
		{
			int temp;
			scanf("%d", &temp);
			coins.push_back(temp);
		}

		// Solve
		int res = solve(v);
		if(res == MAX_VAL)
			printf("sem solucao\n");
		else
			printf("%d\n", res);
	}

	return 0;
}

int solve(int value)
{
	// Base case
	if(value==0)
		return 0;
	if(valueToFinish[value]!=-1)
		return valueToFinish[value];

	// Get best solution to (value-coin)
	int minimumQty = MAX_VAL;
	for(int i=0; i<(int)coins.size(); i++)
	{
		int temp = MAX_VAL;
		if(value-coins[i]>=0)
			temp = solve(value-coins[i]);
		if(temp<minimumQty)
			minimumQty = temp;
	}

	valueToFinish[value]=1+minimumQty;
	//printf("Minimum with [%d]: %d\n", value, valueToFinish[value]);
	return valueToFinish[value];
}

