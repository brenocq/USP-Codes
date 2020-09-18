#include <vector>
#include <stdio.h>

using namespace std;

int n;	
vector<vector<int>> world;

int qtyPaths(int row, int col)
{
	int count = 0;
	if(row>=n || row<0 || col>=n || col<0)
		return 0;
	if(world[row][col]!=0)
		return 0;
	if(row==n-1 && col==n-1)
		return 1;

	world[row][col]=1;
	count+=qtyPaths(row+1, col);
	count+=qtyPaths(row, col+1);
	count+=qtyPaths(row-1, col);
	count+=qtyPaths(row, col-1);
	world[row][col]=0;

	return count;
}

int main()
{
	scanf("%d\n", &n);
	for(int i=0; i<n; i++)
	{
		world.push_back({});
		for(int j=0; j<n; j++)
		{
			int temp;
			scanf("%d", &temp);
			world.back().push_back(temp);
		}
	}

	int count = qtyPaths(0,0);
	printf("%d\n", count);

	return 0;
}
