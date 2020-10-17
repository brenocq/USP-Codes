#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <math.h>

using namespace std;

map<int, int> paths;
int target[9] = {8,0,1,2,3,4,5,6,7};

string solve(int init);
int IDA(int last, int current, int depth, int realDepth, int limit);
int calcDistance(int curr);
int move(int curr, int direction);
int readInit();
string getMove(int from, int to);
string getPathString();
bool isSolvable(int init);

int main()
{
	int n;
	scanf("%d", &n);

	while(n-->0)
	{
		// Read init config
		int init = readInit();
		string res = solve(init);
		if(n>0)
			printf("%s\n\n", res.c_str());
		else
			printf("%s\n", res.c_str());
	}

	return 0;
}

int readInit()
{
	int result = 0;
	int i=9;
	while(i-->0)
	{
		char temp = ' ';
		while(temp==' ' || temp=='\n' || temp=='\r')
			scanf("%c", &temp);
		int num = temp=='x'?0:temp-'0';	
		result += num*pow(10,i);
	}
	return result;
}


int calcDistance(int curr)
{
	int result = 0;
	string currStr = to_string(curr);
	if(currStr.size()==8)
		currStr = "0"+currStr;
	for(int i=0;i<9;i++)
	{
		int posX = i%3;
		int posY = i/3;
		int goalX = target[currStr[i]-'0']%3;
		int goalY = target[currStr[i]-'0']/3;

		int res = abs(posX-goalX)+abs(posY-goalY);
		result += res;
	}
	return result;
}

int move(int curr, int direction)
{
	int moved = curr;
	string currStr = to_string(curr);
	if(currStr.size()==8)
		currStr = "0"+currStr;
	for(int i=0;i<9;i++)
	{
		if(currStr[i]=='0')
		{
			int posX = i%3;
			int posY = i/3;
			switch(direction)
			{
				case 3:// Up
					if(posY>0)
					{
						currStr[i] = currStr[i-3];
						currStr[i-3] = '0';
						moved = stoi(currStr);
					}
					break;
				case 0:// Left
					if(posX>0)
					{
						currStr[i] = currStr[i-1];
						currStr[i-1] = '0';
						moved = stoi(currStr);
					}
					break;
				case 1:// Down
					if(posY<2)
					{
						currStr[i] = currStr[i+3];
						currStr[i+3] = '0';
						moved = stoi(currStr);
					}
					break;
				case 2:// Right
					if(posX<2)
					{
						currStr[i] = currStr[i+1];
						currStr[i+1] = '0';
						moved = stoi(currStr);
					}
					break;
			}
			break;
		}
	}
	return moved;
}


string getMove(int from, int to)
{
	if(to == 0 || from == 0)
		return "";
	string fromStr = to_string(from);
	if(fromStr.size()==8)
		fromStr = "0"+fromStr;
	string toStr = to_string(to);
	if(toStr.size()==8)
		toStr = "0"+toStr;

	int fromPos;
	int toPos;
	for(int i=0;i<9;i++)
	{
		if(fromStr[i]=='0')
			fromPos = i;
		if(toStr[i]=='0')
			toPos = i;
	}

	if(toPos-fromPos==1)
		return "r";
	if(toPos-fromPos==-1)
		return "l";
	if(toPos-fromPos==3)
		return "d";
	if(toPos-fromPos==-3)
		return "u";
	return "";
}

string getPathString()
{
	string moves = "";
	int current = 123456780;
	do
	{
		moves = getMove(paths[current], current)+moves;
		current = paths[current];
	}while(paths[current]!=0);

	return moves;
}

bool isSolvable(int init)
{
	string currStr = to_string(init);
	if(currStr.size()==8)
		currStr = "0"+currStr;

	int qtyInversions = 0;

	for(int i=0; i<9; i++)
		for(int j=i+1; j<9; j++)
			if(currStr[i]>currStr[j] && currStr[i]!='0' && currStr[j]!='0')
				qtyInversions++;

	return qtyInversions%2==0;
}

int IDA(int last, int current, int depth, int realDepth, int limit) {
	if(depth>=limit)
		return -1;

	// Check if not visited before
	if(paths.find(current) == paths.end())
		paths[current] = last;
	else
		return -1;

	if(calcDistance(current) == 0)
		return realDepth;

	for(int i=0;i<4;i++)	
	{
		// Test each of the 4 movements
		int moved = move(current, i);
		if(moved == current)
			continue;
		int distanceToTarget = calcDistance(moved);
	
		int res = IDA(current, moved, realDepth+1+distanceToTarget, realDepth+1, limit);
		if(res != -1)
			return res;
	}

	return -1;
}

string solve(int init)
{
	int maxDepth = 0;
	if(!isSolvable(init))
		return string("unsolvable");

	while(true)
	{
		// Reset visited
		paths.clear();
		// Increase max depth
		maxDepth++;
		// Call IDA
		int res = IDA(0,init, 0, 0, maxDepth);
		if(res!=-1)
			return getPathString();
	}
}
