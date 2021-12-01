#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
int n_jogadores,rodada=0,vez_jogador=0,troca=0;
#include "bib_war.h"



int main(){
	
	int escolha;
	
	
	setlocale(LC_ALL,"Portuguese");
	
	inij=cria();
	init=cria_terr();
	
	carrega_territorios();
	
	pre_jogo(0);
	
	passa_vez();
	
	while(1){
		escolha=menu();
		
		switch(escolha){
			case 1:
				ataque();
				break;
			case 2:
				remanejo();
				break;
			case 3:
				troca_tropas();
				break;
			case 4:
				checa_vitoria();
				break;
			case 5:
				passa_vez();
				break;
			case 6:
				regras();
				break;
			case 7:
				mostra_dados();
				break;
			case 8:
				exit(0);
		}
	}
	
	return 0;
	
}
