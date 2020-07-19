/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 06/06/2020
 */

#ifndef COMUNS_H
#define COMUNS_H

// Info arquivo de indice
#define TAM_CABECALHO_INDICE 72
#define TAM_REGISTRO_INDICE 128
#define ORDEM 6

// Info arquivo de dados
#define TAM_CABECALHO 128
#define TAM_REGISTRO 128
#define OFFSET_STATUS 0
#define OFFSET_RRN_PROX_REG 1
#define OFFSET_INSERIDOS 5
#define OFFSET_REMOVIDOS 9
#define OFFSET_ATUALIZADOS 13

// ARQUIVO DE INDICE
typedef struct _registroIndice{
	int nivel;
	int n;
	int C[ORDEM-1];// Chaves ordanadas de forma crescente
	int PR[ORDEM-1];// RRN do registro de dados
	int P[ORDEM];// Referencia para subarvore
}RegistroIndice;

typedef struct _cabecalhoIndice{
	char status;
	int noRaiz;
	int nroNiveis;
	int proxRRN;
	int nroChaves;
}CabecalhoIndice;

// ARQUIVO DE DADOS
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

typedef struct _cabecalho{
	char status;
	int RRNproxRegistro;
	int numeroRegistrosInseridos;
	int numeroRegistrosRemovidos;
	int numeroRegistrosAtualizados;
}Cabecalho;

#endif// COMUNS_H
