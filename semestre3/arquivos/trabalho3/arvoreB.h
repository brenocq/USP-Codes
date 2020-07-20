/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 06/06/2020
 */

#ifndef ARVORE_B_H
#define ARVORE_B_H
#include <stdio.h>
#include <string.h>
#include "comuns.h"

int insercaoArvoreB(FILE* indice, int noRaiz, int chave, int rrnDados);
int buscaArvoreB(FILE* indice, int rrnNo, int chave, int *rrnEncontrado, int *posEncontrado, RegistroIndice* regEncontrado, int *numAcessos);

// Auxiliares
int leNo(FILE* fp, int rrnNo, RegistroIndice* reg);
void escreveNo(FILE* fp, int rrnNo, RegistroIndice reg);
void imprimeNo(RegistroIndice reg);
#endif// ARVORE_B_H
