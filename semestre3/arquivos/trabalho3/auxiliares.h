/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 06/06/2020
 */
#ifndef AUXILIARES_H
#define AUXILIARES_H
#include <stdio.h>
#include <string.h>
#include "binarioNaTela.h"
#include "comuns.h"

void stringAtPos(char str[], int pos, char out[]);
char containsTemplate(Registro template, Registro reg);
char abreBinario(char nomeArquivoBinario[], FILE **fp, Cabecalho *cabecalho);
char abreBinarioIndice(char nomeArquivoBinario[], FILE **fp, CabecalhoIndice *cabecalho);
char criaBinario(char nomeArquivoBinario[], FILE **fp);

// Leitura
int leRegistro(FILE* fp, int rrn, Registro* reg);
void leRegistroInput(Registro* reg);
char leCabecalho(FILE *fp, Cabecalho *cabecalho);
char leCabecalhoIndice(FILE *fp, CabecalhoIndice *cabecalho);
void leTemplate(Registro* template);

// Escrita
void escreveRegistro(FILE* fp, Registro reg);
void escreveCabecalho(FILE* fp, Cabecalho cabecalho);
void escreveCabecalhoIndice(FILE* fp, CabecalhoIndice cabecalho);
void statusInconsistente(FILE* fp, Cabecalho* cabecalho);
void statusInconsistenteIndice(FILE* fp, CabecalhoIndice* cabecalho);
void statusConsistente(FILE* fp, Cabecalho* cabecalho);
void statusConsistenteIndice(FILE* fp, CabecalhoIndice* cabecalho);
char atualizaRegistro(FILE* fp, int rrn, Registro reg);

// Remocao
void removeRegistrosTemplate(FILE* fp, Registro template, Cabecalho *cabecalho);
void removeRegistro(FILE* fp, int rrn);

// Impressao
void imprimeRegistros(FILE* fp);
void imprimeRegistrosTemplate(FILE* fp, Registro template);
void imprimeRegistro(Registro reg);

#endif// AUXILIARES_H
