#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int readLock();
int calcMinPath(int current, int target, int depth=0);
int rotateLock(int current, int position, bool clockwise);

vector<int> forbidden;
vector<bool> values;

int main()
{
	int n;
	scanf("%d", &n);

	while(n-->0)
	{
		forbidden.clear();
 		values = vector<int>(10000);
		// Read init config
		int init = readLock();

		// Read target config
		int target = readLock();

		// Read forbidden configs
		int qtyForb;
		scanf("%d", &qtyForb);
		for(int i=0;i<qtyForb;i++)
		{
			values[readLock()] = true;
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

int calcMinPath(int current, int target, int depth)
{
	if(current == target)
		return depth;
	values[current]=true;
	for(int i=0;i<8;i++)	
	{
		vector<int> responses;
		int rotated = rotateLock(curr[1], i<4?i:i-4, i<4);
		if(!values[rotated])
			responses.push_back(calcMinPath(rotated, target, depth+1));

		int minimum = 99999;
		for(int val : responses)
			if(val!=-1 && val<minimum)
				minimum=val;
	}
	values[current]=false;
	return maximum;
}
