/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 06/06/2020
 */

#ifndef COMUNS_H
#define COMUNS_H

#define TAM_CABECALHO 128
#define TAM_REGISTRO 128
#define OFFSET_STATUS 0
#define OFFSET_RRN_PROX_REG 1
#define OFFSET_INSERIDOS 5
#define OFFSET_REMOVIDOS 9
#define OFFSET_ATUALIZADOS 13

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
