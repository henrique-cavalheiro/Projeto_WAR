#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
int n_jogadores,rodada=0,vez_jogador=0,troca=0;
#include "bib_war.h"



int main(){
	
	int c,j;
	reg_terr *ini;
	territorio temp;
	FILE *file;
	
	ini=cria_terr();
	
	for(c=0;c<42;c++){
		j=0;
		
		printf("Codigo do pais:");
		scanf("%d",&temp.codigo);
		
		fflush(stdin);
		
		printf("Nome do pais:");
		ler_string(temp.nome,100);
		
		do{
			printf("Fronteira %d:",j+1);
			scanf("%d",&temp.fronteiras[j]);
			j++;
		}while(temp.fronteiras[j-1] != 99); //99 é o valor usado também para parar de ler os territórios
		
		insere_terr(temp,ini);
	}
	
	reg_terr *p;
	
	for (p = ini->prox; p != NULL; p = p->prox){
		printf("\t Nome: %s\n", p->conteudo.nome);
		printf("\t Codigo: %d\n", p->conteudo.codigo);
	}
		

	
	file = fopen("territorios", "wb");
	if (!file){
		printf("Nao conseguiu criar o arquivo");
		system("pause");
		return 1;
	}
	
	for (p = ini->prox; p != NULL; p = p->prox){
		fwrite(&p->conteudo, sizeof(territorio), 1, file);
		printf("Gravado %s \n", p->conteudo.nome);		
	}
	printf("Gravado!!\n");
	fclose(file);
	printf("\n");
	system("pause");
	
	return 0;
	
}
