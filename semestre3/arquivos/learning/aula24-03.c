#include<stdlib.h>
#include<stdio.h>

int main()
{
	FILE *fp;
	//char meutexto[10];

	//fp = fopen("arquivo.txt", "r");

	//fread(meutexto, sizeof(char), 9, fp);
	//meutexto[9]='\0';

	//printf("%s\n", meutexto);

	//fseek(fp, 5, SEEK_CUR);

	//fread(meutexto, sizeof(char), 9, fp);
	//meutexto[9]='\0';

	//printf("%s\n", meutexto);

	char a,b;

	a = 'b';
	b = 'a';

	char *vetor = "OI MADUUU :)"; 
	fp = fopen("meuArquivo-binario.bin", "wb");

	//fwrite(&a, sizeof(char), 1, fp);
	//fwrite(&b, sizeof(char), 1, fp);

	fwrite(vetor, sizeof(char), 12, fp);
	
	fclose(fp);
	return 0;
}
