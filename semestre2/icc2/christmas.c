#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _lang
{
	char* country;
	char* phrase;
}LANG;

int search_lang(LANG* list, char* this_country, int ini, int fim)
{
	//LANG* elem;

	if (ini < fim) return -1;

	int m = (ini + fim) / 2;

	int aux = strcmp(this_country, list[m].country); 
	
	//printf("comp: %s:%s.\n", this_country, elem->country);
	
	if (aux < 0)
	{
		search_lang(list, this_country, ini, m-1);
	}
	else if (aux > 0)
	{
		search_lang(list, this_country, m+1, fim);
	}
	else
	{
		return m;
	}
	return -1;
}

int main()
{
	long int n, aux, size;
	char input[1024];
	LANG* christmas;
	scanf(" %ld ", &size);
	//fprintf(stderr, "%d:", size);
	christmas = (LANG*) malloc (sizeof(LANG) * size);

	for (long int i = 0; i < size; i++)
	{
		scanf(" %[^\r^\n]s ", input);
		//fprintf(stderr, "%s:", input);
		christmas[i].country = (char*) calloc ((strlen(input)+1), sizeof(char)*(strlen(input)+1));
		strcpy(christmas[i].country, input);
	}
	for (long int i = 0; i < size; i++)
	{
		scanf(" %[^\r^\n]s ", input);
		//fprintf(stderr, "%s:", input);
		christmas[i].phrase = (char*) calloc ((strlen(input)+1), sizeof(char)*(strlen(input)+1));
		strcpy(christmas[i].phrase, input);
	}	
/*
	for (int i = 0; i < size; i++)
	{
		printf("pair: %s:%s\n", christmas[i].phrase, christmas[i].country);
	}
*/	
	scanf(" %ld ", &n);

	//fprintf(stderr, "%d:", n);
	for (long int i = 0; i < n; i++)
	{
		scanf(" %[^\r^\n]s ", input);
//		printf("%s.\n\n", input);
		aux = search_lang(christmas, input, 0, size-1);
		//printf("aux is %d\n", search_lang(christmas, input, size));
		
		if(aux == -1)
		{
			fprintf(stdout, "--- NOT FOUND ---\n");
		}
		else
		{
			fprintf(stdout, "%s\n", christmas[aux].phrase);
		}
	}	

}
