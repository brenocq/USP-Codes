#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
	int n, m, q;

	// Recebe tamanho do grafo e número de arestas
	scanf("%d",&n);
	scanf("%d",&m);

	// Cria o grafo
	GRAFO *grafo = grafo_criar(n);

	// Cria as m arestas
	for(int i=0;i<m;i++)
	{
		int v0, v1;
		scanf("%d",&v0);
		scanf("%d",&v1);
		grafo_inserir(grafo, v0, v1);
	}

	// Recebe número de operações
	scanf("%d",&q);

	// Realiza as q operações
	for(int i=0;i<q;i++)
	{
		int operacao;
		int v0, v1;// Auxiliares

		scanf("%d",&operacao);
		switch(operacao)
		{
			case 1:
				// Insere nova aresta
				scanf("%d",&v0);
				scanf("%d",&v1);
				grafo_inserir(grafo, v0, v1);
				break;

			case 2:
				// Remove aresta
				scanf("%d",&v0);
				scanf("%d",&v1);
				grafo_remover(grafo, v0, v1);
				break;

			case 3:
				// Exibe matriz de adjacências
				grafo_exibir(grafo);
				break;
		}
	}

	grafo_deletar(&grafo);
	return 0;
}
