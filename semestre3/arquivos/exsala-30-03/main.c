#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//------------ Main menu -----------//
void printMenu();
int validMenuOption(int selected);
//-------- Register products -------//
void printRegisterProdMenu();
void registerProducts(FILE *fp);
//-------- Recover products --------//
void printRecoverProdMenu();
void printProducts(FILE *fp);

int main()
{
	FILE *fp;
	fp = fopen("arquivoBinario.bin", "arb+");
	char aux[50];
	int menuAux = -1;
		
	while(1)
	{
		printMenu();
		do{
			scanf("%d", &menuAux);
			if(!validMenuOption(menuAux))
				printf("Por favor insira uma opção de menu válida.\n");
		}while(!validMenuOption(menuAux));

		switch(menuAux)
		{
			case 0:
				exit(0);
				break;
			case 1:
				//-------- Register products --------//
				printRegisterProdMenu();
				registerProducts(fp);
				break;
			case 2:
				//-------- Recover products --------//
				printRecoverProdMenu();
				printProducts(fp);
				break;
		}
	}
	
	fclose(fp);
	return 0;
}

//------------------------------- Main menu ------------------------------//
void printMenu()
{
	printf("---------------- Menu --------------------\n");
	printf("1 - Gravar novos produtos\n");
	printf("2 - Recuperar produtos gravados\n");
	printf("0 - Sair\n");
}

int validMenuOption(int selected)
{
	return selected>=0 && selected<=2;
}

//--------------------------- Register Products --------------------------//
void printRegisterProdMenu()
{
	printf("-------- Registrar novos produtos --------\n");
	printf("Digite q no nome/marca/ean13 para parar de cadastrar\n");
}

void registerProducts(FILE *fp){
	char nome[50];	
	char marca[50];	
	char ean[14];	
	float valor;	

	fseek(fp, 0, SEEK_END);

	while(1)
	{
		// Nome
		printf("NOME: ");
		scanf("%s", nome);
		if(strcmp(nome, "q")==0)
			return;
		// Marca
		printf("MARCA: ");
		scanf("%s", marca);
		if(strcmp(nome, "q")==0)
			return;
		// Ean
		printf("EAN13 (13 digitos): ");
		scanf("%s", ean);
		if(strcmp(nome, "q")==0)
			return;
		// Valor
		printf("VALOR: ");
		scanf("%f", &valor);

		fwrite(&nome, sizeof(char), 50, fp);
		fwrite(&marca, sizeof(char), 50, fp);
		fwrite(&ean, sizeof(char), 14, fp);
		fwrite(&valor, sizeof(float), 1, fp);

		printf("Produto cadastrado!\n\n");
	}
}

//---------------------------- Recover Products ---------------------------//
void printRecoverProdMenu()
{
	printf("-------- Produtos registrados --------\n");
}

void printProducts(FILE* fp)
{
	char nome[50];	
	char marca[50];	
	char ean[14];	
	float valor;	

	fseek(fp, 0, SEEK_SET);
	while(fread(nome, sizeof(char), 50, fp) !=0)
	{
		fread(marca, sizeof(char), 50, fp);
		fread(ean, sizeof(char), 14, fp);
		fread(&valor, sizeof(float), 1, fp);
		printf("NOME: %s\n", nome);
		printf("MARCA: %s\n", marca);
		printf("EAN13: %s\n", ean);
		printf("VALOR: %.2f\n\n", valor);
	}
}
