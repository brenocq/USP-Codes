#ifndef RELATORIO_H
#define RELATORIO_H

// Define o tipo bool
#define bool char 
#define true 1
#define false 0

typedef struct _aluno Aluno;
typedef struct _registros Registros;

Registros* registro_criar();// Cria o registro
Aluno* aluno_criar(int id, float horasDeEstudo, float nota1, float nota2);// Cria elemento sobre aluno
bool registro_deletar(Registros *r);// Destroi todos os registros
bool registro_inserir(Registros *r, Aluno* aluno);// Insere novo aluno nos registros
bool registro_remover(Registros *r, int IDdoAluno);// Remove aluno dos registros
Aluno* registro_busca(Registros *r, int IDdoAluno);// Retorna aluno desejado
void registro_imprimir(Registros *r);// Imprime todas as informações registradas
void relatorio_de_aprovacoes(Registros *r);// Imprime o relatório de aprovações
void horas_de_estudo(Registros *r);// Imprimi a quantidade de horas de estudo

#endif
