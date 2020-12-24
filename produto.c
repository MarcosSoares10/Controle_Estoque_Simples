#include<stdio.h>
#include<stdlib.h>
#include"abrirarq.h"
#include<string.h>
#include<conio.h>
#include"menu.h"
#define UM 49
#define DOIS 50
#define ESC 27
#define ENTER 13
#include<time.h>




typedef struct prod{
	int cod;
	char descricao[41];
	float preco;
	int estoque;
	float vendatotal;
	float compratotal;
	int caddia, cadmes, cadano, cadhora, cadmin, cadsec; //registro de data e hora da ultima alteração do cadastro
	int	compdia, compmes, compano, comphora, compmin, compsec; //registro de data e hora da ultima compra do produto
	int venddia, vendmes, vendano, vendhora, vendmin, vendsec; //registro de data e hora da ultima venda do produto
}Produto;

//Estrutura para capturar dados de data e hora da biblioteca Time.h


Produto buscaCodigo(int cod){
	Produto c;
	rewind(fp);
	while(!feof(fp)){
		if(fread(&c, sizeof(Produto), 1, fp))
			if(cod == c.cod)
				return c;
				
	}
c.cod = -3;
return c;
	
}

void cadastrar(void){
	system("color 0B");
	abrirarq();
	struct tm *Data;
	time_t segundos;
	time(&segundos);
	Data = localtime(&segundos);
	Produto c, p;
	int tecla;
	system("CLS");
	printf("\t\t====== CADASTRO DE PRODUTOS ======\n\n");
	printf("Escolha uma opcao\n\n");
	printf("1 - Alterar dados do produto\n");
	printf("2 - Cadastrar novo\n\n");
	printf("ESC - Menu principal\n");
	
	fflush(stdin); //limpa o buffer do teclado pra evitar erros ao capturar a tecla digitada
	tecla = getch(); // captura uma tecla digitada
		
	if(tecla == UM){
		system("CLS");
		printf("\tALTERAR CADASTRO\n");		
		printf("Digite codigo do produto que deseja alterar\n");
		scanf("%d", &c.cod);
		if(c.cod>0)
		p = buscaCodigo(c.cod);
		if(p.cod == c.cod){
			system("CLS");
			printf("Produto identificado: %s\n", p.descricao);
			printf("Codigo do produto: %d\n", p.cod);
			printf("Preco Atual: R$%g\n", p.preco);
			printf("\n=============================== \n");
			printf("Digite nova Descricao do produto.\n");
			fflush(stdin);
			gets(c.descricao);
			strupr(c.descricao);
			system("CLS");
			printf("*Nota: Caso queira abortar esta operacao, digite um valor negativo neste campo.\n\n\n\n");
			printf("Digite novo preco unitario do produto: ");
			scanf("%f", &c.preco);
			if(c.preco<0){
				printf("\n\n\nVoce entrou com um valor negativo e por este motivo esta operacao foi abortada.\n- O produto nao foi salvo na base de dados...\n\n\n");
				getch();
				menu();				
			}
			else{
				p.preco = c.preco;
				strcpy(p.descricao,c.descricao);
				p.caddia = Data->tm_mday;
				p.cadmes = Data->tm_mon+1;
				p.cadano = Data->tm_year+1900;
				p.cadhora = Data->tm_hour;
				p.cadmin = Data->tm_min;
				p.cadsec = Data->tm_sec;
				fseek(fp, -1 * sizeof(Produto), SEEK_CUR);
				fwrite(&p, sizeof(Produto), 1, fp);
				system("CLS");
				printf("\tCADASTRO ALTERADO COM SUCESSO...\n\n");
				printf("Codigo do produto: %d\n", p.cod);
				printf("Nova descricao: %s\n", p.descricao);
				printf("Novo preco unitario: R$ %g\n", p.preco);
				printf("Cadastro alterado em %d/%d/%d as %d:%d:%d.\n\n\n", p.caddia,p.cadmes,p.cadano,p.cadhora,p.cadmin,p.cadsec);
				printf("\n\n\nAgora voce pode adicionar este produto em estoque no menu <COMPRAR PRODUTOS>...\n ");
				printf("\n\n\n");
				getch();
				fclose(fp);
				menu();
			}
			
			
		}
		else{
			system("CLS");
			printf("Produto nao consta na base de dados...\n\n\n\n");
			getch();
			menu();
		}
			
		
	}
	
	else if (tecla == DOIS){
		system("CLS");
		printf("\tCADASTRAR NOVO\n\n");
		printf("Digite codigo do produto.\n");
		scanf("%d", &c.cod);
		if(c.cod>0){
			p = buscaCodigo(c.cod);
			if(p.cod == c.cod){
				printf("\nProduto ja cadastrado no sistema... \n\n\n\n");
				getch();
				menu();
			}
			else{
				system("CLS");
				printf("Descricao do produto: ");
				fflush(stdin);
				gets(c.descricao);
				strupr(c.descricao);
				system("CLS");
				printf("*Nota: Caso queira abortar esta operacao, digite um valor negativo neste campo.\n\n\n\n");
				printf("Digite o preco unitario do produto:");
				scanf("%f", &c.preco);
				if(c.preco < 0){
					printf("\n\n\nVoce entrou com um valor negativo e por este motivo esta operacao foi abortada.\n- O produto nao foi salvo na base de dados...\n\n\n");
					getch();
					menu();
				}
				else{
					c.estoque = 0;
					c.compratotal = 0;
					c.vendatotal = 0;
					c.compdia = 0;
					c.compmes = 0;
					c.compano = 0;
					c.comphora=0;
					c.compmin=0;
					c.compsec=0;
					c.vendano=0;
					c.vendmes=0;
					c.venddia=0;
					c.vendhora=0;
					c.vendmin=0;
					c.vendsec=0;
					c.caddia = Data->tm_mday;
					c.cadmes = Data->tm_mon+1;
					c.cadano = Data->tm_year+1900;
					c.cadhora = Data->tm_hour;
					c.cadmin = Data->tm_min;
					c.cadsec = Data->tm_sec;
					fseek(fp,0, SEEK_END);
					fwrite(&c, sizeof(Produto), 1, fp);
					system("CLS");
					printf("\tPRODUTO CADASTRADO COM SUCESSO...\n\n");
					printf("Codigo do produto: %d\n", c.cod);
					printf("Descricao: %s\n", c.descricao);
					printf("Preco unitario: R$ %g\n", c.preco);
					printf("Cadastro realizado em %d/%d/%d as %d:%d:%d.\n\n\n", c.caddia,c.cadmes,c.cadano,c.cadhora,c.cadmin,c.cadsec);
					printf("\n\n\nAgora voce pode adicionar este produto em estoque no menu <COMPRAR PRODUTOS>...\n ");
					printf("\n\n\n");
					getch();
					fclose(fp);
					menu();
				}
					
				
			}
		}
		else{
			printf("Digite numero maior que zero...\n\n\n");
			getch();
			menu();
		}
	}
	else if(tecla == ESC)
		menu();
	else{
		system("CLS");
		printf("COMANDO NAO RECONHECIDO.\n\n\n");
		getch();
		menu();
	}
fclose(fp);
}


// =====================================================================================================================

void comprar(void){
	system("color 0B");
	abrirarq();
	int tecla;
	struct tm *Data;
	time_t segundos;
	time(&segundos);
	Data = localtime(&segundos);
	Produto c, p;
	system("CLS");
	printf("\t\t====== COMPRAR PRODUTOS ======\n\n");
	printf("Digite codigo do produto que deseja inserir em estoque.\n");
	scanf("%d", &c.cod);
	if(c.cod>0){
		p = buscaCodigo(c.cod);
		if(p.cod == c.cod){
			system("CLS");	
			printf("\t PRODUTO IDENTIFICADO. \n\n");
			printf("Codigo do produto: %d\n", p.cod);
			printf("Descricao: %s\n",p.descricao);
			printf("Preco unitario: R$%g\n", p.preco);
			printf("\n================================\n");
			
			
			
			printf("Digite a quantidade que deseja inserir em estoque.\n");
			
			scanf("%d",&c.estoque);
			if(c.estoque > 0){
				printf("Digite valor total desta compra.\n");
				scanf("%f", &c.compratotal);
				if(c.compratotal>=0){
					system("CLS");
					printf("Confirma que deseja salvar estes dados?\n\n");
					printf("Produto: %s, COD produto: %d. \n", p.descricao, p.cod);
					printf("Quantidade comprada: %d\n", c.estoque);
					printf("Valor total da compra: R$%g.\n", c.compratotal);
					printf("\n\nENTER = SIM");
					printf("\n\n\n\n*Pressione ENTER para prosseguir e salvar os dados, ao pressionar qualquer outra tecla, os dados nao serao salvos e a operacao sera abortada.");
					tecla = getch();
					if(tecla == ENTER){
						p.compdia = Data->tm_mday;
						p.compmes = Data->tm_mon+1;
						p.compano = Data->tm_year+1900;
						p.comphora = Data->tm_hour;
						p.compmin = Data->tm_min;
						p.compsec = Data->tm_sec;
						p.compratotal += c.compratotal;
						p.estoque += c.estoque;
						fseek(fp, -1 * sizeof(Produto), SEEK_CUR);
						fwrite(&p, sizeof(Produto), 1, fp);
						system("CLS");
						printf("\tCOMPRA EFETUADA");
						printf("\n\n\nVoce comprou %d unidades de <%s> por R$%g.", c.estoque, p.descricao,c.compratotal);
						printf("\nEm: %d/%d/%d as %d:%d:%d\n\n\n\n",p.compdia,p.compmes,p.compano,p.comphora,p.compmin,p.compsec);
						getch();
						fclose(fp);
						menu();
					}
					else{
						system("CLS");
						printf("Voce cancelou a compra do produto e sera redirecionado(a) para o menu principal.\n\n");
						getch();
						fclose(fp);
						menu();
					}
				}
				else{
					printf("Operacao abortada, o valor da compra deve ser maior ou igual a ZERO\n");
					getch();
					fclose(fp);
					menu();
				}
			}else{
				printf("Operacao abortada, a quantidade a ser inserida em estoque deve ser maior que ZERO\n");
				getch();
				fclose(fp);
				menu();
			}
			
		
				
		}
		else{
			printf("\n\nProduto nao encontrado na base de dados.\n\n");
			getch();
			fclose(fp);
			menu();
		}
	}
	else{
		printf("\n\nCodigo invalido\n\n");
		getch();
		fclose(fp);
		menu();
		
	}
	
} // encerra funcao comprar

void vender(void){
	system("color 0B");
	abrirarq();
	struct tm *Data;
	time_t segundos;
	time(&segundos);
	Data = localtime(&segundos);
	Produto c, p;
	int quantvenda;
	float vendaparcial = 0;
	int tecla;
	system("CLS");
	printf("\t\t====== VENDER PRODUTOS ======\n\n");
	printf("Digite codigo do produto que deseja vender.\n");
	scanf("%d", &c.cod);
	if(c.cod>0){
		p = buscaCodigo(c.cod);
		if(p.cod == c.cod){
			system("CLS");	
			printf("\t PRODUTO IDENTIFICADO. \n\n");
			printf("Codigo do produto: %d\n", p.cod);
			printf("Descricao: %s\n",p.descricao);
			printf("Preco unitario: R$%g\n", p.preco);
			printf("\n================================\n");
			printf("\nDigite quantidade de produtos que deseja vender: ");
			scanf("%d", &quantvenda);
			if(quantvenda>0){
				if(quantvenda > p.estoque){
					system("CLS");
					printf("Operacao abortada, quantidade em estoque insuficiente.\n\n\n");
					getch();
					fclose(fp);
					menu();
				}
				else{
					vendaparcial = quantvenda * p.preco;
					system("CLS");
					printf("Confirma que deseja salvar estes dados?\n\n");
					printf("Produto: %s, COD produto: %d. \n", p.descricao, p.cod);
					printf("Preco unitario: R$%.2f\n", p.preco);
					printf("Quantidade vendida: %d unidades\n", quantvenda);
					printf("Valor total da venda: R$%g.\n", vendaparcial);
					printf("\n\nENTER = SIM");
					printf("\n\n\n\n*Pressione ENTER para prosseguir e salvar os dados, ao pressionar qualquer outra tecla, os dados nao serao salvos e a operacao sera abortada.");
					tecla = getch();
					if(tecla == ENTER){
						p.venddia = Data->tm_mday;
						p.vendmes = Data->tm_mon+1;
						p.vendano = Data->tm_year+1900;
						p.vendhora = Data->tm_hour;
						p.vendmin = Data->tm_min;
						p.vendsec = Data->tm_sec;
						p.estoque -= quantvenda;
						p.vendatotal += vendaparcial;
						fseek(fp, -1 * sizeof(Produto), SEEK_CUR);
						fwrite(&p, sizeof(Produto), 1, fp);
						system("CLS");
						printf("\tVENDA EFETUADA");
						printf("\n\n\nVoce vendeu %d unidades de <%s> por R$%g.", quantvenda, p.descricao,vendaparcial);
						printf("\nEm: %d/%d/%d as %d:%d:%d\n\n\n\n",p.venddia,p.vendmes,p.vendano,p.vendhora,p.vendmin,p.vendsec);
						getch();
						fclose(fp);
						menu();
					}
					else{
						system("CLS");
						printf("Voce cancelou a compra do produto e sera redirecionado(a) para o menu principal.\n\n");
						getch();
						fclose(fp);
						menu();
					}
				} 
			}
			else{
				system("CLS");
				printf("Entre com valores maiores do que ZERO.\n\n");
				getch();
				fclose(fp);
				menu();
			}
		}
		else{
			printf("\nProduto nao encontrado na base de dados.\n\n");
			getch();
			fclose(fp);
			menu();
		}	
	}
	else{
		printf("\nCodigo invalido\n\n");
		getch();
		fclose(fp);
		menu();
	}
}


//=========================================================================================================================

void listarcadastrados(void){
	system("color 0B");
	abrirarq();
	system("CLS");
	printf("\t\t\t========= RELATORIO =========\n\n\n");
	Produto c;
	int quantcadastrados = 0;
	long int quantestoque = 0;
	float lucrototal;
	rewind(fp);
	while(!feof(fp)){	
		if(fread(&c,sizeof(Produto),1,fp))
			if(c.cod > 0){
				printf("\n--- Dados Cadastrais---\n");
				printf("Codigo do produto: %d\n", c.cod);
				printf("Nome do produto: %s\n", c.descricao);
				printf("Preco unitario: R$%g\n", c.preco);
				printf("Data da ultima alteracao do cadastro: %d/%d/%d as %d:%d:%d\n\n\n", c.caddia,c.cadmes,c.cadano,c.cadhora,c.cadmin,c.cadsec);
				printf("\n--- Informacoes sobre compra ---\n");
				if(c.compano == 0 && c.comphora == 0 ){
					printf("Este produto nunca foi comprado.\n\n\n");
				}
				else{
				printf("Foram investidos R$%g neste produto\t",c.compratotal);
				printf("Ultima compra em: %d/%d/%d as %d:%d:%d\n\n\n", c.compdia,c.compmes,c.compano, c.comphora,c.compmin,c.compsec);
				
				}
				printf("\n --- Informacoes sobre vendas--- \n");
				if(c.vendano == 0 && c.vendhora == 0){
					printf("Este produto nunca foi vendido.\n\n\n");
				}
				else{
					printf("Receita total gerada por este produto: R$%g\n", c.vendatotal);
					printf("Ultima venda em: %d/%d/%d as %d:%d:%d\n\n\n", c.venddia,c.vendmes,c.vendano,c.vendhora,c.vendmin,c.vendsec);
				}
				float lucro = c.vendatotal - c.compratotal;	
				lucrototal+= lucro;
				printf("\nLucro obtido com este produto: R$%g\n", lucro);
				printf("Quantidade em estoque: %d\n\n", c.estoque);
				quantcadastrados ++;
				quantestoque += c.estoque;
				printf("\n========================================================================\n\n\n");
			}
		}
	fclose(fp);
	if(quantcadastrados>0){	
	system("color 0B");
		printf("Quantidade de produtos cadastrados: %d produtos.\n", quantcadastrados);
		printf("Quantidade total em estoque: %d produtos.\n", quantestoque);
		if(lucrototal > 0){
				printf("Lucro total ate agora: R$%.2f\n\n\n", lucrototal);
		}else{
			printf("Prejuizo total ate agora: R$%.2f\n\n\n", -1* lucrototal);
		}
	
	}
	else{
		printf("Nao ha produtos cadastrados...\n\n\n\n\n\n\n");
	}

	getch();
	menu();
}
