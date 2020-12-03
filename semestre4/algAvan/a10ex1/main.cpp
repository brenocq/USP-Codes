#include <iostream>
#include <string>
#include <vector>

void solve(std::string t, std::string p);

int main()
{
	std::string text, pattern;
	std::cin >> text >> pattern;
	solve(text, pattern);
	return 0;
}

void solve(std::string t, std::string p)
{
	std::vector<int> temp(p.size());
	temp[0]=0;
	// Generate temp array
	int j=0;
	for(unsigned int i=1; i<temp.size();)
	{
		if(p[i]!=p[j])	
		{
			temp[i]=0;
			if(j!=0)
				j=temp[j-1];
			else
			{
				temp[i]=0;
				i++;
			}

		}
		else
		{
			j++;
			temp[i] = j;
			i++;
		}
	}

	//for(auto val : temp)
	//	std::cout << val << " ";
	//std::cout<<std::endl;

	// Search in t
	j=0;
	for(unsigned int i=0; i<t.size();)
	{
		if(t[i]==p[j])	
		{
			i++;
			j++;
		}
		if(j==(int)p.size())
		{
			std::cout << "O padrao foi encontrado na posicao " << i-j << std::endl;
			j = temp[j-1];
		}
		else if(i<t.size() && t[i]!=p[j])
		{
			if(j!=0)
				j=temp[j-1];
			else
				i++;
		}
	}
}
