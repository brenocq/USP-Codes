#include <iostream>
#include <vector>
#define DEBUG 0

using namespace std;

void readProblem(vector<vector<int>>& womenPreferences, vector<vector<int>>& menPreferences, vector<pair<int,int>>& weddings);
void solveProblem(vector<vector<int>>& womenPreferences, vector<vector<int>>& menPreferences, vector<pair<int,int>>& weddings);
bool checkVectorFull(vector<pair<int,int>> v);
int getFirstSingleMan(vector<pair<int,int>> weddings);
int getWomanHusband(int woman, vector<pair<int,int>> weddings);
bool womanPreferFirst(int m, int womanHusband, vector<int> preferences);
void printSolution(vector<pair<int,int>> weddings);

int main()
{
	vector<vector<int>> womenPreferences;
	vector<vector<int>> menPreferences;
	vector<pair<int, int>> weddings;

	int qtyProblems;
	scanf("%d\n", &qtyProblems);
	while(qtyProblems-->0)
	{
		readProblem(womenPreferences, menPreferences, weddings);
		solveProblem(womenPreferences, menPreferences, weddings);
		printSolution(weddings);
	}

	return 0;
}

void readProblem(vector<vector<int>>& womenPreferences, vector<vector<int>>& menPreferences, vector<pair<int,int>>& weddings)
{
	womenPreferences.clear();
	menPreferences.clear();
	weddings.clear();

	int n;
	scanf("%d\n", &n);

	// Women preferences
	for(int i=0; i<n; i++)
	{
		int val;
		scanf("%d\n", &val);
		weddings.push_back(make_pair(i+1, -1));

		womenPreferences.push_back({});
		for(int j=0; j<n; j++)
		{
			scanf("%d\n", &val);
			womenPreferences[i].push_back(val);
		}
	}

	// Men preferences
	for(int i=0; i<n; i++)
	{
		int val;
		scanf("%d\n", &val);

		menPreferences.push_back({});
		for(int j=0; j<n; j++)
		{
			scanf("%d\n", &val);
			menPreferences[i].push_back(val);
		}
	}
}

void solveProblem(vector<vector<int>>& womenPreferences, vector<vector<int>>& menPreferences, vector<pair<int,int>>& weddings)
{
	while(!checkVectorFull(weddings))
	{
		int m = getFirstSingleMan(weddings);
		// Test for each woman
		for(int i=0; i<(int)menPreferences[m-1].size(); i++)
		{
			int w = menPreferences[m-1][i];
			if(DEBUG)
				printf("%d trys to propose %d\n", m, w);
			int womanHusband = getWomanHusband(w, weddings);

			// Single
			if(womanHusband==0)
			{
				if(DEBUG)
					printf("%d single, (%d,%d) married!\n", w, m, w);
				weddings[m-1].second = w;
				break;
			}
			// Married
			else
			{
				if(womanPreferFirst(m, womanHusband, womenPreferences[w-1]))
				{
					if(DEBUG)
						printf("%d now loves %d, (%d,%d) married!\n", w, m, m, w);
					weddings[womanHusband-1].second = -1;
					weddings[m-1].second = w;
					break;
				}
			}
		}
	}
}

bool checkVectorFull(vector<pair<int,int>> v)
{
	for(auto i : v)	
	{
		if(i.first<1 || i.second<1)	
			return false;
	}
	return true;
}

int getFirstSingleMan(vector<pair<int,int>> weddings)
{
	for(auto i : weddings)	
	{
		if(i.second==-1)	
			return i.first;
	}
	return -1;
}

int getWomanHusband(int woman, vector<pair<int,int>> weddings)
{
	for(auto p : weddings)
	{
		if(p.second == woman)
		{
			return p.first;
		}
	}
	return 0;
}

bool womanPreferFirst(int m, int womanHusband, vector<int> preferences)
{
	for(auto p : preferences)	
	{
		if(p==m)
			return true;
		if(p==womanHusband)
			return false;
	}
	return false;
}

void printSolution(vector<pair<int,int>> weddings)
{
	for(auto wed : weddings)
		printf("%d %d\n", wed.first, wed.second);
}
