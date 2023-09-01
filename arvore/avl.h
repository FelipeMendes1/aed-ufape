#ifndef AVL_H
#define AVL_H
#include <stdlib.h>

typedef struct indice_avl {
	int codigo;
	int indice; 
}indice_avl;


typedef struct no_avl {
	indice_avl *dado;
	int valor;
	int fatorBalanceamento;
	struct no_avl *sub_esq, *sub_dir;
} no_avl;

typedef no_avl* arvore_avl;

indice_avl* inicializar_indice_avl(int indice, int codigo);
int buscar_indice_avl(arvore_avl raiz, int codigo);

int maior(int dir, int esq);
int maior_avl(arvore_avl raiz);
int altura_avl(arvore_avl raiz);
arvore_avl rotacionar(arvore_avl raiz);
arvore_avl rotacaoSimplesDireitaAvl(arvore_avl raiz);
arvore_avl rotacaoSimplesEsquerdaAvl(arvore_avl raiz);
arvore_avl rotacaoDuplaDireitaAvl(arvore_avl raiz);
arvore_avl rotacaoDuplaEsquerdaAvl(arvore_avl raiz);
arvore_avl atualizaFator(arvore_avl raiz);
void in_orderAvl(arvore_avl raiz);
void pre_orderAvl(arvore_avl raiz);
arvore_avl inserir_avl(indice_avl *v, arvore_avl raiz);
arvore_avl remover_avl(int valor, arvore_avl raiz);

#endif