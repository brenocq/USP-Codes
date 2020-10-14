//----------------------
// Breno Cunha Queiroz
// aula4-exer1
//----------------------
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int readLock();
int calcMinPath(int current, int target);
int calcDistance(int val1, int val2);
int rotateLock(int current, int position, bool clockwise);

vector<bool> visited = vector<bool>(10000);
vector<int> forbidden;

int main()
{
	int n;
	scanf("%d", &n);

	while(n-->0)
	{
		forbidden.clear();

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

		int distance = calcMinPath(init, target);
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
	int powers[4] = {1, 10, 100, 1000};
	int result = current;
	int power = powers[position];
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
	// Distance between two configurations
	int result = 0;
	for(int i=0;i<4;i++)
	{
		int powers[4] = {1, 10, 100, 1000};
		int power = powers[i];
		int curr1 = (val1/power)%10;
		int curr2 = (val2/power)%10;
		int res = abs(curr1-curr2);
		
		result += res>5?10-res:res;
	}
	return result;
}

int IDA(int current, int target, int depth, int realDepth, int limit) {
	if(current == target)
		return realDepth;
	if(depth>=limit)
		return -1;

	// Check if not visited before
	if(visited[current]==false)
		visited[current]=true;
	else
		return -1;

	for(int i=0;i<8;i++)	
	{
		// Test each of the 8 possibilities
		int rotated = rotateLock(current, i<4?i:i-4, i<4);
		int distanceToTarget = calcDistance(rotated, target);

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

		int res = IDA(rotated, target, realDepth+1+distanceToTarget, realDepth+1, limit);
		if(res != -1)
			return res;
	}

	return -1;
}

int calcMinPath(int current, int target)
{
	int maxDepth = 0;
	while(true)
	{
		// Reset visited
		visited = vector<bool>(10000);
		// Increase max depth
		maxDepth++;
		// Call IDA
		int res = IDA(current, target, 0, 0, maxDepth);
		if(res!=-1)
			return res;
	}
}
