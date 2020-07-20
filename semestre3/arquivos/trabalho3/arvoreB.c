/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 06/06/2020
 */

#include "arvoreB.h"

// Defines utilizados no retorno da insercao recurvisa na arvore B
#define ERROR 0
#define PROMOTION 1
#define NO_PROMOTION 2

//----------------------------------------------//
//------------------ ARVORE B ------------------//
//----------------------------------------------//
int insercaoArvoreBRec(FILE* fp, int currRRN, int key, int rrnDado, int *promoRChild, int *promoKey, int *promoRRNdado);
void split(int iKey, int iRRNdado, int iRRN, RegistroIndice *page, int *promoKey, int *promoRRNdado, int *promoRChild, RegistroIndice *newPage);
void inicializaPagina(RegistroIndice* reg);

//------- Cabeçalho ------//
// Mesma variavel global de main.c para ser acessado por todas as funcao de insercao
extern CabecalhoIndice cabecalhoIndice;

int insercaoArvoreB(FILE* indice, int noRaiz, int chave, int rrnDados)
{
	// Implementacao do procedimento driver
	
	// Cria no raiz se ainda nao existir
	if(cabecalhoIndice.noRaiz == -1)
	{
		RegistroIndice page;
		//inicializaPagina(&page);
		page.n = 1;
		page.nivel = 1;
		page.C[0] = chave;
		page.PR[0] = rrnDados;

		 Inicializa C e PR restantes como -1
		for(int i=1; i<MAXKEYS; i++)
		{
			page.C[i] = -1;
			page.PR[i] = -1;
		}

		// Inicializa ponteiros para proximos nos como -1
		for(int i=0; i<MAXKEYS+1; i++)
		{
			page.P[i] = -1;
		}
		escreveNo(indice, 0, page);
		//imprimeNo(page);
		cabecalhoIndice.noRaiz = 0;
		cabecalhoIndice.nroNiveis = 1;
		cabecalhoIndice.proxRRN = 1;
		//printf("Added root c:%d rrn:%d\n", chave, rrnDados);
	}
	// Adiciona chave a uma btree ja inicializada
	else
	{
		int promoRChild;
		int promoKey;
		int promoRRNdado;
		int result;
		result = insercaoArvoreBRec(indice, noRaiz, chave, rrnDados, &promoRChild, &promoKey, &promoRRNdado);
		if(result == PROMOTION)
		{
			RegistroIndice novaRaiz;
			inicializaPagina(&novaRaiz);
			novaRaiz.n = 1;
			novaRaiz.nivel = cabecalhoIndice.nroNiveis+1;
			novaRaiz.C[0] = promoKey;
			novaRaiz.PR[0] = promoRRNdado;
			novaRaiz.P[0] = noRaiz;
			novaRaiz.P[1] = promoRChild;
			
			//// Inicializa C e PR restantes como -1
			//for(int i=1; i<MAXKEYS; i++)
			//{
			//	novaRaiz.C[i] = -1;
			//	novaRaiz.PR[i] = -1;
			//}

			//// Inicializa ponteiros para proximos nos como -1
			//for(int i=2; i<MAXKEYS+1; i++)
			//{
			//	novaRaiz.P[i] = -1;
			//}

			cabecalhoIndice.noRaiz = cabecalhoIndice.proxRRN;
			escreveNo(indice, cabecalhoIndice.noRaiz, novaRaiz);
			cabecalhoIndice.proxRRN++;
			cabecalhoIndice.nroNiveis++;

			//printf("Create new root rrn:%d\n", cabecalhoIndice.noRaiz);
		}
		else if(result == ERROR)
			return 1;
	}

	cabecalhoIndice.nroChaves++;
	return 0;
}

void split(int iKey, int iRRNdado, int iRRN, RegistroIndice *page, int *promoKey, int *promoRRNdado, int *promoRChild, RegistroIndice *newPage)
{
	// Realiza o split e atualiza em disco
	
	// Pagina temporaria que suporta uma chave a mais
	int tempC[MAXKEYS+1];
	int tempPR[MAXKEYS+1];
	int tempP[MAXKEYS+2];

	// Copia todas as chaves e ponteiros para pagina temporaria
	for(int i=0; i<MAXKEYS; i++)
	{
		tempC[i] = page->C[i];
		tempPR[i] = page->PR[i];
	}
	for(int i=0; i<MAXKEYS+1; i++)
	{
		tempP[i] = page->P[i];
	}

	// Define ultimos como -1
	tempC[MAXKEYS] = -1;
	tempPR[MAXKEYS] = -1;
	tempP[MAXKEYS+1] = -1;

	// Shift dos valores para direita para inserir
	int posToAdd = 0;
	for(int i=MAXKEYS-1; i>=0; i--)
	{
		if(tempC[i]<iKey)
		{
			posToAdd = i+1;
			break;
		}

		tempPR[i+1] = tempPR[i];
		tempC[i+1] = tempC[i];
		tempP[i+2] = tempP[i+1];
	}

	// Insere iKey e iRRN ordenado
	tempC[posToAdd] = iKey;
	tempPR[posToAdd] = iRRNdado;
	tempP[posToAdd+1] = iRRN;

	//printf("GRSDFUIZCXKNLMRFS: ");
	//for(int i=0; i<MAXKEYS+2; i++)
	//{
	//	printf("%d ", tempP[i]);
	//}
	//printf("\n");

	// Define qual chave sera promovida
	int posMiddle = MAXKEYS/2+1;
	*promoKey = tempC[posMiddle];
	*promoRRNdado = tempPR[posMiddle];
	*promoRChild = cabecalhoIndice.proxRRN;

	// Copia chaves/ponteiros antes da promovida para page
	page->n = posMiddle;
	for(int i=0;i<posMiddle;i++)
	{
		page->C[i] = tempC[i];
		page->PR[i] = tempPR[i];
		page->P[i+1] = tempP[i+1];
	}

	// Coloca restante da pagina como -1
	for(int i=posMiddle; i<MAXKEYS; i++)
	{
		page->C[i] = -1;
		page->PR[i] = -1;
		page->P[i+1] = -1;
	}

	// Copia chaves/ponteiros depois da promovida para newPage
	newPage->n = MAXKEYS-posMiddle;
	for(int i=posMiddle+1;i<MAXKEYS+1;i++)
	{
		newPage->C[i-(posMiddle+1)] = tempC[i];
		newPage->PR[i-(posMiddle+1)] = tempPR[i];
		newPage->P[i-(posMiddle+1)] = tempP[i];
	}
	newPage->P[MAXKEYS+1-(posMiddle+1)] = tempP[MAXKEYS+1];

	// Coloca restante da pagina como -1
	for(int i=MAXKEYS-posMiddle; i<MAXKEYS; i++)
	{
		newPage->C[i] = -1;
		newPage->PR[i] = -1;
		newPage->P[i+1] = -1;
	}

	//printf("NOVAS PAGINAAAAS\n");
	//imprimeNo(*page);
	//imprimeNo(*newPage);
}

int insercaoArvoreBRec(FILE* fp, int currRRN, int key, int rrnDado, int *promoRChild, int *promoKey, int *promoRRNdado)
{
	// Funcao recurvisa de insercao na arvore B
	RegistroIndice page;// Registro atual
	RegistroIndice newPage;// Novo registro apos parrticionamento
	int pos;// Posicao onde esta ou deveria estar a chave
	int pbKey;// Chave promovida do nivel inferior
	int pbRRNdado;// RRNdado promovida do nivel inferior
	int pbRRN;// RRN promovido do nivel inferior

	inicializaPagina(&page);
	inicializaPagina(&newPage);

	if(currRRN == -1)
	{
		*promoRChild = -1;
		*promoKey = key;
		*promoRRNdado = rrnDado;
		return PROMOTION;
	}
	else
	{
		// Desce na arvore ate cheagar em um no folha
		leNo(fp, currRRN, &page);
		//imprimeNo(page);
		//printf("Curr RRN: %d\n", currRRN);
		//printf("NIVEL: %d\n", page.nivel);

		// Procura a posicao para continuar a recursao
		pos = 0;
		for(int i=0; i<page.n; i++)
		{
			pos = i;

			// Se encontrou a chave retorna erro (nao pode ter chave duplicada)
			if(key == page.C[i])
			{
				return ERROR;
			}

			// Se a chave esta no nó filho
			if(key < page.C[i])
			{
				break;
			}

			// Se a chave é maior que todas as chaves do nó
			if(i == page.n-1)
			{
				pos++;
			}
		}

		int result;
		result = insercaoArvoreBRec(fp, page.P[pos], key, rrnDado, &pbRRN, &pbKey, &pbRRNdado);
		if(result == NO_PROMOTION || result == ERROR)
		{
			return result;
		}
		else if(page.n<MAXKEYS)
		{
			//printf("CAN INSERT HERE\n");
			//imprimeNo(page);
			//printf("add: %d %d %d\n", pbRRNdado, pbKey, pbRRN);
			// insert in page
			int posToAdd = 0;

			// Shift dos valores para a direita
			for(int i=page.n-1; i>=0; i--)
			{
				if(page.C[i]<pbKey)
				{
					posToAdd = i+1;
					break;
				}

				page.PR[i+1] = page.PR[i];
				page.C[i+1] = page.C[i];
				page.P[i+2] = page.P[i+1];
			}

			page.PR[posToAdd] = pbRRNdado;
			page.C[posToAdd] = pbKey;
			page.P[posToAdd+1] = pbRRN;
			page.n++;
			escreveNo(fp, currRRN, page);
			
			//imprimeNo(page);
			return NO_PROMOTION;
		}
		else
		{
			//printf("promote!\n");
			// Realiza o split
			RegistroIndice newPage;
			newPage.nivel = page.nivel;
			split(pbKey, pbRRNdado, pbRRN, &page, promoKey, promoRRNdado, promoRChild, &newPage);
			//printf("-------\nnew page\n");
			//printf("%d\t", currRRN);
			//imprimeNo(page);
			//printf("%d\t", *promoRChild);
			//imprimeNo(newPage);
			//printf("-------\n");

			// Atualiza/cria paginas em disco
			escreveNo(fp, currRRN, page);
			escreveNo(fp, *promoRChild, newPage);

			// Atualiza dados do struct de cabecalho
			cabecalhoIndice.proxRRN++;
			
			return PROMOTION;
		}
	}
}

int buscaArvoreB(FILE* indice, int rrnNo, int chave, int *rrnEncontrado, int *posEncontrado, RegistroIndice* regEncontrado, int *numAcessos)
{
	// Retorna o RRN de dados com esta chave
	if(rrnNo < 0)
	{
		// Chave de busca nao encontrada
		return 0;
	}

	RegistroIndice reg;
	leNo(indice, rrnNo, &reg);
	(*numAcessos)++;
	for(int i=0; i<reg.n; i++)
	{
		*posEncontrado = i;

		// Se encontrou a chave
		if(chave == reg.C[i])
		{
			*rrnEncontrado = rrnNo;
			*regEncontrado = reg;
			return 1;
		}

		// Se a chave esta no nó filho
		if(chave < reg.C[i])
		{
			return buscaArvoreB(indice, reg.P[i], chave, rrnEncontrado, posEncontrado, regEncontrado, numAcessos);
		}

		// Se a chave é maior que todas as chaves do nó
		if(i == reg.n-1)
		{
			return buscaArvoreB(indice, reg.P[i+1], chave, rrnEncontrado, posEncontrado, regEncontrado, numAcessos);
		}
	}

	// (Nunca deve chegar aqui)
	return 0;
}

int leNo(FILE* fp, int rrnNo, RegistroIndice* reg)
{
	int offset = TAM_CABECALHO_INDICE+rrnNo*TAM_REGISTRO_INDICE;
	int leu;// Se conseguiu ler o registro
	fseek(fp, offset, SEEK_SET);

	// Nivel do nó
	leu = fread(&reg->nivel, sizeof(int), 1, fp);

	// Retorna erro se nao foi possivel ler o registro (fim do arquivo)
	if(leu<=0)
		return 0;

	// N (numero de chaves)
	fread(&reg->n, sizeof(int), 1, fp);

	// Le pares <C, PR>
	for(int i=0; i<MAXKEYS; i++)
	{
		fread(&reg->C[i], sizeof(int), 1, fp);
		fread(&reg->PR[i], sizeof(int), 1, fp);
	}

	// Le ponteiros para proximos nós
	for(int i=0; i<MAXKEYS+1; i++)
	{
		fread(&reg->P[i], sizeof(int), 1, fp);
	}

	return 1;
}

void escreveNo(FILE* fp, int rrnNo, RegistroIndice reg)
{
	int offset = TAM_CABECALHO_INDICE+rrnNo*TAM_REGISTRO_INDICE;
	int leu;// Se conseguiu ler o registro
	fseek(fp, offset, SEEK_SET);

	// Escreve nivel do no
	fwrite(&reg.nivel, sizeof(int), 1, fp);

	// Escreve N (numero de chaves)
	fwrite(&reg.n, sizeof(int), 1, fp);

	// Escreve pares <C, PR>
	for(int i=0; i<MAXKEYS; i++)
	{
		fwrite(&reg.C[i], sizeof(int), 1, fp);
		fwrite(&reg.PR[i], sizeof(int), 1, fp);
	}

	// Escreve ponteiros para proximos nós
	for(int i=0; i<MAXKEYS+1; i++)
	{
		fwrite(&reg.P[i], sizeof(int), 1, fp);
	}
}

void imprimeNo(RegistroIndice reg)
{
	// Utilizado para debugging
	printf("No: n=%d nivel=%d chaves:", reg.n, reg.nivel);

	int regN = reg.n<=5?reg.n:5;

	for(int i=0; i<regN;i++)
	{
		printf("[%d,%d]", reg.C[i], reg.PR[i]);
	}
	printf(" ptrs: ");

	for(int i=0; i<=regN;i++)
	{
		printf("[%d]", reg.P[i]);
	}
	printf("\n");
}

void inicializaPagina(RegistroIndice* reg)
{
	reg->nivel = 0;
	reg->n = 0;
	for(int i=0; i<MAXKEYS; i++)
	{
		reg->C[i] = -1;
		reg->PR[i] = -1;
		reg->P[i] = -1;
	}
	reg->P[MAXKEYS] = -1;
}
