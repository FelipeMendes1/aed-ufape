#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#include <string.h>

int inicializarTabela(tabela *tab) {
	tab->arquivo_dados = fopen("dados.dat", "r+b");
	tab->indice_avl = NULL;
	
	carregar_arquivo_arvore(tab, AVL);

	if(tab->arquivo_dados != NULL)
		return 1;
	else
		return 0;
}
void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

int inserir_piloto(tabela *tab, dado *pil) {
	
	int posicaoNovoRegistro, retorno;
	retorno = tab->arquivo_dados != NULL;
	if(retorno) {
		fseek(tab->arquivo_dados, 0L, SEEK_END);
		
		posicaoNovoRegistro = ftell(tab->arquivo_dados);
		
		
		tab->indice_avl = inserir_avl(inicializar_indice_avl(posicaoNovoRegistro, pil->codigo), tab->indice_avl);
		
		//salvar no arquivo de dados
		salvar_piloto(tab->arquivo_dados, pil);
	}

	return retorno;
}

void salvar_piloto(FILE *arq, dado *pil) {

	fprintf(arq, "%d;%s;", pil->removido, pil->nome);

	fprintf(arq, ";%d;%d;%f;%s;%d\n", pil->codigo, pil->idade, pil->altura, pil->nacionalidade, pil->equipe[0]);

}

void remover_piloto(tabela* tab, int indice) {
	if(tab != NULL){
		dado pil = buscar_piloto(tab->arquivo_dados, indice);
		if(!pil.removido){
			tab->indice_avl = remover_avl(pil.codigo, tab->indice_avl);
			fseek(tab->arquivo_dados, indice, SEEK_SET);
			char str[] = "1";
			fwrite(str, 1, sizeof(char), tab->arquivo_dados);
			fseek(tab->arquivo_dados, 0L, SEEK_END);
		}
		else
			printf("Erro ao remover\n");
	}
}

char* equipes_enum(int eq) {
	switch(eq) {
		case 1:
			return "Mercedes_AMG";
		case 2:
			return "Red_Bull";
		case 3:
			return "McLaren";
		case 4:
			return "Scuderia_Ferrari";
		case 5:
			return "Alpine";
		case 6:
			return "Scuderia_AlphaTauri";
		case 7:
			return "Aston_Martin";
		case 8:
			return "Alfa_Romeo";
		case 9:
			return "Williams_Racing";
		case 10:
			return "Haas";
		case 11:
			return "Indeterminada";
	}
}

dado* ler_dados() {
	int equi, op;
	dado* novo = (dado*) malloc(sizeof(dado));
	char * buffer = (char *) malloc(256 * sizeof(char));

	printf("Nome: ");
	scanf(" %[^\n]%*c", novo->nome);

	printf("Codigo: ");
	while (scanf("%d", &novo->codigo) != 1) {
		printf("Insira apenas numeros: ");
		while ((getchar()) != '\n');
	}
	while (getchar() != '\n');

	printf("Idade: ");
	while (scanf("%d", &novo->idade) != 1) {
		printf("Insira apenas numeros: ");
		while ((getchar()) != '\n');
	}

	printf("Altura: ");
	while (scanf("%f", &novo->altura) != 1) {
		printf("Insira apenas numeros: ");
		while ((getchar()) != '\n');
	}
	while (getchar() != '\n');

	printf("Nacionalidade: ");
	fgets(buffer, 256, stdin);
	novo->nacionalidade = strdup(buffer);
	tirar_enter(novo->nacionalidade);

	printf("Equipes disponiveis:\n");
	for(int i = 1; i <= 11; i++){
		printf("%d - %s\n", i, equipes_enum(i));
	}
	printf("\n");

	printf("Selecione a Equipe: ");
	while (scanf("%d", &equi) != 1 || equi > 11) {
		printf("Insira um numero entre 1 e 11: ");
		while ((getchar()) != '\n');
	}
	novo->equipe[0] = (eqp) equi;


	free(buffer);
	novo->removido = 0;

	return novo;
}

void carregar_arquivo_arvore(tabela *tab, tipo_arvore tipo) {

	FILE *arq;
	size_t len;
	char nome[16], *linha = (char*) malloc(len), delim[] = ";";
	switch (tipo) {
	case AVL:
		strcpy(nome, "indices_avl.dat");
		break;
	}
	arq = fopen(nome, "r+");
    
  if(arq != NULL){
		while(getdelim(&linha, &len, '\n', arq) > 0){
  			char *ptr;
			ptr = strtok(linha, delim);
			int indice = atoi(ptr);
			ptr = strtok(NULL, delim);
			tirar_enter(ptr);
			switch (tipo) {
				case AVL:
					tab->indice_avl = inserir_avl(inicializar_indice_avl(indice, atoi(ptr)),tab->indice_avl);
					break;
			}
		}
		fclose(arq);
 	}
 	free(linha);
}

dado buscar_piloto(FILE *arq, int indice){
	dado temp;
	if(indice >= 0 ){ 
		if(arq != NULL){
			long len = sizeof(char) * 256;
			char *buffer = (char *) malloc(len);
			char delim[] = ";";
			dado temp;
			fseek(arq, indice, SEEK_SET);

			getline(&buffer, &len, arq);
			
			char *ptr = strtok(buffer, delim);
			temp.removido = atoi(ptr);

			ptr = strtok(NULL, delim);
			strcpy(temp.nome, ptr);
			
			ptr = strtok(NULL, delim);
			temp.codigo = atoi(ptr);

			ptr = strtok(NULL, delim);
			temp.idade = atoi(ptr);

			ptr = strtok(NULL, delim);
			temp.altura = atof(ptr);

			ptr = strtok(NULL, delim);
			temp.nacionalidade = (char*) malloc(sizeof(ptr));
			strcpy(temp.nacionalidade, ptr);

			ptr = strtok(NULL, ",");
			temp.equipe[0] = (eqp) atoi(ptr);

			return temp;
			
		}
		printf("Arquivo invalido!\n");
	} else 
		printf("Indice invalido!\n");
	temp.removido = 1;
	return temp;
} 

void imprimir_elemento(dado pil){

	printf("Nome: %s\n", pil.nome);
	printf("Codigo: %d\n", pil.codigo);
	printf("Idade: %d\n", pil.idade);
	printf("Altura: %.2f\n", pil.altura);
	printf("Nacionalidade: %s\n", pil.nacionalidade);
	printf("Equipe: ");
	printf("%s", equipes_enum((int)pil.equipe[0]));
	printf("\n");
	
	
}

void listar_por_codigo(FILE *arq, arvore_avl raiz) {

	if(raiz != NULL) {
		listar_por_codigo(arq, raiz->sub_esq);
		printf("\n-----------------------------------------------\n\n");
		imprimir_elemento(buscar_piloto(arq, raiz->dado->indice));
		listar_por_codigo(arq, raiz->sub_dir);
	}
}

void salvar_arquivo_avl(char *nome, arvore_avl raiz) {
	FILE *arq;
	arq = fopen(nome, "w+");
	if(arq != NULL) {
		salvar_auxiliar_avl(raiz, arq);
		fclose(arq);
	}
}

void salvar_auxiliar_avl(arvore_avl raiz, FILE *arq){
	if(raiz != NULL) {
		
		fprintf(arq, "%d;%d\n", raiz->dado->indice, raiz->dado->codigo);
		salvar_auxiliar_avl(raiz->sub_esq, arq);
		salvar_auxiliar_avl(raiz->sub_dir, arq);
	}

}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo_avl("indices_avl.dat", tab->indice_avl);
}