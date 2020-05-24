/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 04/05/2020
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarioNaTela.h"

#define TAM_CABECALHO 128
#define TAM_REGISTRO 128
#define OFFSET_STATUS 0
#define OFFSET_RRN_PROX_REG 1
#define OFFSET_INSERIDOS 5
#define OFFSET_REMOVIDOS 9
#define OFFSET_ATUALIZADOS 13

typedef struct _cabecalho{
	char status;
	int RRNproxRegistro;
	int numeroRegistrosInseridos;
	int numeroRegistrosRemovidos;
	int numeroRegistrosAtualizados;
}Cabecalho;

typedef struct _registro{
	// Variavel (max 105 bytes)
	char cidadeMae[128];
	char cidadeBebe[128];

	// Fixo
	int idNascimento;
	int idadeMae;
	char dataNascimento[11];
	char sexoBebe[2];
	char estadoMae[3];
	char estadoBebe[3];
}Registro;

//------- Cabeçalho ------//
char status = '1';
int RRNproxRegistro = 0;
int numeroRegistrosInseridos = 0;
int numeroRegistrosRemovidos = 0;
int numeroRegistrosAtualizados = 0;

//------------- Protótipos de função --------------//
void opGerarBinario();
void opMostraBinario();
void escreveCabecalho(FILE* fp);
void escreveRegistro(FILE* fp, Registro reg);
Registro leRegistro(FILE* fp, int rrn);
void imprimeRegistros(FILE* fp);
void imprimeRegistro(Registro reg);
void stringAtPos(char str[], int pos, char out[]);

//-------------------- Main ----------------------//
int main()
{
	int opcao;
	scanf("%d", &opcao);

	switch(opcao)
	{
		case 1:
			opGerarBinario();
			break;
		case 2:
			opMostraBinario();
			break;
	}
	return 0;
}

void opGerarBinario()
{
	char csvFileName[100];
	char binFileName[100];
	scanf("%s", csvFileName);
	scanf("%s", binFileName);

	// Abre arquivo csv
	FILE *csv = fopen(csvFileName, "r");
	if(csv==NULL)
	{
		printf("Nao foi possivel abrir %s", csvFileName);
		return;
	}

	// Abre arquivo bin
	FILE *bin = fopen(binFileName, "rwb");
	if(bin==NULL)
	{
		printf("Nao foi possivel abrir %s", binFileName);
		fclose(csv);
		return;
	}

	char line[1024];
	// Ignore first line
	fgets(line, 1024, csv);
	// Read each line
	while(fgets(line, 1024, csv))
	{
		Registro reg;
		char tmp[128];

		// Lê campos do CSV
		// cidadeMae
		stringAtPos(line, 0, reg.cidadeMae);

		// cidadeBebe
		stringAtPos(line, 1, reg.cidadeBebe);

		// idNascimento
		stringAtPos(line, 2, tmp);
		sscanf(tmp, "%d", &reg.idNascimento);

		// idadeMae
		stringAtPos(line, 3, tmp);
		if(strlen(tmp)!=0)
			sscanf(tmp, "%d", &reg.idadeMae);
		else reg.idadeMae=-1;

		// dataNascimento
		stringAtPos(line, 4, reg.dataNascimento);

		// sexoBebe
		stringAtPos(line, 5, reg.sexoBebe);
		
		// estadoMae
		stringAtPos(line, 6, reg.estadoMae);

		// estadoBebe
		stringAtPos(line, 7, reg.estadoBebe);

		// imprime arquivo binario
		escreveRegistro(bin, reg);
	}
	// Escreve abecalho
	escreveCabecalho(bin);

	// Fecha os dois arquivos
	fclose(csv);
	fclose(bin);
	binarioNaTela(binFileName);
}

void opMostraBinario()
{
	// Recebe nome do arquivo binário
	char binFileName[100];
	scanf("%s", binFileName);
	FILE *bin = fopen(binFileName, "rb");
	
	// Checa se arquivo existe
	if(bin==NULL) 
	{
		printf("Falha no processamento do arquivo.\n");
		return;
	}

	// Checa status
	char status;
	fseek(bin, OFFSET_STATUS, SEEK_SET);
	fread(&status, sizeof(char), 1, bin);

	if(status=='0')
	{
		printf("Falha no processamento do arquivo.\n");
		fclose(bin);
		return;
	}

	// Checa se existe registros
	int qtdInseridos;
	fseek(bin, OFFSET_INSERIDOS, SEEK_SET);
	fread(&qtdInseridos, sizeof(int), 1, bin);
	if(qtdInseridos==0)
	{
		printf("Registro inexistente.\n");
		fclose(bin);
		return;
	}

	// Imprime registros
	imprimeRegistros(bin);

	fclose(bin);
}

void imprimeRegistros(FILE* fp)
{
	int qtdRegistros;
	fseek( fp, OFFSET_INSERIDOS, SEEK_SET);
	fread(&qtdRegistros, sizeof(int), 1, fp);
	
	for(int rrn=0;rrn<qtdRegistros;rrn++)
	{
		Registro reg = leRegistro(fp, rrn);
		imprimeRegistro(reg);
	}
}

void imprimeRegistro(Registro reg)
{
	// Checa se o registro foi deletado
	if(reg.cidadeMae[0]!='*')
	{
		// Se string estiver vazia, trocar por "-"
		if(strlen(reg.cidadeBebe)==0)
			strcpy(reg.cidadeBebe, "-");
		if(strlen(reg.estadoBebe)==0)
			strcpy(reg.estadoBebe, "-");
		if(strlen(reg.dataNascimento)==0)
			strcpy(reg.dataNascimento, "-");

		char sexo[10] = "";
		// Imprime sexo dependendo do número registrado
		if(reg.sexoBebe[0]=='0')
			strcpy(sexo, "IGNORADO");
		else if(reg.sexoBebe[0]=='1')
			strcpy(sexo, "MASCULINO");
		else if(reg.sexoBebe[0]=='2')
			strcpy(sexo, "FEMININO");

		// Imprime linha formatada
		printf("Nasceu em %s/%s, em %s, um bebê de sexo %s.\n", reg.cidadeBebe, reg.estadoBebe, reg.dataNascimento, sexo);
	}else{
		printf("Registro deletado.\n");
	}
}

Registro leRegistro(FILE* fp, int rrn)
{
	Registro reg;
	int offset = TAM_CABECALHO+rrn*TAM_REGISTRO;
	int tamCidadeMae, tamCidadeBebe;

	// Checa se registro existe
	fseek(fp, offset, SEEK_SET);
	char aux;
	fread(&aux, sizeof(char), 1, fp);
	if(aux=='*')
	{
		reg.cidadeMae[0]='*';
		reg.cidadeMae[1]='\0';
		return reg;
	}

	// Tamanho cidade mae
	fseek(fp, offset, SEEK_SET);
	fread(&tamCidadeMae, sizeof(int), 1, fp);

	// Tamanho cidade bebe
	fseek(fp, offset+4, SEEK_SET);
	fread(&tamCidadeBebe, sizeof(int), 1, fp);

	// Cidade mae
	fseek(fp, offset+8, SEEK_SET);
	fread(reg.cidadeMae, sizeof(char), tamCidadeMae, fp);
	reg.cidadeMae[tamCidadeMae]='\0';

	// Cidade bebe
	fseek(fp, offset+8+tamCidadeMae, SEEK_SET);
	fread(reg.cidadeBebe, sizeof(char), tamCidadeBebe, fp);
	reg.cidadeBebe[tamCidadeBebe]='\0';

	// Id nascimento
	fseek(fp, offset+105, SEEK_SET);
	fread(&reg.idNascimento, sizeof(int), 1, fp);

	// Idade mae
	fseek(fp, offset+109, SEEK_SET);
	fread(&reg.idadeMae, sizeof(int), 1, fp);

	// Data de nascimento
	fseek(fp, offset+113, SEEK_SET);
	fread(reg.dataNascimento, sizeof(char), 10, fp);
	reg.dataNascimento[10] = '\0';

	// Sexo bebe
	fseek(fp, offset+123, SEEK_SET);
	fread(reg.sexoBebe, sizeof(char), 1, fp);
	reg.sexoBebe[1] = '\0';

	// Estado mae
	fseek(fp, offset+124, SEEK_SET);
	fread(reg.estadoMae, sizeof(char), 2, fp);
	reg.estadoMae[2]='\0';

	// Estado bebe
	fseek(fp, offset+126, SEEK_SET);
	fread(reg.estadoBebe, sizeof(char), 2, fp);
	reg.estadoBebe[2]='\0';

	return reg;
}

void escreveCabecalho(FILE* fp)
{
	int tamCabecalho = TAM_CABECALHO;
	tamCabecalho -= (sizeof(int)*4 + sizeof(char)*1);

	fseek(fp, 0, SEEK_SET);
	// Imprime campos do registro
	fwrite(&status, sizeof(char), 1, fp);
	fwrite(&RRNproxRegistro, sizeof(int), 1, fp);
	fwrite(&numeroRegistrosInseridos, sizeof(int), 1, fp);
	fwrite(&numeroRegistrosRemovidos, sizeof(int), 1, fp);
	fwrite(&numeroRegistrosAtualizados, sizeof(int), 1, fp);

	// Imprime o que resta para completar o registro com '$'
	while(tamCabecalho--)
		fwrite("$", sizeof(char), 1, fp);
}

void escreveRegistro(FILE* fp, Registro reg)
{
	int tamVariavelRestante = 105;

	int tamCidadeMae = strlen(reg.cidadeMae);
	int tamCidadeBebe = strlen(reg.cidadeBebe);
	// Remove tamanho int
	tamVariavelRestante-=sizeof(int);
	tamVariavelRestante-=sizeof(int);
	// Remove tamanho cidade mae
	tamCidadeMae = (tamCidadeMae > tamVariavelRestante) ? tamVariavelRestante : tamCidadeMae;
	tamVariavelRestante-=tamCidadeMae;
	// Remove tamanho cidade bebe
	tamCidadeBebe = (tamCidadeBebe > tamVariavelRestante) ? tamVariavelRestante : tamCidadeBebe;
	tamVariavelRestante-=tamCidadeBebe;

	// Escreve cidade mae e cidade bebe
	fwrite(&tamCidadeMae, sizeof(int), 1, fp);
	fwrite(&tamCidadeBebe, sizeof(int), 1, fp);
	fwrite(reg.cidadeMae, sizeof(char), tamCidadeMae, fp);
	fwrite(reg.cidadeBebe, sizeof(char), tamCidadeBebe, fp);

	while(tamVariavelRestante--)
		fwrite("$", sizeof(char), 1, fp);

	fwrite(&reg.idNascimento, sizeof(int), 1, fp);
	fwrite(&reg.idadeMae, sizeof(int), 1, fp);

	if(strlen(reg.dataNascimento)!=0)
		fwrite(reg.dataNascimento, sizeof(char), 10, fp);
	else
		fwrite("\0$$$$$$$$$", sizeof(char), 10, fp);

	if(strlen(reg.sexoBebe)!=0)
		fwrite(&reg.sexoBebe, sizeof(char), 1, fp);
	else
		fwrite("0", sizeof(char), 1, fp);

	if(strlen(reg.estadoMae)!=0)
		fwrite(&reg.estadoMae, sizeof(char), 2, fp);
	else
		fwrite("\0$", sizeof(char), 2, fp);

	if(strlen(reg.estadoBebe)!=0)
		fwrite(&reg.estadoBebe, sizeof(char), 2, fp);
	else
		fwrite("\0$", sizeof(char), 2, fp);

	// Atualiza RRN
	RRNproxRegistro++;
	numeroRegistrosInseridos++;
}

void stringAtPos(char str[], int pos, char out[])
{
	int start=-1;
	int end=-1;
	pos++;
	// Calcula posicao inicial e final da string
	while(pos--)
	{
		for(int i=++end;i<strlen(str);i++)
		{
			if(str[i]==',')
			{
				start=end;
				end=i;
				break;
			}
			if(i==strlen(str)-1)
			{
				start=end;
				end=strlen(str);
				// Remover \n
				if(str[end-1]=='\n')
					end--;
			}
		}
	}
	// Retorna string entre start e end para out
	int tmp=0;
	for(int i=start;i<end;i++)
		out[tmp++]=str[i];
	out[tmp]='\0';
}
