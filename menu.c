#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define ESC 27
#define UM 49
#define DOIS 50
#define TRES 51
#define QUATRO 52
#define CINCO 53
#include"menu.h"



void menu(void){
int tecla;
system("color 0B");
	system("CLS");
	printf("\t==================================================================\n");	
	printf("\t||                     CONTROLE DE ESTOQUE                      ||\n");
	printf("\t||                                                              ||\n");
	printf("\t||    1 - CADASTRAR PRODUTO                                     ||\n");
	printf("\t||    2 - COMPRAR PRODUTO                                       ||\n");
	printf("\t||    3 - VENDER PRODUTO                                        ||\n");
	printf("\t||    4 - RELATORIO DE COMPRA/VENDA/CADASTRO                    ||\n");
	printf("\t||    5 / ESC - SAIR                                            ||\n");
	printf("\t==================================================================\n");

	tecla = getch();
	if(tecla == ESC)
		exit(1);
	
	else if(tecla == UM)
		cadastrar();
	
	else if(tecla == DOIS)
		comprar();
	
	else if(tecla == TRES)
		vender();
		
	else if(tecla == QUATRO)
		listarcadastrados();
		
	else if(tecla == CINCO)
		exit(1);	
	
	
	else{
		menu();
	}	


}

void telainicial(void){
	system("CLS");
	system("color 0B");
	printf("\t==================================================================\n");	
	printf("\t||           C O N T R O L E     D E     E S T O Q U E          ||\n");
	printf("\t||                                                              ||\n");
	printf("\t||    Programa desenvolvido por:                                ||\n");
	printf("\t||    			                                              ||\n");
	printf("\t||    				                                          ||\n");
	printf("\t||    *Marcos Soares                                            ||\n");
	printf("\t||    *Rodrigo Teixeira                                         ||\n");
	printf("\t||                                                              ||\n");
	printf("\t||                                                              ||\n");
	printf("\t||                                                              ||\n");
	printf("\t||Disciplina de Programacao I, Universidade Estadual do Piaui   ||\n");
	printf("\t||Prof Orientador: 							                  ||\n");
	printf("\t||                                                              ||\n");
	printf("\t||                                           Em: Julho de 2015  ||\n");
	printf("\t||Aguarde enquanto o programa inicia...                         ||\n");
	printf("\t==================================================================\n");
	sleep(3);
	printf("Programa iniciado... pressione qualquer tecla.");
	getch();
	menu();
}
