#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int readLock();
int calcMinPath(int current, int target, vector<int> forbidden);
int calcDistance(int val1, int val2);
int rotateLock(int current, int position, bool clockwise);

int main()
{
	int n;
	scanf("%d", &n);

	while(n-->0)
	{
		vector<int> forbidden;

		// Read init config
		int init = readLock();

		// Read target config
		int target = readLock();

		// Read forbidden configs
		int qtyForb;
		scanf("%d", &qtyForb);
		for(int i=0;i<qtyForb;i++)
		{
			forbidden.push_back(readLock());
		}

		int distance = calcMinPath(init, target, forbidden);
		printf("%d\n", distance);
	}

	return 0;
}

int readLock()
{
	int result = 0;
	int aux;
	scanf("%d", &aux);
	result += aux*1000;
	scanf("%d", &aux);
	result += aux*100;
	scanf("%d", &aux);
	result += aux*10;
	scanf("%d", &aux);
	result += aux;

	return result;
}

int rotateLock(int current, int position, bool clockwise)
{
	int result = current;
	int power = pow(10,position);
	int digit = (current/power)%10;
	result -= digit*power;
	// Rotate
	digit += clockwise?1:-1;
	digit = digit<0?10+digit:digit;
	result += (digit%10)*power;

	return result;
}

int calcDistance(int val1, int val2)
{
	int result = 0;
	for(int i=0;i<4;i++)
	{
		int power = pow(10,i);
		int curr1 = (val1/power)%10;
		int curr2 = (val2/power)%10;
		int res = abs(curr1-curr2);
		
		result += res>5?10-res:res;
	}
	return result;
}

int calcMinPath(int current, int target, vector<int> forbidden)
{
	priority_queue<vector<int> > options;

	int distance = calcDistance(current, target);
	vector<int> curr = {10000-distance, current, 0};
	vector<bool> searched = vector<bool>(10000);
	options.push(curr);

	//printf("start = %d ------------ target = %d\n", current, target);
	while(options.size()!=0)
	{
		curr = options.top();
		options.pop();

		if(searched[curr[1]]==false)
			searched[curr[1]]=true;
		else
			continue;

		if(curr[1] == target)
			return curr[2];

		// Add possible next paths
		for(int i=0;i<8;i++)	
		{
			int rotated = rotateLock(curr[1], i<4?i:i-4, i<4);
			int distanceToTarget = calcDistance(rotated, target);
			int distanceFromInit = curr[2]+1;

			// Check if it is accessible
			bool canAdd = true;
			for(auto forb : forbidden)
				if(forb==rotated)
				{
					canAdd = false;
					break;
				}
			if(!canAdd)
				continue;

			options.push({10000-(distanceToTarget+distanceFromInit), rotated, distanceFromInit});
		}


		//printf("----------- LIST BEGIN\n");
		//priority_queue<vector<int> > g = options;
		//while(!g.empty()) 
		//{ 
		//	printf(" %d->%d", g.top()[0], g.top()[1]);
		//	g.pop(); 
		//} 
		//cout << '\n'; 
		//printf("----------- LIST END\n");

		//printf("current = %d(%d)\n", curr[1], curr[0]);
	}
	return -1;
}
