#ifndef RELATORIO_H
#define RELATORIO_H
typedef struct _aluno Aluno;
typedef struct _registros Registros;

Registros* registro_criar();// Cria o registro
void registro_deletar(Registros *r);// Destroi todos os registros
Aluno* aluno_criar(int id, float horasDeEstudo, float nota1, float nota2);

void registro_inserir(Registros *r, Aluno* aluno);
int registro_remover(Registros *r, int IDdoAluno);
Aluno* registro_busca(Registros *r, int IDdoAluno);
void registro_imprimir(Registros *r);
void relatorio_de_aprovacoes(Registros *r);
void horas_de_estudo(Registros *r);

#endif
