#ifndef TABELA_H
#define TABELA_H
#include "../arvore/avl.h"
#include "../arvore/avl.c"
//#include <stdio_ext.h>

enum tipo_arvore {AVL};
typedef enum tipo_arvore tipo_arvore;


enum eqp {Mercedes_AMG, Red_Bull, McLaren, Scuderia_Ferrari, Alpine,
				   Scuderia_AlphaTauri, Aston_Martin, Alfa_Romeo, Williams_Racing,
				   Haas, Indeterminada};
				   
typedef enum eqp eqp;


typedef struct piloto {
	int removido;
	char nome[50];
    int codigo;
	int idade;
	float altura;
	char* nacionalidade;
	eqp equipe[2];
}dado;

typedef struct tabela {

	FILE *arquivo_dados;
	arvore_avl indice_avl;

} tabela;

int inicializarTabela(tabela *tab);

int inserir_piloto(tabela *tab, dado *pil);
void remover_piloto(tabela *tab, int indice);
dado buscar_piloto(FILE *arq, int chave);

void salvar_piloto(FILE *arq, dado *pil);
void imprimir_elemento(dado pil);
void listar_por_codigo(FILE *arq, arvore_avl raiz);


void salvar_arquivo_avl(char *nome, arvore_avl raiz);
void salvar_auxiliar_avl(arvore_avl raiz, FILE *arq);

void carregar_arquivo_arvore(tabela *tab, tipo_arvore tipo);

dado* ler_dados();
void tirar_enter(char *string);
void finalizar (tabela *tab);

#endif