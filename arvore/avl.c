#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


indice_avl* inicializar_indice_avl(int indice, int codigo)  {
	indice_avl *novo = (indice_avl*) malloc(sizeof(indice_avl));
	novo->indice = indice;
	novo->codigo = codigo;
	return novo;
}

int buscar_indice_avl(arvore_avl raiz, int codigo) {
	if(raiz != NULL) {
		if(raiz->dado->codigo == codigo) {
			return raiz->dado->indice;
		}
		else {
			if(raiz->dado->codigo > codigo)
				return buscar_indice_avl(raiz->sub_esq, codigo);
			else 
				return buscar_indice_avl(raiz->sub_dir, codigo);
		}
	} else {
		return -1;
	}
}

int maior(int dir, int esq) {
	int maior = 0;

	if (dir > esq || esq == dir) {
		maior = dir;
	}
	else if ( esq > dir) {
		maior = esq;
	}

	return maior;
}

int altura_avl(arvore_avl raiz) {
	int altura_dir = 0;
	int altura_esq = 0;
	int altura = 0;

	if (raiz==NULL) {
		return 0;
	}
	else {
		altura_dir = altura_avl(raiz->sub_dir);
		altura_esq = altura_avl(raiz->sub_esq);
		altura = 1 + maior(altura_dir, altura_esq);
		return altura;
	}
}

arvore_avl atualizaFator(arvore_avl raiz) {

	if (raiz == NULL) {
		return 0;
	}
	else {
		raiz->fatorBalanceamento = altura_avl(raiz->sub_dir) - altura_avl(raiz->sub_esq);
		atualizaFator(raiz->sub_dir);
		atualizaFator(raiz->sub_esq);
		return raiz;
	}

}


arvore_avl rotacaoSimplesDireitaAvl(arvore_avl raiz) {
	arvore_avl auxU, auxT2;
	auxU = raiz->sub_esq;
	auxT2 = auxU->sub_dir;

	auxU->sub_dir = raiz;
	raiz->sub_esq = auxT2;

	auxU = atualizaFator(auxU);
	raiz = atualizaFator(raiz);


	return auxU;
}

arvore_avl rotacaoSimplesEsquerdaAvl(arvore_avl raiz) {
	arvore_avl auxU, auxT2;
	auxU = raiz->sub_dir;
	auxT2 = auxU->sub_esq;

	auxU->sub_esq = raiz;
	raiz->sub_dir = auxT2;

	auxU = atualizaFator(auxU);
	raiz = atualizaFator(raiz);

	return auxU;

}

arvore_avl rotacaoDuplaDireitaAvl(arvore_avl raiz) {
	raiz->sub_esq = rotacaoSimplesEsquerdaAvl(raiz->sub_esq);
	raiz = rotacaoSimplesDireitaAvl(raiz);
	return raiz;
}

arvore_avl rotacaoDuplaEsquerdaAvl(arvore_avl raiz) {
	raiz->sub_dir = rotacaoSimplesDireitaAvl(raiz->sub_dir);
	raiz = rotacaoSimplesEsquerdaAvl(raiz);
	return raiz;
}

arvore_avl rotacionar(arvore_avl raiz) {
	if (raiz->fatorBalanceamento == -2 && raiz->sub_esq->fatorBalanceamento == -1) {
		return rotacaoSimplesDireitaAvl(raiz);
	}
	else if (raiz->fatorBalanceamento == 2 && raiz->sub_dir->fatorBalanceamento == 1) {
		return rotacaoSimplesEsquerdaAvl(raiz);
	}
	else if (raiz->fatorBalanceamento == -2 && raiz->sub_esq->fatorBalanceamento == 1) {
		return rotacaoDuplaDireitaAvl(raiz);
	}
	else if (raiz->fatorBalanceamento == 2 && raiz->sub_dir->fatorBalanceamento == -1) {
		return rotacaoDuplaEsquerdaAvl(raiz);
	}
	return raiz;
}


int maior_avl(arvore_avl raiz) {
	int maiorAvl = raiz->valor;
	while (raiz->sub_dir != NULL) {
		if (raiz->sub_dir->valor > maiorAvl) {
			maiorAvl = raiz->sub_dir->valor;
		}
		raiz = raiz->sub_dir;
	}
	return maiorAvl;

}


arvore_avl inserir_avl(indice_avl *v, arvore_avl raiz) {

	if (raiz == NULL) {
		arvore_avl novo = (arvore_avl)malloc(sizeof(struct no_avl));
		novo->dado = v;
		novo->sub_esq = NULL;
		novo->sub_dir = NULL;
		novo->fatorBalanceamento = 0;
		return novo;
	}
	else {
		if (v->codigo > raiz->dado->codigo) {
			raiz->sub_dir = inserir_avl(v, raiz->sub_dir);
			raiz = atualizaFator(raiz);

		}
		else {
			raiz->sub_esq = inserir_avl(v, raiz->sub_esq);
			raiz = atualizaFator(raiz);

		}
		raiz = rotacionar(raiz);

		return raiz;
	}
}

arvore_avl remover_avl(int v, arvore_avl raiz) {

	if (raiz == NULL) {
		return raiz;
	}

	if (raiz->dado->codigo == v) {

		if (raiz->sub_esq == NULL && raiz->sub_dir == NULL) {
			free(raiz);
			return NULL;
		}

		if (raiz->sub_esq != NULL && raiz->sub_dir == NULL) {
			arvore_avl aux = raiz->sub_esq;
			free(raiz);

			aux = atualizaFator(aux);
			aux = rotacionar(aux);

			return aux;
		}
		if (raiz->sub_esq == NULL && raiz->sub_dir != NULL) {
			arvore_avl aux = raiz->sub_dir;
			free(raiz);

			aux = atualizaFator(aux);
			aux = rotacionar(aux);

			return aux;
		}

		int maiorAvl = maior_avl(raiz->sub_esq);
		raiz->valor = maiorAvl;
		raiz->sub_esq = remover_avl(maiorAvl, raiz->sub_esq);

		raiz = atualizaFator(raiz);
		raiz = rotacionar(raiz);

		return raiz;

	}
	if (v > raiz->valor) {
		raiz->sub_dir = remover_avl(v, raiz->sub_dir);
	}
	else {
		raiz->sub_esq = remover_avl(v, raiz->sub_esq);
	}

	return raiz;

}
void in_orderAvl(arvore_avl raiz) {
	if (raiz != NULL) {
		in_orderAvl(raiz->sub_esq);
		printf("[%d] fb:%d\n", raiz->valor, raiz->fatorBalanceamento);
		in_orderAvl(raiz->sub_dir);
	}
}

void pre_orderAvl(arvore_avl raiz) {
	if (raiz != NULL) {
		printf("[%d] fb:%d\n", raiz->valor, raiz->fatorBalanceamento);
		pre_orderAvl(raiz->sub_esq);
		pre_orderAvl(raiz->sub_dir);
	}
}




