#include <iostream>
#include <vector>

using namespace std;

vector<int> coins;

int getWithdraw(int index=-1, int value=0, int lastPontuation=0);

int main()
{
	int t;
	scanf("%d\n", &t);
	while(t-->0)
	{
		int n;
		scanf("%d\n", &n);
		coins.clear();
		while(n-->0)
		{
			int temp;
			scanf("%d\n", &temp);
			coins.push_back(temp);
		}

		printf("%d\n", getWithdraw());
	}

	return 0;
}

int getPoint(int value)
{
	int differentCoins = 0;
	int remain = value;
	//printf("---------------\n");
	for(int i=coins.size()-1; i>=0; i--)
	{
		if(remain/coins[i]==1)
		{
			//printf("%d*%d\n", int(remain/coins[i]), coins[i]);
			remain-=int(remain/coins[i])*coins[i];
			differentCoins++;
		}
		else if(remain/coins[i]>1)
			return -1;
	}
	//printf("---------------\n");
	return differentCoins;
}


int getWithdraw(int index, int value, int lastPontuation)
{
	if(index == -1)
		index = coins.size()-1;

	int maxPoints = lastPontuation;
	for(int i=index; i>=0; i--)
	{
		int currAmount = value+coins[i];
		int result = getPoint(currAmount);
		if(result>=maxPoints)
		{
			//printf("Amount: %d+%d, points: %d\n", value, coins[i], result);
			maxPoints = result;
			if(i-1>=0)
				maxPoints = getWithdraw(i-1, currAmount, result);
		}
	}
	return maxPoints;
}
