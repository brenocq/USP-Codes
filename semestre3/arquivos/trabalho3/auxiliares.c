/*
 * Autor: Breno Cunha Queiroz
 * SCC0215 - Organização de Arquivos
 * 11218991
 *
 * Data: 06/06/2020
 */
#include "auxiliares.h"

void stringAtPos(char str[], int pos, char out[])
{
	// Esta funcao retorna a string na posicao [pos] na linha do csv
	// Exemplo:
	// 12, luis, 34, eduardo
	// Se a posicao for 0, retornará "12"
	// Se a posição for 1, retormará "luis"
	// E assim por diante
	
	int start=-1;
	int end=-1;
	
	// Calcula posicao inicial(start) e final(end) da string na posicao [pos]
	// Executa o while [pos] vezes+1
	pos++;
	while(pos--)
	{
		// Percorre a string procurando ','
		// Quando encontra ',' atualiza start e end
		for(int i=++end;i<strlen(str);i++)
		{
			if(str[i]==',')
			{
				start=end;
				end=i;
				break;
			}
			// Trata quando é a ultima posição (nao termina com ',')
			if(i==strlen(str)-1)
			{
				start=end;
				end=strlen(str);
				// Remover \n
				if(str[end-1]=='\n')
					end--;
			}
		}
	}
	// Retorna string entre start e end para out
	int tmp=0;
	for(int i=start;i<end;i++)
		out[tmp++]=str[i];
	out[tmp]='\0';
}

char containsTemplate(Registro template, Registro reg)
{
	// Compara cada campo do registro com o template
	// Se o template esta com aquele campo preenchido, este campro deve ter o mesmo valor no registro
	if(strlen(template.cidadeMae)>0 && strcmp(template.cidadeMae, reg.cidadeMae)!=0)
		return 0;
	if(strlen(template.cidadeBebe)>0 && strcmp(template.cidadeBebe, reg.cidadeBebe)!=0)
		return 0;
	if(template.idNascimento!=-1 && template.idNascimento!=reg.idNascimento)
		return 0;
	if(template.idadeMae!=-1 && template.idadeMae!=reg.idadeMae)
		return 0;
	if(strlen(template.dataNascimento)>0 && strcmp(template.dataNascimento, reg.dataNascimento)!=0)
		return 0;
	if(strlen(template.sexoBebe)>0 && strcmp(template.sexoBebe, reg.sexoBebe)!=0)
		return 0;
	if(strlen(template.estadoMae)>0 && strcmp(template.estadoMae, reg.estadoMae)!=0)
		return 0;
	if(strlen(template.estadoBebe)>0 && strcmp(template.estadoBebe, reg.estadoBebe)!=0)
		return 0;

	// Se todos os campos definidos no template tem o mesmo valor no reg
	return 1;
}

char abreBinario(char nomeArquivoBinario[], FILE **fp, Cabecalho* cabecalho)
{
	*fp = fopen(nomeArquivoBinario, "r+b");

	if(*fp==NULL) 
	{
		printf("Falha no processamento do arquivo.\n");
		return 1;
	}
	
	// Le o cabecalho (retorna 0 se houve erro na leitura)
	if(leCabecalho(*fp, cabecalho) == 0)
		return 1;
	return 0;
}

char abreBinarioIndice(char nomeArquivoBinario[], FILE **fp, CabecalhoIndice *cabecalho)
{
	*fp = fopen(nomeArquivoBinario, "r+b");

	if(*fp==NULL) 
	{
		printf("Falha no processamento do arquivo.\n");
		return 1;
	}
	
	// Le o cabecalho (retorna 0 se houve erro na leitura)
	if(leCabecalhoIndice(*fp, cabecalho) == 0)
		return 1;
	return 0;
}

char criaBinario(char nomeArquivoBinario[], FILE **fp)
{
	*fp = fopen(nomeArquivoBinario, "w+b");

	if(*fp==NULL) 
	{
		printf("Falha no processamento do arquivo.\n");
		return 1;
	}

	return 0;
}

void statusInconsistente(FILE* fp, Cabecalho* cabecalho)
{
	// Coloca status como inconsistente
	cabecalho->status ='0';
	fseek(fp, OFFSET_STATUS, SEEK_SET);
	fwrite(&cabecalho->status, sizeof(char), 1, fp);
}

void statusInconsistenteIndice(FILE* fp, CabecalhoIndice* cabecalho)
{
	// Coloca status do cabecalho de indice como inconsistente
	cabecalho->status ='0';
	fseek(fp, OFFSET_STATUS, SEEK_SET);
	fwrite(&cabecalho->status, sizeof(char), 1, fp);
}

void statusConsistente(FILE* fp, Cabecalho* cabecalho)
{
	// Coloca status como consistente
	cabecalho->status = '1';
	fseek(fp, OFFSET_STATUS, SEEK_SET);
	fwrite(&cabecalho->status, sizeof(char), 1, fp);
}

void statusConsistenteIndice(FILE* fp, CabecalhoIndice* cabecalho)
{
	// Coloca status do cabecalho de indice como consistente
	cabecalho->status = '1';
	fseek(fp, OFFSET_STATUS, SEEK_SET);
	fwrite(&cabecalho->status, sizeof(char), 1, fp);
}

//----------------------------------------------//
//------------------ LEITURA -------------------//
//----------------------------------------------//
void leTemplate(Registro* template)
{
	// Esta funcao altera os campos do template com os valores lidos do terminal
	// Os templates estao sendo utilizados tanto para buscar de acordo com um template
	// ou para atualizar os dados de um determinado registro
	
	int qtdCamposBusca = 0;
	char campoParaBusca[16];
	char aux[5];
	
	// Recebe quantidade de campos do filtro
	scanf("%d", &qtdCamposBusca);
	// Preenche registro com template de busca
	while(qtdCamposBusca--)
	{
		scanf("%s", campoParaBusca);
		// Preenche cidadeMae
		if(strcmp(campoParaBusca, "cidadeMae")==0)	
		{
			scan_quote_string(template->cidadeMae);
		}
		// Preenche cidadeBebe
		else if(strcmp(campoParaBusca, "cidadeBebe")==0)
		{
			scan_quote_string(template->cidadeBebe);
		}
		// Preenche idNascimento
		else if(strcmp(campoParaBusca, "idNascimento")==0)
		{
			scanf("%s", aux);
			// Se for nulo, preencher com -1
			if(strcmp(aux, "NULO") == 0)
				template->idNascimento = -1;
			else
				template->idNascimento = atoi(aux);
		}
		// Preenche idadeMae
		else if(strcmp(campoParaBusca, "idadeMae")==0)
		{
			scanf("%s", aux);
			// Se for nulo, preencher com -1
			if(strcmp(aux, "NULO") == 0)
				template->idadeMae = -1;
			else
				template->idadeMae = atoi(aux);
		}
		// Preenche dataNascimento
		else if(strcmp(campoParaBusca, "dataNascimento")==0)
		{
			scan_quote_string(template->dataNascimento);
		}
		// Preenche sexoBebe
		else if(strcmp(campoParaBusca, "sexoBebe")==0)
		{
			scan_quote_string(template->sexoBebe);
		}
		// Preenche estadoMae
		else if(strcmp(campoParaBusca, "estadoMae")==0)
		{
			scan_quote_string(template->estadoMae);
		}
		// Preenche estadoBebe
		else if(strcmp(campoParaBusca, "estadoBebe")==0)
		{
			scan_quote_string(template->estadoBebe);
		}
	}
}

char leCabecalho(FILE *fp, Cabecalho *cabecalho)
{
	// Move para o inicio e le o cabecalho
	fseek(fp, OFFSET_STATUS, SEEK_SET);
	fread(&cabecalho->status, sizeof(char), 1, fp);
	fread(&cabecalho->RRNproxRegistro, sizeof(int), 1, fp);
	fread(&cabecalho->numeroRegistrosInseridos, sizeof(int), 1, fp);
	fread(&cabecalho->numeroRegistrosRemovidos, sizeof(int), 1, fp);
	fread(&cabecalho->numeroRegistrosAtualizados, sizeof(int), 1, fp);

	// Checa consistencia do arquivo
	if(cabecalho->status=='0')
	{
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		return 0;
	}
	return 1;
}

char leCabecalhoIndice(FILE *fp, CabecalhoIndice *cabecalho)
{
	// Move para o inicio e le o cabecalho
	fseek(fp, OFFSET_STATUS, SEEK_SET);
	fread(&cabecalho->status, sizeof(char), 1, fp);
	fread(&cabecalho->noRaiz, sizeof(int), 1, fp);
	fread(&cabecalho->nroNiveis, sizeof(int), 1, fp);
	fread(&cabecalho->proxRRN, sizeof(int), 1, fp);
	fread(&cabecalho->nroChaves, sizeof(int), 1, fp);

	// Checa consistencia do arquivo
	if(cabecalho->status=='0')
	{
		printf("Falha no processamento do arquivo.\n");
		fclose(fp);
		return 0;
	}
	return 1;
}

int leRegistro(FILE* fp, int rrn, Registro* reg)
{
	int offset = TAM_CABECALHO+rrn*TAM_REGISTRO;
	int tamCidadeMae, tamCidadeBebe;
	int leu;// Se conseguiu ler o registro

	// Tamanho cidade mae
	leu = fread(&tamCidadeMae, sizeof(int), 1, fp);

	// Retorna erro se nao foi possivel ler o registro (fim do arquivo)
	if(leu<=0)
		return 0;

	// Checa se registro existe
	if(tamCidadeMae==-1)
	{
		reg->cidadeMae[0]='*';
		reg->cidadeMae[1]='\0';

		// Move para inicio do proximo registro
		fseek(fp, TAM_CABECALHO+(rrn+1)*TAM_REGISTRO, SEEK_SET);
		return 1;
	}

	// Tamanho cidade bebe
	fread(&tamCidadeBebe, sizeof(int), 1, fp);

	// Cidade mae
	fread(reg->cidadeMae, sizeof(char), tamCidadeMae, fp);
	reg->cidadeMae[tamCidadeMae]='\0';

	// Cidade bebe
	fread(reg->cidadeBebe, sizeof(char), tamCidadeBebe, fp);
	reg->cidadeBebe[tamCidadeBebe]='\0';

	// Move para inicio dos campos de tamanho fixo
	fseek(fp, offset+105, SEEK_SET);

	// Id nascimento
	fread(&reg->idNascimento, sizeof(int), 1, fp);

	// Idade mae
	fread(&reg->idadeMae, sizeof(int), 1, fp);

	// Data de nascimento
	fread(reg->dataNascimento, sizeof(char), 10, fp);
	reg->dataNascimento[10] = '\0';

	// Sexo bebe
	fread(reg->sexoBebe, sizeof(char), 1, fp);
	reg->sexoBebe[1] = '\0';

	// Estado mae
	fread(reg->estadoMae, sizeof(char), 2, fp);
	reg->estadoMae[2]='\0';

	// Estado bebe
	fread(reg->estadoBebe, sizeof(char), 2, fp);
	reg->estadoBebe[2]='\0';

	return 1;
}

void leRegistroInput(Registro* reg)
{
	// Enquanto o leTemplate le casos como:
	// campo valor campo valor campo valor
	// Esta funcao le todos os valores do registro a partir do terminal. Exemplo:
	// cidadeMae cidadeBebe idNascimento idadeMae dataNascimento sexoBebe estadoMae estadoBebe
	int qtdCamposBusca = 0;
	char campoParaBusca[16];
	char aux[5];
	
	// Le cada um dos campos e coloca em reg
	scan_quote_string(reg->cidadeMae);
	scan_quote_string(reg->cidadeBebe);

	scanf("%s", aux);
	// Se for nulo, definir como -1
	if(strcmp(aux, "NULO") == 0)
		reg->idNascimento = -1;
	else
		reg->idNascimento = atoi(aux);

	scanf("%s", aux);
	// Se for nulo, definir como -1
	if(strcmp(aux, "NULO") == 0)
		reg->idadeMae = -1;
	else
		reg->idadeMae = atoi(aux);

	scan_quote_string(reg->dataNascimento);
	scan_quote_string(reg->sexoBebe);
	scan_quote_string(reg->estadoMae);
	scan_quote_string(reg->estadoBebe);
}

//----------------------------------------------//
//------------------ ESCRITA -------------------//
//----------------------------------------------//
void escreveCabecalho(FILE* fp, Cabecalho cabecalho)
{
	int tamCabecalho = TAM_CABECALHO;
	// Tamanho total menos quantidade de bytes escritos
	tamCabecalho -= (sizeof(int)*4 + sizeof(char)*1);

	// Move para o inicio do arquivo
	fseek(fp, 0, SEEK_SET);
	// Imprime campos do registro
	fwrite(&cabecalho.status, sizeof(char), 1, fp);
	fwrite(&cabecalho.RRNproxRegistro, sizeof(int), 1, fp);
	fwrite(&cabecalho.numeroRegistrosInseridos, sizeof(int), 1, fp);
	fwrite(&cabecalho.numeroRegistrosRemovidos, sizeof(int), 1, fp);
	fwrite(&cabecalho.numeroRegistrosAtualizados, sizeof(int), 1, fp);

	// Imprime o que resta para completar o registro com '$'
	while(tamCabecalho--)
		fwrite("$", sizeof(char), 1, fp);
}

void escreveCabecalhoIndice(FILE* fp, CabecalhoIndice cabecalho)
{
	int tamCabecalho = TAM_CABECALHO_INDICE;
	// Tamanho total menos quantidade de bytes escritos
	tamCabecalho -= (sizeof(int)*4 + sizeof(char)*1);

	// Move para o inicio do arquivo
	fseek(fp, 0, SEEK_SET);
	// Imprime campos do registro
	fwrite(&cabecalho.status, sizeof(char), 1, fp);
	fwrite(&cabecalho.noRaiz, sizeof(int), 1, fp);
	fwrite(&cabecalho.nroNiveis, sizeof(int), 1, fp);
	fwrite(&cabecalho.proxRRN, sizeof(int), 1, fp);
	fwrite(&cabecalho.nroChaves, sizeof(int), 1, fp);

	// Imprime o que resta para completar o registro com '$'
	while(tamCabecalho--)
		fwrite("$", sizeof(char), 1, fp);
}

void escreveRegistro(FILE* fp, Registro reg)
{
	int tamVariavelRestante = 105;

	// Tamanho dos campos variaveis cidade mae e cidade bebe
	int tamCidadeMae = strlen(reg.cidadeMae);
	int tamCidadeBebe = strlen(reg.cidadeBebe);
	// Remove tamanho int
	tamVariavelRestante-=sizeof(int);
	tamVariavelRestante-=sizeof(int);
	// Remove tamanho cidade mae
	tamCidadeMae = (tamCidadeMae > tamVariavelRestante) ? tamVariavelRestante : tamCidadeMae;
	tamVariavelRestante-=tamCidadeMae;
	// Remove tamanho cidade bebe
	tamCidadeBebe = (tamCidadeBebe > tamVariavelRestante) ? tamVariavelRestante : tamCidadeBebe;
	tamVariavelRestante-=tamCidadeBebe;

	// Escreve cidade mae e cidade bebe
	fwrite(&tamCidadeMae, sizeof(int), 1, fp);
	fwrite(&tamCidadeBebe, sizeof(int), 1, fp);
	fwrite(reg.cidadeMae, sizeof(char), tamCidadeMae, fp);
	fwrite(reg.cidadeBebe, sizeof(char), tamCidadeBebe, fp);

	// Preenche o que sobrar com '$'
	while(tamVariavelRestante--)
		fwrite("$", sizeof(char), 1, fp);

	// Escreve id nascimento
	fwrite(&reg.idNascimento, sizeof(int), 1, fp);
	// Escreve idade mae
	fwrite(&reg.idadeMae, sizeof(int), 1, fp);

	// Escreve data de nascimento (trata se for null)
	if(strlen(reg.dataNascimento)!=0)
		fwrite(reg.dataNascimento, sizeof(char), 10, fp);
	else
		fwrite("\0$$$$$$$$$", sizeof(char), 10, fp);

	// Escreve sexo do bebe (trata se for null)
	if(strlen(reg.sexoBebe)!=0)
		fwrite(&reg.sexoBebe, sizeof(char), 1, fp);
	else
		fwrite("0", sizeof(char), 1, fp);

	// Escreve estado da mae (trata se for null)
	if(strlen(reg.estadoMae)!=0)
		fwrite(&reg.estadoMae, sizeof(char), 2, fp);
	else
		fwrite("\0$", sizeof(char), 2, fp);

	// Escreve estado de bebe (trata se for null)
	if(strlen(reg.estadoBebe)!=0)
		fwrite(&reg.estadoBebe, sizeof(char), 2, fp);
	else
		fwrite("\0$", sizeof(char), 2, fp);

}

char atualizaRegistro(FILE* fp, int rrn, Registro reg)
{
	int tamVariavelRestante = 105;
	int tamCidadeMae, tamCidadeBebe;
	int leu;

	// Move para registro que sera removido
	fseek(fp, TAM_CABECALHO+rrn*TAM_REGISTRO, SEEK_SET);

	// Checa se registro foi deletado ou nao acessivel
	leu = fread(&tamCidadeMae, sizeof(int), 1, fp);
	if(leu<=0 || tamCidadeMae == -1)
		return 1;

	// Volta a o file pointer para o inicio
	fseek(fp, -sizeof(int), SEEK_CUR);

	// Atualiza tamanho de cidadeMae
	if(strcmp(reg.cidadeMae, "*") != 0)
	{
		tamCidadeMae = strlen(reg.cidadeMae);
		// Confere para nao permitir valor maior que o permitido para a string
		if(tamCidadeMae>tamVariavelRestante)
			tamCidadeMae=tamVariavelRestante;
		fwrite(&tamCidadeMae, sizeof(int), 1, fp);
	}
	else 
	{
		// Recebe tamanho de cidadeMae (nao sera alterado)
		fread(&tamCidadeMae, sizeof(int), 1, fp);
	}
	tamVariavelRestante-=tamCidadeMae;

	// Atualiza tamanho de cidadeBebe
	if(strcmp(reg.cidadeBebe, "*") != 0)
	{
		tamCidadeBebe = strlen(reg.cidadeBebe);
		// Confere para nao permitir valor maior que o permitido para a string
		if(tamCidadeBebe>tamVariavelRestante)
			tamCidadeBebe=tamVariavelRestante;

		fwrite(&tamCidadeBebe, sizeof(int), 1, fp);
	}
	else 
	{
		// Recebe tamanho de cidadeMae (nao sera alterado)
		fread(&tamCidadeBebe, sizeof(int), 1, fp);
	}
	tamVariavelRestante-=tamCidadeBebe;

	// Atualiza cidadeMae
	if(strcmp(reg.cidadeMae, "*") != 0)
		fwrite(&reg.cidadeMae, sizeof(char), tamCidadeMae, fp);
	else// Move o file pointer para o proximo campo
		fseek(fp, tamCidadeMae, SEEK_CUR);
	
	// Atualiza cidadeBebe
	if(strcmp(reg.cidadeBebe, "*") != 0)
		fwrite(&reg.cidadeBebe, sizeof(char), tamCidadeBebe, fp);
	else
		fseek(fp, tamCidadeBebe, SEEK_CUR);

	// Move para a porcao fixa do registro
	fseek(fp, TAM_CABECALHO+rrn*TAM_REGISTRO+105, SEEK_SET);
	// Atualiza idNascimento se necessario
	if(reg.idNascimento != -2)
		fwrite(&reg.idNascimento, sizeof(int), 1, fp);
	else
		fseek(fp, sizeof(int), SEEK_CUR);

	// Atualiza idadeMae se necessario
	if(reg.idadeMae != -2)
		fwrite(&reg.idadeMae, sizeof(int), 1, fp);
	else
		fseek(fp, sizeof(int), SEEK_CUR);

	// Atualiza dataNascimento se necessario
	if(strcmp(reg.dataNascimento, "") == 0)
		fwrite("\0$$$$$$$$$", sizeof(char), 10, fp);
	else if(strcmp(reg.dataNascimento, "*") != 0)
		fwrite(&reg.dataNascimento, sizeof(char), 10, fp);
	else
		fseek(fp, 10*sizeof(char), SEEK_CUR);

	// Atualiza sexoBebe se necessario
	if(strcmp(reg.sexoBebe, "") == 0)
		fwrite("0", sizeof(char), 1, fp);
	else if(strcmp(reg.sexoBebe, "*") != 0)
		fwrite(&reg.sexoBebe, sizeof(char), 1, fp);
	else
		fseek(fp, 1*sizeof(char), SEEK_CUR);

	// Atualiza estadoMae se necessario
	if(strcmp(reg.estadoMae, "") == 0)
		fwrite("\0$", sizeof(char), 2, fp);
	else if(strcmp(reg.estadoMae, "*") != 0)
		fwrite(&reg.estadoMae, sizeof(char), 2, fp);
	else
		fseek(fp, 2*sizeof(char), SEEK_CUR);
	
	// Atualiza estadoBebe se necessario
	if(strcmp(reg.estadoBebe, "") == 0)
		fwrite("\0$", sizeof(char), 2, fp);
	else if(strcmp(reg.estadoBebe, "*") != 0)
		fwrite(&reg.estadoBebe, sizeof(char), 2, fp);
	else
		fseek(fp, 2*sizeof(char), SEEK_CUR);

	return 0;
}

//----------------------------------------------//
//------------------ REMOCAO -------------------//
//----------------------------------------------//
void removeRegistrosTemplate(FILE* fp, Registro template, Cabecalho *cabecalho)
{
	// Esta funcao remove todos os registros do binario com o template de busca
	
	// Move para primeiro registro (rrn=0)
	fseek(fp, TAM_CABECALHO+0*TAM_REGISTRO, SEEK_SET);

	// Procura registros com o template
	Registro reg;
	int rrn=0;
	while(leRegistro(fp, rrn, &reg))
	{
		// Remove se registro ainda nao foi removido
		if(reg.cidadeMae[0]!='*')
		{
			// Remove registros com o tamplate
			if(containsTemplate(template, reg))
			{
				removeRegistro(fp, rrn);
				// Altera cabecalho para cada registro removido
				cabecalho->numeroRegistrosInseridos--;
				cabecalho->numeroRegistrosRemovidos++;
				// Move para ler proximo registro
				fseek(fp, TAM_CABECALHO+(rrn+1)*TAM_REGISTRO, SEEK_SET);
			}
		}
		rrn++;
	}
}

void removeRegistro(FILE* fp, int rrn)
{
	int removedFlag = -1;
	// Move para registro que sera removido
	fseek(fp, TAM_CABECALHO+rrn*TAM_REGISTRO, SEEK_SET);
	// Imprime a flag de removido no registro
	fwrite(&removedFlag, sizeof(int), 1, fp);
}

//----------------------------------------------//
//----------------- IMPRESSAO ------------------//
//----------------------------------------------//
void imprimeRegistrosTemplate(FILE* fp, Registro template)
{
	// Imprime todos os registros do binario com o template de busca

	// Move para primeiro registro (rrn=0)
	fseek(fp, TAM_CABECALHO+0*TAM_REGISTRO, SEEK_SET);

	// Procura registros com o template
	char encontrou = 0;
	Registro reg;
	int rrn=0;
	while(leRegistro(fp, rrn++, &reg))
	{
		// Le o registro e imprime
		if(containsTemplate(template, reg))
		{
			imprimeRegistro(reg);
			encontrou = 1;
		}
	}
	if(!encontrou)
		printf("Registro Inexistente.\n");
}

void imprimeRegistros(FILE* fp)
{
	// Move para primeiro registro (rrn=0)
	fseek(fp, TAM_CABECALHO+0*TAM_REGISTRO, SEEK_SET);

	// Para cada registro...
	Registro reg;
	int rrn=0;
	while(leRegistro(fp, rrn++, &reg))
	{
		// Le o registro e imprime
		imprimeRegistro(reg);
	}
}

void imprimeRegistro(Registro reg)
{
	// Checa se o registro foi deletado
	if(reg.cidadeMae[0]!='*')
	{
		// Se string estiver vazia, trocar por "-"
		if(strlen(reg.cidadeBebe)==0)
			strcpy(reg.cidadeBebe, "-");
		if(strlen(reg.estadoBebe)==0)
			strcpy(reg.estadoBebe, "-");
		if(strlen(reg.dataNascimento)==0)
			strcpy(reg.dataNascimento, "-");

		char sexo[10] = "";
		// Imprime sexo dependendo do número registrado
		if(reg.sexoBebe[0]=='0')
			strcpy(sexo, "IGNORADO");
		else if(reg.sexoBebe[0]=='1')
			strcpy(sexo, "MASCULINO");
		else if(reg.sexoBebe[0]=='2')
			strcpy(sexo, "FEMININO");

		// Imprime linha formatada
		printf("Nasceu em %s/%s, em %s, um bebê de sexo %s.\n", reg.cidadeBebe, reg.estadoBebe, reg.dataNascimento, sexo);
	}else{
		printf("Registro Inexistente.\n");
	}
}
