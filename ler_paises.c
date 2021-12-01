#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
int n_jogadores,rodada=0,vez_jogador=0,troca=0;
#include "bib_war.h"



int main(){
	
	int c,j,escolha,terr;
	reg_terr *init;
	territorio temp;
	FILE *file;
	
	init=cria_terr();
	
	file = fopen("territorios", "rb");
	if (!file){
		printf("Nao conseguiu criar o arquivo");
		system("pause");
		return 1;
	}
	
	reg_terr *p;
	
	for (c=0;c<42;c++){
		fread(&temp, sizeof(territorio), 1, file);
		insere_terr(temp,init);		
	}
	fclose(file);
		
	for (p = init->prox; p != NULL; p = p->prox){
		printf("\t Nome: %s\n", p->conteudo.nome);
		printf("\t Codigo: %d\n", p->conteudo.codigo);
		printf("\t Fronteiras:");
		for(j=0;(j<10 && p->conteudo.fronteiras[j] !=99); j++){
			printf("%d ",p->conteudo.fronteiras[j]);
		}
		printf("\n\n");
	}
	
/*	do{
	printf("Deseja mudar algum territorio:(1.sim 2.nao)");
	scanf("%d",&escolha);
	
	j=0;
	
	if(escolha==1){
		printf("Digite o codigo do territorio:");
		scanf("%d",&terr);
	for(p = init->prox;(p != NULL && p->conteudo.codigo != terr); p = p->prox);
	
	fflush(stdin);
		
		printf("Nome do pais:");
		ler_string(p->conteudo.nome,100);
		
		do{
			printf("Fronteira %d:",j+1);
			scanf("%d",&p->conteudo.fronteiras[j]);
			j++;
		}while(p->conteudo.fronteiras[j-1] != 99);
	
}
}while(escolha==1);
	
	file = fopen("territorios", "wb");
	if (!file){
		printf("Nao conseguiu criar o arquivo");
		system("pause");
		return 1;
	}
	
	for (p = init->prox; p != NULL; p = p->prox){
		fwrite(&p->conteudo, sizeof(territorio), 1, file);
		printf("Gravado %s \n", p->conteudo.nome);		
	}
	printf("Gravado!!\n");
	fclose(file);
	printf("\n");
	system("pause");*/
	
	return 0;
}
