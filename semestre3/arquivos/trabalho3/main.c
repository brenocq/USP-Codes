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
#include "comuns.h"
#include "auxiliares.h"

//------- Cabeçalho ------//
Cabecalho cabecalho = {'1',0,0,0,0};
CabecalhoIndice cabecalhoIndice = {'0',-1,0,0,0};
//------------- Funções principais --------------//
void opGerarBinario();
void opMostraBinario();
void opBuscaRegistrosTemplate();
void opBuscaRegistroRRN();
void opRemoveRegistrosTemplate();
void opInserirRegistros();
void opAtualizarRegistros();
void opCriaArquivoIndice();
void opPesquisaArvoreB();
void opInserirArvoreB();

//-------------------- Main ----------------------//
int main()
{
	// Recebe função para executar
	int opcao;
	scanf("%d", &opcao);
	// Executa a funcao do comando
	switch(opcao)
	{
		case 1:
			// Gera binario a partir de um csv
			opGerarBinario();
			break;
		case 2:
			// Imprime todos os registros de um binario
			opMostraBinario();
			break;
		case 3:
			// Busca registros que satisfaçam um critério
			opBuscaRegistrosTemplate();
			break;
		case 4:
			// Busca registro com RRN
			opBuscaRegistroRRN();
			break;
		case 5:
			// Remove registros que satisfaçam um critério
			opRemoveRegistrosTemplate();
			break;
		case 6:
			// Insere registros no binario
			opInserirRegistros();
			break;
		case 7:
			// Atualiza registros no binario
			opAtualizarRegistros();
			break;
		case 8:
			// Cria arquivo de indice
			opCriaArquivoIndice();
		case 9:
			// Pesquisa registros pela arvore B que satisfaçam um critério
			opPesquisaArvoreB();
		case 10:
			// Insere registros utilizando arvore B
			opInserirArvoreB();
	}
	return 0;
}

//-------------------- Opcoes ----------------------//
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
		// Checa se ocorreu algum erro ao abrir o arquivo
		printf("Nao foi possivel abrir %s", csvFileName);
		return;
	}

	// Abre arquivo bin
	FILE *bin = fopen(binFileName, "rwb");
	if(bin==NULL)
	{
		// Checa se ocorreu algum erro ao abrir o arquivo
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
		// Se nao tiver idade da mae o valor 
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
		// Atualiza cabecalho
		cabecalho.RRNproxRegistro++;
		cabecalho.numeroRegistrosInseridos++;
	}
	// Escreve cabecalho
	escreveCabecalho(bin, cabecalho);

	// Fecha os dois arquivos
	fclose(csv);
	fclose(bin);
	binarioNaTela(binFileName);
}

void opMostraBinario()
{
	FILE *fp;
	
	// Recebe nome do arquivo binário
	char binFileName[100];
	scanf("%s", binFileName);
	// Retorna 1 se houve erro
	if(abreBinario(binFileName, &fp, &cabecalho))
		return;

	// Checa se existe registros
	if(cabecalho.numeroRegistrosInseridos==0)
	{
		printf("Registro inexistente.\n");
		fclose(fp);
		return;
	}

	// Imprime registros
	imprimeRegistros(fp);

	fclose(fp);
}

void opBuscaRegistrosTemplate()
{
	FILE *fp;
	
	// Recebe nome do arquivo binário
	char binFileName[100];
	scanf("%s", binFileName);
	// Retorna 1 se houve erro
	if(abreBinario(binFileName, &fp, &cabecalho))
		return;

	Registro templateDeBusca = {"", "", -1, -1, "", "", "", ""};
	// Le template de busca	
	leTemplate(&templateDeBusca);
	// imprime registros do binario com este template
	imprimeRegistrosTemplate(fp, templateDeBusca);

	// Fecha arquivo de leitura
	fclose(fp);
}

void opBuscaRegistroRRN()
{
	FILE *fp;
	char binFileName[100];
	int rrn;
	
	// Recebe nome do arquivo binário
	scanf("%s", binFileName);
	// Retorna 1 se houve erro
	if(abreBinario(binFileName, &fp, &cabecalho))
		return;

	// Le RRN
	scanf("%d", &rrn);
		
	// Checa se existe um registro neste RRN
	if(cabecalho.numeroRegistrosInseridos>0)
	{
		// Imprime registro
		fseek(fp, TAM_CABECALHO+rrn*TAM_REGISTRO, SEEK_SET);
		Registro reg;
		if(leRegistro(fp, rrn, &reg))
			imprimeRegistro(reg);
		else
			printf("Registro Inexistente.\n");
	}
	else
		printf("Registro Inexistente.\n");

	// Fecha arquivo de leitura
	fclose(fp);
}

void opRemoveRegistrosTemplate()
{
	FILE *fp;
	int qtdRepeticoes = 0;
	char binFileName[100];
	
	// Recebe nome do arquivo binário
	scanf("%s", binFileName);
	// Retorna 1 se houve erro
	if(abreBinario(binFileName, &fp, &cabecalho))
		return;
	
	//----- Comecar Operacao -----//
	statusInconsistente(fp, &cabecalho);	

	// Recebe quantas vezes ira executar
	scanf("%d", &qtdRepeticoes);
	while(qtdRepeticoes--)
	{
		Registro templateDeBusca = {"", "", -1, -1, "", "", "", ""};
		// Le template de busca	
		leTemplate(&templateDeBusca);
		// Remove registros do binario com este template
		removeRegistrosTemplate(fp, templateDeBusca, &cabecalho);
	}

	//----- Operacao finalizada -----//

	// Retorna status para consistente e escreve cabecalho
	cabecalho.status = '1';
	escreveCabecalho(fp, cabecalho);

	// Fecha arquivo de leitura
	fclose(fp);

	binarioNaTela(binFileName);
}

void opInserirRegistros()
{
	FILE *fp;
	Registro reg;
	char binFileName[100];
	int quantidadeRegistros;
	
	// Recebe nome do arquivo binário
	scanf("%s", binFileName);
	// Retorna 1 se houve erro
	if(abreBinario(binFileName, &fp, &cabecalho))
		return;

	// Le quantidade de registros para inserir
	scanf("%d", &quantidadeRegistros);
		
	//----- Comecar Operacao -----//
	statusInconsistente(fp, &cabecalho);	

	// Move o ponteiro para inserir no final do arquivo
	fseek(fp, 0, SEEK_END);
	while(quantidadeRegistros--)
	{
		leRegistroInput(&reg);
		escreveRegistro(fp, reg);
		cabecalho.numeroRegistrosInseridos++;
		cabecalho.RRNproxRegistro++;
	}
	//----- Operacao finalizada -----//

	// Retorna status para consistente e escreve cabecalho
	cabecalho.status = '1';
	escreveCabecalho(fp, cabecalho);

	// Fecha arquivo de leitura
	fclose(fp);

	binarioNaTela(binFileName);
}

void opAtualizarRegistros()
{
	FILE *fp;
	char binFileName[100];
	int quantidadeRegistros;
	int rrn;
	// Registro inicializado com valores incomuns para detectar atualizacoes para nulo
	
	// Recebe nome do arquivo binário
	scanf("%s", binFileName);
	// Retorna 1 se houve erro
	if(abreBinario(binFileName, &fp, &cabecalho))
		return;

	//----- Comecar Operacao -----//
	statusInconsistente(fp, &cabecalho);	

	// Le quantidade de registros para inserir
	scanf("%d", &quantidadeRegistros);
		
	while(quantidadeRegistros--)
	{
		Registro reg = {"*", "*", -2, -2, "*", "*", "*", "*"};
		// Le o rrn do registro para atulizar
		scanf("%d", &rrn);
		leTemplate(&reg);

		if(atualizaRegistro(fp, rrn, reg) == 0)
			cabecalho.numeroRegistrosAtualizados++;
	}
	//----- Operacao finalizada -----//

	// Retorna status para consistente e escreve cabecalho
	cabecalho.status = '1';
	escreveCabecalho(fp, cabecalho);

	// Fecha arquivo de leitura
	fclose(fp);
	binarioNaTela(binFileName);
}

void opCriaArquivoIndice()
{
	// Split (quer colocar o setimo): Divide em duas folhas - 3/promove/2
	//  - Cria mais um no, cria um terceiro no para raiz
	//  Usa -1 quando chave nao existir
	//  Usa -1 quando o ponteiro nao existe
	FILE *indice, *dados;
	char indiceFileName[100];
	char dadosFileName[100];

	// Recebe nome dos arquivos
	scanf("%s", dadosFileName);
	scanf("%s", indiceFileName);

	// Abre arquivo de dados
	// Retorna 1 se houve erro
	if(abreBinario(dadosFileName, &dados, &cabecalho))
		return;
	
	// Cria arquivo de indice
	// Retorna 1 se houve erro
	if(criaBinario(indiceFileName, &indice))
		return;
	
	//----- Comecar Operacao -----//
	// Escreve cabecalho do arquivo de indice como inconsistente
	escreveCabecalhoIndice(indice, cabecalhoIndice);

	// Cria arvore B

	//----- Operacao finalizada -----//
	// Escreve cabecalho do arquivo de indice como consistente
	statusConsistenteIndice(indice, &cabecalhoIndice);	

	// Fecha arquivos de escrita/leitura
	fclose(indice);
	fclose(dados);
	binarioNaTela(indiceFileName);
}

void opPesquisaArvoreB()
{

}

void opInserirArvoreB()
{

}
