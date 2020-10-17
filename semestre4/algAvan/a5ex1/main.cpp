#include <iostream>
#include <vector>

using namespace std;

int sortAndCount(vector<int> &values, int l, int r);
int mergeAndCount(vector<int> &values, int l, int m, int r);

int main()
{
	int N;
	scanf("%d", &N);
	while(N-->0)
	{
		vector<int> values;

		int size;
		scanf("%d", &size);

		while(size-->0)
		{
			int val;
			scanf("%d", &val);
			values.push_back(val);
		}

		int inversions = sortAndCount(values, 0, values.size()-1);
		printf("%d\n", inversions);
	}

	return 0;
}

int sortAndCount(vector<int> &values, int l, int r)
{
	int qtyInversions = 0;
	if(l<r)
	{
		int m = l + (r-l)/2;
		qtyInversions += sortAndCount(values, l, m);
		qtyInversions += sortAndCount(values, m+1, r);
		qtyInversions += mergeAndCount(values, l, m, r);
	}
	return qtyInversions;
}

int mergeAndCount(vector<int> &values, int l, int m, int r)
{
	int countInversins = 0;

 	int n1 = m - l + 1; 
    int n2 = r - m; 

	// Temp vectors
	vector<int> L(n1);
	vector<int> R(n2);

	for(int i = 0; i < n1; i++)
        L[i] = values[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = values[m + 1 + j];

	// Index vector L
    int i = 0;
    // Index vector R
    int j = 0;
    // Index merged vector
    int k = l;

	// Merge two vectors to merged vector
	while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            values[k] = L[i];
            i++;
        }
        else
        {
			// Count number of inversions
			countInversins+=n1-i;
            values[k] = R[j];
            j++;
        }
        k++;
    }

	// Copy the remaining elements of 
    // L, if there are any  
    while (i < n1)  
    { 
        values[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    // Copy the remaining elements of 
    // R, if there are any  
    while (j < n2) 
    { 
        values[k] = R[j]; 
        j++; 
        k++; 
    } 

	return countInversins;
}
