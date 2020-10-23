#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

vector<int> ladies;
int findClosestLady(int height, int start=0, int end=ladies.size());

int main()
{
	int N; cin >> N;
	// Read ladies height
	while(N--)
	{
		int temp;
		cin >> temp;
		ladies.push_back(temp);
	}

	int Q; cin >> Q;
	// Read queries and print answer
	while(Q--)
	{
		// Get height and calculate position
		int height; cin >> height;
		int res = findClosestLady(height);
		int shortLady = -1;
		int tallLady = -1;

		// Find short lady
		for(int i=res; i>=0;i--)	
			if(ladies[i]<height)
			{
				shortLady = ladies[i];
				break;
			}

		// Find tall lady
		for(int i=res; i<int(ladies.size());i++)	
			if(ladies[i]>height)
			{
				tallLady = ladies[i];
				break;
			}

		if(shortLady!=-1)
			printf("%d ", shortLady);
		else 
			printf("X ");

		if(tallLady!=-1)
			printf("%d\n", tallLady);
		else 
			printf("X\n");
	}

	return 0;
}

int findClosestLady(int height, int start, int end)
{
	// Binary like search
	int mid=(start+end)/2;

	if(end-start==1)
		return start;

	if(ladies[mid]>=height)
		return findClosestLady(height, start, mid);
	else
		return findClosestLady(height, mid, end);
}
