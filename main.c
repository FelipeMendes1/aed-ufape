#include <stdio.h>
#include <stdlib.h>
#include "tabela/tabela.h"
#include "tabela/tabela.c"
#include "arvore/avl.h"

int op_menu;

int menu();
int menu_buscar();
int menu_listar();
int menu_remover();
int voltar();
void limpar_tela();

int main(int argc, char* argv[]) {

	tabela tab;
	int indice, codigo;
	dado piloto;


	if(inicializarTabela(&tab)) {
		do{
			switch(menu()) {
				int valor;
				case 1:
					printf("Insira os dados do Piloto\n\n");
					if(inserir_piloto(&tab, ler_dados()))
						printf("Piloto Cadastrado com sucesso\n"); 
					else 
						printf("Piloto nao inserido\n");
					break;
					voltar();
				case 2:
					while (1) {
						switch (menu_buscar()) {
							case 1:
								printf("Buscar Piloto por codigo\n\n");
								printf("Codigo: ");
								scanf("%d", &codigo);
								while (getchar() != '\n');
								limpar_tela();
								indice = buscar_indice_avl(tab.indice_avl, codigo);
								if(indice >= 0) {
									piloto = buscar_piloto(tab.arquivo_dados, indice);
									printf("Buscar Piloto por codigo\n\n");
									if(!piloto.removido)
										imprimir_elemento(piloto);
									else
										printf("Erro ao buscar");
								} else
									printf("Nao encontrado\n");
									break;
							case 2:
								goto fim_buscar;
								break;
								
							default:		
								printf("Opcao invalida!\n");
								break;
							}
							voltar();
					}
					fim_buscar:;
					break;
					case 3 :
						while (1) {
							switch (menu_listar())	{
							case 1:
								printf("\n");
								printf("Listando Piloto por codigo:");
								listar_por_codigo(tab.arquivo_dados, tab.indice_avl);
								break;
							case 2:
								goto fim_listar;
								break;
							default:
								break;
							}
							voltar();
						}
						fim_listar:;
						break;
					case 4:
						while (1) {
							switch (menu_remover()) {
								case 1:
									printf("Remover por codigo: ");
									scanf("%d", &codigo);
									indice = buscar_indice_avl(tab.indice_avl, codigo);
									if(indice >= 0) {
										remover_piloto(&tab, indice);
									} else
										printf("Nao encontrado\n");
									break;
								case 2:
									goto fim_remover;
									break;
								default:
									printf("Opcao invalida");
									break;
								}
								voltar();
						}
						fim_remover:;
					break;

					case 5:
						finalizar(&tab);
						exit(1);
					break;

					default:
						printf("Opcao invalida");
			}

		} while(1);
	} 
}

void limpar_tela(){
	system("clear");
}

int menu() {
	limpar_tela();
	printf("|---- Sistema de Cadastro de Pilotos de Formula 1 ----|\n");
	printf("1 - Inserir Piloto\n");
	printf("2 - Buscar Piloto\n");
	printf("3 - Listar Piloto\n");
	printf("4 - Remover Piloto\n");
	printf("5 - Sair\n");
	printf("Opcao : ");
	scanf("%d", &op_menu);
	limpar_tela();
	getchar();
	return op_menu;
}	

int menu_buscar() {
	limpar_tela();
	printf("----Buscar----\n");
	printf("1 - Buscar por codigo: \n");
	printf("2 - Voltar para o menu principal\n");
	printf("Opcao : ");
	scanf("%d", &op_menu);
	limpar_tela();
	getchar();
	return op_menu;
}

int menu_listar() {
	limpar_tela();
	printf("----Listagem---\n");
	printf("1 - Listagem por codigo\n");
	printf("2 - Voltar para o menu principal\n");
	printf("Opcao : ");
	scanf("%d", &op_menu);
	limpar_tela();
	getchar();
	return op_menu;
}

int menu_remover() {
	limpar_tela();
	printf("----Remocao---\n");
	printf("1 - Remocao Por codigo: \n");
	printf("2 - Voltar para o menu principal\n");
	printf("Opcao : ");
	scanf("%d", &op_menu);
	limpar_tela();
	getchar();
	return op_menu;
}

int voltar() {
	printf("\n\n");
	printf("Digite qualquer tecla para voltar: ");
	while(!getchar());
}
