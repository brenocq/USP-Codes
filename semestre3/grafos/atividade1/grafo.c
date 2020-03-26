#include "grafo.h"

struct grafo_{
	int *matrizAdj;
	int qtdVertices;
};

GRAFO *grafo_criar(int qtdVertices)
{
	// Cria o grafo 
	GRAFO *grafo = (GRAFO*)malloc(sizeof(GRAFO));

	if(grafo==NULL)
	{
		printf("Não foi possível criar o grafo. O programa será encerrado.\n");
		exit(0);
	}

	grafo->matrizAdj = (int*)calloc(qtdVertices*qtdVertices,sizeof(int));
	if(grafo->matrizAdj==NULL)
	{
		printf("Não foi possível criar a matriz de adjacências. O programa será encerrado.\n");
		exit(0);
	}

	grafo->qtdVertices = qtdVertices;

	return grafo;
}

void grafo_inserir(GRAFO *grafo, int v0, int v1)
{
	// Insere uma aresta do grafo
	
	int qtd = grafo->qtdVertices;
	// Error
	if(v0>=qtd || v1>=qtd)
	{
		printf("Não foi possível inserir uma aresta entre os vértices %d e %d", v0, v1);
		return;
	}

	grafo->matrizAdj[v0*qtd + v1] = 1;
	grafo->matrizAdj[v1*qtd + v0] = 1;
}

void grafo_remover(GRAFO *grafo, int v0, int v1)
{
	// Remove uma aresta do grafo
	
	int qtd = grafo->qtdVertices;
	// Error
	if(v0>=qtd || v1>=qtd)
	{
		printf("Não foi possível inserir uma aresta entre os vértices %d e %d", v0, v1);
		return;
	}

	grafo->matrizAdj[v0*qtd + v1] = 0;
	grafo->matrizAdj[v1*qtd + v0] = 0;
}

void grafo_exibir(GRAFO *grafo)
{
	// Exibe a matriz de adjacências
	for(int i=0;i<grafo->qtdVertices;i++)
	{
		for(int j=0;j<grafo->qtdVertices;j++)
		{
			printf("%d ", grafo->matrizAdj[i*grafo->qtdVertices+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void grafo_deletar(GRAFO **grafo)
{
	// Libera o espaço da memória alocada para o grafo
	free((*grafo)->matrizAdj);
	free(*grafo);
}
