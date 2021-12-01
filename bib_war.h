typedef struct{
	int codigo;				//estrutura que cont�m as informa��es sobre os territ�rios
	char nome[100];			
	int fronteiras[10];		//o conte�do do vetor fronteiras � o c�digo dos territ�rios que fazem fronteira com este territ�rio
}territorio;

typedef struct{				//estrutura com os dados dos jogadores
	char nome[25];
	char cor[10];
	int codigo;
	int territorios[42];	//o �ndice do vetor territ�rios � o c�digo do territ�rio-1
	int objetivo;			//logo, se o brasil tem c�digo 1, ele ocupa a posi��o 0
	int terr_ocup;			//o conte�do de cada posi��o no vetor � o n�mero de tropas que h� naquele territ�rio
	int tropas_totais;
}jogador;


typedef struct regt{		//lista encadeada de territ�rios
	territorio conteudo;	//o jogador n�o pode alterar estas informa��es
	struct regt *prox;
}reg_terr;

typedef struct regj{		//lista encadeada de jogadores
	jogador conteudo;
	struct regj *prox;
}reg_jog;

reg_jog *inij;
reg_terr *init;

void ler_string(char palavra[100], int tamanho){
	int i = 0;
	char c;
	c = getchar();
	while ((c != '\n') && (i < tamanho)) {
		palavra[i++] = c;
		c = getchar();
	}
	palavra[i] = '\0';
	if (c != '\n') {
		c = getchar();
		while ((c != '\n') && (c != EOF)) {
			c = getchar();
		}
	}
}

reg_jog *cria(void)
{
	reg_jog *start;

	start = (reg_jog *) malloc(sizeof(reg_jog));
	start->prox = NULL;
	return start;
}

void insere(jogador x)
{
	reg_jog *nova;

	nova = (reg_jog *) malloc(sizeof(reg_jog));
	nova->conteudo = x;
	nova->prox = inij->prox;
	inij->prox = nova;
}

void remova(jogador x)
{
	reg_jog *anterior, *proximo;
	anterior = inij;
	proximo = inij->prox;
	while ((proximo != NULL) && (proximo->conteudo.codigo != x.codigo)) {
		anterior = proximo;
		proximo = proximo->prox;
	}
	if (proximo != NULL) {
		anterior->prox = proximo->prox;
		free(proximo);
		printf("O ex�rcito de cor %s foi derrotado!\n",x.cor);
		system("pause");
	}
	
}

void salva_jogadores(){
	
	int c,j;
	FILE *file;
	reg_jog *pj;
	
	file = fopen("jogadores", "wb");
	if (!file){
		printf("Nao conseguiu criar o arquivo");
		system("pause");
		return;
	}
	
	fwrite(&n_jogadores,sizeof(int), 1, file);
	fwrite(&rodada,sizeof(int), 1, file);
	fwrite(&vez_jogador,sizeof(int), 1, file);
	fwrite(&troca,sizeof(int), 1, file);
	
	for (pj = inij->prox; pj != NULL; pj = pj->prox){
		fwrite(&pj->conteudo, sizeof(jogador), 1, file);	
	}
	fclose(file);

}

void carrega_jogadores(){
	
	int c,j;
	FILE *file;
	jogador temp;
	
	file = fopen("jogadores", "rb");
	if (!file){
		printf("N�o existem jogos salvos!\n");
		printf("Criando um novo jogo!\n");
		system("pause");
		pre_jogo(2);
		return;
	}
	
	fread(&n_jogadores, sizeof(int), 1, file);
	fread(&rodada, sizeof(int), 1, file);
	fread(&vez_jogador, sizeof(int), 1, file);
	fread(&troca, sizeof(int), 1, file);
	
	for (c=0;c<n_jogadores;c++){
		fread(&temp, sizeof(jogador), 1, file);
		insere(temp);		
	}
	fclose(file);
	
}

int mostra_territorios(){		//mostra os territ�rios que o jogador atual possui, juntamente com quantas tropas existem em cada um deles
	
	reg_terr *p2;
	reg_jog *p1;
	int c,j,escolha;
	
	for (p1 = inij->prox; (p1 != NULL && p1->conteudo.codigo!=vez_jogador); p1 = p1->prox);
	for(c=0;c<42;c++){
		if(p1->conteudo.territorios[c] != 0){
			for(p2 = init->prox;(p2 != NULL && p2->conteudo.codigo != c+1); p2 = p2->prox);
			printf("%d. %s:%d\n",c+1,p2->conteudo.nome,p1->conteudo.territorios[c]);
		}
	}
	printf("Digite o territ�rio:");
	scanf("%d",&escolha);
	
	return(escolha);
	
}

void pre_jogo(int aux){		//Configura o programa para o numero adequado de jogadores,l� os objetivos e territ�rios

	int c,escolha_terr,j;
	jogador temp;
	reg_terr *mostrar;
	
	printf("\t\t\tAssistente WAR\nAjustes pr�-jogo\n\n");
	
	while(aux != 1 && aux != 2){
	printf("Deseja carregar os dados da ultima partida?(1.Sim 2.N�o):");
	scanf("%d",&aux);
	}
	
	if(aux==1){
		carrega_jogadores();
	}
	else{
		do{
			printf("Numero de jogadores(m�nimo 3, m�ximo 6):");
			scanf("%d",&n_jogadores);
		}while(n_jogadores<3 || n_jogadores>6); 
		
		
		for(c=0;c<n_jogadores;c++){
			system("cls");
			fflush(stdin);
			
			printf("Nome do jogador %d:",c+1);
			ler_string(temp.nome,100);
			
			fflush(stdin);
			
			printf("Cor do jogador %d:",c+1);
			ler_string(temp.cor,100);
			
			escolha_terr=0;
			temp.terr_ocup=0;
			temp.tropas_totais=0;
			temp.codigo=c+1;
			
			for(j=0;j<44;j++){
				temp.territorios[j]=0;
				}
				
			for(mostrar = init->prox; mostrar != NULL; mostrar = mostrar->prox){
				printf("%d.%s\n",mostrar->conteudo.codigo,mostrar->conteudo.nome);	//Listar todos os pa�ses junto com seus c�digo no printf
			}
			printf("Territorios ocupados pelo jogador %d:",c+1);
				
			while(escolha_terr != 99){
				scanf("%d",&escolha_terr);
							
				if(escolha_terr != 99 && (escolha_terr<1 || escolha_terr>42)){
					printf("Territ�rio inv�lido!\nDigite novamente.\n");
				}
				else{
					temp.territorios[escolha_terr - 1]= 1;			//a posi��o foi decrementada em 1 para utilizar os pa�ses de 1 at� 42
				}													//ao contr�rio do vetor de territ�rios que vai de 0 at� 41
			}
			printf("Objetivo do jogador %d:\n",c+1);
			printf("1.Conquistar na totalidade a EUROPA, a OCEANIA e mais um terceiro.\n");
			printf("2.Conquistar na totalidade a ASIA e a AM�RICA DO SUL.\n");
			printf("3. Conquistar na totalidade a EUROPA, a AM�RICA DO SUL e mais um terceiro.\n");
			printf("4.Conquistar 18 TERRIT�RIOS e ocupar cada um deles com pelo menos dois ex�rcitos.\n");
			printf("5.Conquistar na totalidade a ASIA e a �FRICA.\n");
			printf("6.Conquistar na totalidade a AM�RICA DO NORTE e a �FRICA.\n");
			printf("7.Conquistar 24 TERRIT�RIOS � sua escolha.\n");
			printf("8.Conquistar na totalidade a AM�RICA DO NORTE e a OCEANIA.\n");
			printf("9.Destruir totalmente OS EX�RCITOS AZUIS.\n");
			printf("10.Destruir totalmente OS EX�RCITOS AMARELOS.\n");
			printf("11.Destruir totalmente OS EX�RCITOS VERMELHOS.\n");
			printf("12.Destruir totalmente OS EX�RCITOS PRETOS.\n");
			printf("13.Destruir totalmente OS EX�RCITOS BRANCO.\n");
			printf("14.Destruir totalmente OS EX�RCITOS VERDES.\n");
			scanf("%d",&temp.objetivo);
			
			for(j=0;j<42;j++){
				if(temp.territorios[j] != 0){
					temp.terr_ocup++;
					temp.tropas_totais += temp.territorios[j];
				}
			}
			
			insere(temp);
		}
		
		system("cls");
		}
}

int menu(void){			//a��es que o jogador atual pode executar
	
	system("cls");
	
	reg_jog *pm;
	int c = 0;
	
	for (pm = inij->prox; (pm != NULL && pm->conteudo.codigo!= vez_jogador); pm = pm->prox);
	
	do {
		printf("Vez do Jogador(a):%s\tRodada:%d\n",pm->conteudo.nome,rodada);
		printf("-- A��ES:\n");
		printf("\t 1. Atacar\n");
		printf("\t 2. Remanejo\n");
		printf("\t 3. Troca\n");
		printf("\t 4. Decretar Vit�ria\n");
		printf("\t 5. Passar a Vez\n");
		printf("\t 6. Ler as Regras\n");
		printf("\t 7. Mostrar os Dados\n");
		printf("\t 8. Sair do Jogo\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &c);
	} while (c <= 0 || c > 8);
	getchar();
	return c;
	
}

void regras(){		//busca e imprime as regras que est�o em um arquivo txt
	
	system("cls");
	
	
	FILE *arquivo;
	char linha[150];
	
	arquivo = fopen("regras.txt", "rt");
	while (fgets(linha, 120, arquivo) != NULL) {
		printf("%s", linha);
	}
	
	fclose(arquivo);
	
	system("pause");
}


void mostra_dados(){ 
	
	system("cls");
	reg_jog *dados;
	
	/*percorre a lista de jogadores at� o final, ou at� achar o jogador que tem aquele c�digo no seu perfil*/		
	/*depois de apontar para o jogador com este c�digo, imprime seus dados*/
	
	for (dados = inij->prox; (dados != NULL && dados->conteudo.codigo!= vez_jogador); dados = dados->prox);
	
	printf("--Dados do Jogador %d:\n", dados->conteudo.codigo);
	printf("\t Nome: %s\n", dados->conteudo.nome);
	printf("\t Cor: %s\n", dados->conteudo.cor);
	printf("\t Objetivo: %d\n", dados->conteudo.objetivo);
	printf("\t N�mero de territ�rios ocupados: %d\n", dados->conteudo.terr_ocup);
	printf("\t Total de Tropas: %d\n", dados->conteudo.tropas_totais);
	printf("\t ---------------\n");
		
	system("pause");
}



void insere_terr(territorio x)
{
	reg_terr *nova;

	nova = (reg_terr *) malloc(sizeof(reg_terr));
	nova->conteudo = x;
	nova->prox = init->prox;
	init->prox = nova;
}

reg_terr *cria_terr(void)
{
	reg_terr *start;

	start = (reg_terr *) malloc(sizeof(reg_terr));
	start->prox = NULL;
	return start;
}

int verifica_ocup(int ini,int fin,reg_jog *pj){		
	
	int flag=1,c;
	
	for(c=ini-1;c<fin;c++){						//testa para ver se um jogador tem todos os territ�rio em um intervalo de territ�rios
		if(pj->conteudo.territorios[c]==0)		//serve para testar se ele possui um continente inteiro
			flag=0;
	}
	
	return flag;
}

void distribui_tropas(int ini,int fin,int *d_uni,int *d,reg_jog*pj,int esco,int mover){	//fun��o gen�rica para ver qual dos mostradores ser� utilizado
	
	if(esco>=ini && esco<=fin){													//para distribuir as tropas, a prioridade � para os de continentes
			if(*d>0 && mover<=*d){														//espec�ficos
				*d=*d - mover;
				pj->conteudo.territorios[esco-1]+=mover;
				pj->conteudo.tropas_totais+=mover;
			}
			else{
				if(mover>*d && mover<=*d+*d_uni){
					*d_uni=*d_uni - (mover-*d);
					*d=0;
					pj->conteudo.territorios[esco-1]+=mover;
					pj->conteudo.tropas_totais+=mover;
				}
				else{
					if(mover>*d+*d_uni){
						printf("N�o � poss�vel mover esse n�mero de tropas!\n");
						system("pause");
						return;
					}
				}
			}
			
		salva_jogadores();
		}
	
}

void ordena(int d1,int d2,int d3,int n,int *dado){			//bubble sort para ordenar em ordem decrescente
	
	int c,ref,flag=1;
	int v[3];
	
	if(n==3){
		v[0]=d1;
		v[1]=d2;
		v[2]=d3;
	}
	if(n==2){
		v[0]=d1;
		v[1]=d2;
		v[2]=0;
	}
	if(n==1){
		printf("%d\t\n",d1);
		return;
	}
		
	while(flag==1){
		flag=0;
		for(c=0;c<n-1;c++){
			if(v[c+1]>v[c]){
				ref=v[c];
				v[c]=v[c+1];
				v[c+1]=ref;
				flag=1;
			}
		}
	}
	
	for(c=0;c<n;c++){
		printf("%d\t",v[c]);
		*(dado+c)=v[c];
	}
	printf("\n");
}

void ataque(){
	
	/*mostrar os territ�rios do jogador atual com as tropas ao lado e perguntar com qual ele deseja atacar, ap�s isso, mostrar os pa�ses
	que fazem fronteira mas n�o pertencem a este jogador e perguntar qual ele deseja atacar. Rolar o numero de dados adequado para ataque
	e defesa -igual ao numero de tropas no territ�rio mas no m�ximo 3, no caso do ataque a ultima tropa do territ�rio n�o pode atacar-
	depois de compara os dados -maior com maior, do meio com do meio, e menor com menor - que tiver o dado mais alto ganha,mas em caso de
	empate a defesa ganha, os dados s�o independentes. No final tira tropas de quem perdeu - pode acontecer simultaneamete no atacante e
	no atacado - e atualiza o arquivo de mem�ria.*/
	
	int dado_atk[3],dado_def[3],c,atacante,atacado=0,num1,num2,denovo=1,comp,flag,flag2,mover,ref;
	reg_terr *pt1,*pt2;
	reg_jog *pj1,*pj2;
	
	system("cls");
	
	printf("Com qual territ�rio voc� deseja atacar?\n");
	printf("Digite 99 para sair:\n");
	atacante=mostra_territorios();
	printf("\n\n");
	
	
	if(atacante == 99)
		return;
	
	if(atacante != 99){
		
		
		for(pj1 = inij->prox; (pj1 != NULL && pj1->conteudo.codigo!=vez_jogador); pj1 = pj1->prox);	//ponteiro pj1 aponta p/ jogador atual
		for(pt1 = init->prox; (pt1 != NULL && pt1->conteudo.codigo!=atacante); pt1 = pt1->prox);	//ponteiro pt1 aponta p/ territ�rio atacante
		
		flag=0;
		
		for(c=0;(c<10 && pt1->conteudo.fronteiras[c]!=99);c++){				/*procura as fronteiras do pa�s escolhido*/
			if(pj1->conteudo.territorios[pt1->conteudo.fronteiras[c]-1] ==0){ 		//se o jogador n�o possui este territ�rio
				for(pt2 = init->prox; (pt2 != NULL && pt2->conteudo.codigo!= pt1->conteudo.fronteiras[c]); pt2 = pt2->prox);			//aponta pro territ�rio da fronteira atual
				for(pj2 = inij->prox; (pj2 != NULL && pj2->conteudo.territorios[pt1->conteudo.fronteiras[c]-1]==0); pj2 = pj2->prox);	//aponta pro jogador que possui este territ�rio da fronteira atual
				if(pj2!=NULL){  //se existe outro jogador que n�o o atual nas fronteiras, ele mostra abaixo.
					flag=1;																																											
					printf("%d. %s:%d\n",pt2->conteudo.codigo,pt2->conteudo.nome,pj2->conteudo.territorios[pt1->conteudo.fronteiras[c]-1]);
				}
			}
		}
		
		printf("\n\n");
		
		if(flag==0){
			printf("N�o � possivel atacar com este territ�rio!\n");
			system("pause");
			ataque();
		}
		
		printf("Qual territ�rio voc� deseja atacar?\n");
		printf("Digite 99 para sair:\n");
		scanf("%d",&atacado);
		
		if(atacado==99)
			return;
		
		if(atacado != 99 && atacante != 99){
		
			while(atacante !=99 && atacado!=99 && denovo==1){
				if(pj1->conteudo.territorios[atacante-1]>3){		//caso o jogador tenha mais de 3 tropas, ataca com somente 3
					num1=3;
				}
				else{
					num1=pj1->conteudo.territorios[atacante-1]-1;		//se o atacante tiver 3 pe�as, s� pode atacar com 2 pois a ultima
					if(num1<1){											//n�o pode atacar
						printf("N�o � possivel atacar com este territ�rio!\n");
						system("pause");
						ataque();
					}
				}
				
				for(pj2 = inij->prox; (pj2 != NULL && pj2->conteudo.territorios[atacado-1] == 0); pj2 = pj2->prox);		//aponta p/ o jogador que possui o territ�rio atacado
				
				if(pj2->conteudo.territorios[atacado-1]>3){		//se tiver mais de 3 tropas se defende com 3
					num2=3;
				}
				else{
					num2=pj2->conteudo.territorios[atacado-1];	//se tiver menos, se defende com quantas tropas h� no territ�rio
				}
			
				srand(time(NULL)); 			
				for(c=0;c<num1;c++){				//vai gerar 1,2 ou 3 dados aleat�rio dependendo de quantas tropas est�o atacando
					dado_atk[c]=1 + (rand()%6);		//tem que fazer a mesma coisa para os dados de defesa
				}									//tamb�m precisa ordenar os dados de maior a menor pra poder comparar
				system("pause");									
				ordena(dado_atk[0],dado_atk[1],dado_atk[2],num1,&dado_atk);
				
				srand(time(NULL)); 
				for(c=0;c<num2;c++){					
					dado_def[c]=1 + (rand()%6);			
				}
				system("pause"); 
				ordena(dado_def[0],dado_def[1],dado_def[2],num2,&dado_def);
				
				if(num1>num2){
					comp=num2;
				}
				else{
					comp=num1;
				}
				
				for(c=0;c<comp;c++){
					if(dado_atk[c]>dado_def[c]){
						printf("Ganhou dado %d ",c+1);
						pj2->conteudo.territorios[atacado-1]--;
						pj2->conteudo.tropas_totais--;
						salva_jogadores();
						if(pj2->conteudo.territorios[atacado-1]==0){			//em caso de ganhar de todas as tropas que est�o defendendo
							printf("Territ�rio Conquistado!\n");				//o territ�rio � conquistado e o jogador atual deve mover
							do{													//alguma tropas para este territ�rio (de 1 at� quantas ele
								printf("Quantas tropas deseja mover?(1-%d):",num1);//usou para atacar)
								scanf("%d",&mover);
								if(mover<1 || mover>num1)
									printf("Valor Inv�lido!\n");
							}while(mover<1 || mover>num1);
							pj1->conteudo.territorios[atacado-1]+=mover;
							pj1->conteudo.territorios[atacante-1]-=mover;
							pj1->conteudo.terr_ocup++;
							pj2->conteudo.terr_ocup--;
							if(pj2->conteudo.terr_ocup == 0){
								remova(pj2->conteudo);
							}
							
							salva_jogadores();
							system("pause");
							ataque();
						}
					}
					else{
						printf("Perdeu dado %d ",c+1);
						pj1->conteudo.territorios[atacante-1]--;
						pj1->conteudo.tropas_totais--;
						salva_jogadores();
						if(pj1->conteudo.territorios[atacante-1] == 1){					//caso o jogador s� tenha 1 tropa, ele n�o pode 
							printf("N�o � mais poss�vel atacar com este territ�rio!\n");//atacar com este territ�rio
							system("pause");
							ataque();
						}
					}
				}
				
				printf("\n%d tropas restantes no territ�rio atacante!",pj1->conteudo.territorios[atacante-1]);
				printf("\n%d tropas restantes no territ�rio atacado",pj2->conteudo.territorios[atacado-1]);
				
				do{
					printf("Deseja continuar atacando o mesmo territ�rio? (1.Sim 2.N�o):");
					scanf("%d",&denovo);
				}while(denovo!=1 && denovo!=2);
				
				if(denovo == 2)
					ataque();
			}
			
			/*ap�s a compara��o j� deve atualizar o numero de tropas em cada territ�rio, mostrar na tela e carregar no arquivo de mem�ria*/
			/*junto com os dados de tropas em cada pa�s perguntar se deseja realizar o mesmo ataque, ou outro ataque*/
			
		}
	}
}

void remanejo(){
	
	/*Mostrar todos os territ�rios deste jogador com o numero de tropas ao lado para selecionar.
	Quando ele escolher um, mostrar para quais pa�ses ele pode mover baseado nas fronteiras, e perguntar
	o n�mero de tropas que ele quer mover baseado em quantas pe�as existem nesse territ�rio, feito isso atualizar o
	vetor territorios[] com os novos numeros*/
	
	int escolha;
	
	system("cls");
	
	int escolha1=0,escolha2,c,mover;
	reg_terr *pterr1,*pterr2;
	reg_jog *pjog1;
	
	while(escolha1!=99){
		printf("Digite o terri�rio do qual voc� deseja remover as tropas:\n");
		printf("Digite 99 para sair:\n");
		
		escolha1 = mostra_territorios();
		printf("\n\n");
		
		if(escolha1==99)
			return;
		
		if(escolha1 !=99){
			
			
			for(pjog1 = inij->prox; (pjog1 != NULL && pjog1->conteudo.codigo!=vez_jogador); pjog1 = pjog1->prox);		/*aponta pro jogador atual*/
			for(pterr1 = init->prox; (pterr1 != NULL && pterr1->conteudo.codigo!=escolha1); pterr1 = pterr1->prox);		/*aponta pro pa�s que ele escolheu*/
			
			for(c=0;(c<10 && pterr1->conteudo.fronteiras[c]!=99);c++){					/*procura as fronteiras do pa�s escolhido*/
				if(pjog1->conteudo.territorios[pterr1->conteudo.fronteiras[c]-1] !=0){	/*se o jogador atual possuir este territ�rio*/
					for(pterr2 = init->prox; (pterr2 != NULL && pterr2->conteudo.codigo!= pterr1->conteudo.fronteiras[c]); pterr2 = pterr2->prox);	/*aponta pra fronteira atual*/
					printf("%d. %s:%d\n",pterr2->conteudo.codigo,pterr2->conteudo.nome,pjog1->conteudo.territorios[pterr2->conteudo.codigo-1]);
				}
			}
			printf("\n\nEscolha o territ�rio para o qual voc� deseja mover as tropas:\n");
			printf("Digite 99 para sair:\n");
			scanf("%d",&escolha2);
			
			if(escolha2 == 99)
				return;
			
			if(escolha2 !=99 && escolha1 !=99){
			
				do{
				printf("Quantas tropas voc� deseja mover:\n");
				printf("Digite 99 para sair:\n");
				scanf("%d",&mover);
				if(mover>=pjog1->conteudo.territorios[escolha1-1]){
					printf("N�mero de tropas excede o permitido!\n");
				}
				if(mover == 99)
					return;
				}while(mover>=pjog1->conteudo.territorios[escolha1-1]);
			
				pjog1->conteudo.territorios[escolha2-1]+=mover;
				pjog1->conteudo.territorios[escolha1-1]-=mover;
				
				salva_jogadores();
			}
		}
	}
}
void troca_tropas(){
	
	/*limpar a tela e perguntar se realmente deseja fazer a troca, se sim perguntar se o jogador possui
	algumas das cartas utilizadas na troca para ganhar tropas b�nus e distribuir exatamente neste territorio.
	Ap�s isso, ganhar um n�mero de tropas equivalente com a troca e abrir uma nova tela para distribuir essas
	tropas nos pa�ses ocupados por este jogardor e atualizar o vetor territorios simultaneamente com as distribui��es
	*/
	
	
	int tropas=0,mover,escolha,certeza,possui,j=0,c;
	reg_jog *pj;
	
	system("cls");
	
	do{
		printf("Tem certeza de que deseja fazer a troca?(1.Sim 2.N�o)");
		scanf("%d",&certeza);
		if(certeza!=1 && certeza!=2)
			printf("Op��o inv�lida!\n");
	}while(certeza!=1 && certeza!=2);
	
	if(certeza==1){
		troca++;
		
		if(troca==1)
			tropas=4;
		if(troca==2)
			tropas=6;
		if(troca==3)
			tropas=8;
		if(troca==4)
			tropas=10;
		if(troca==5)
			tropas=12;
		if(troca==6)
			tropas=15;
		if(troca>6){
			for(c=1;c<troca-2;c++){
				tropas+=5;
			}
		}
			
			
		for(pj = inij->prox; (pj != NULL && pj->conteudo.codigo!=vez_jogador); pj = pj->prox);
		
		do{
			do{
				printf("Voc� tem algum dos territ�rios utilizado para fazer a troca?(1.Sim 2.N�o)");
				scanf("%d",&possui);
			}while(possui!=1 && possui!=2);
		
			if(possui==1){
				j++;
				printf("Qual dos territ�rios voc� tem?\n\n");
				escolha=mostra_territorios();
				
				printf("\nColoque mais 2 tropas neste territ�rio!\n\n");
				
				pj->conteudo.territorios[escolha-1]+=2;
				pj->conteudo.tropas_totais+=2;
				
				salva_jogadores();
				
				system("pause");
			}
		}while(possui==1 && j<3);
		
		while(tropas>0){
			system("cls");
			printf("Escolha o territ�rio para o qual deseja mover as tropas\n");
			printf("Tropas para distribuir:%d\n\n",tropas);
				
			escolha=mostra_territorios();
				
			do{
				printf("Digite quantas tropas deseja colocar:");
				scanf("%d",&mover);
				if(mover>tropas)
					printf("N�o � poss�vel mover esse n�mero de tropas!\n");
			}while(mover>tropas || mover<=0);
																
			tropas -= mover;
			pj->conteudo.territorios[escolha-1]+=mover;
			pj->conteudo.tropas_totais+=mover;
		
			salva_jogadores();
		}
	}
}

void checa_vitoria(){
	
	/*mostra o objetivo referente ao cadastrado no perfil do jogador, caso o jogador j� tenha alcan�ado ele pode decretar vit�ria*/
	
	reg_jog *vit;
	int decreto;
	
	for(vit = inij->prox; (vit != NULL && vit->conteudo.codigo!=vez_jogador); vit = vit->prox);
	
	switch(vit->conteudo.objetivo){
		case 1:
			printf("Conquistar na totalidade a EUROPA, a OCEANIA e mais um terceiro.\n");
			break;
		case 2:
			printf("Conquistar na totalidade a ASIA e a AM�RICA DO SUL.\n");
			break;
		case 3:
			printf("Conquistar na totalidade a EUROPA, a AM�RICA DO SUL e mais um terceiro.\n");
			break;
		case 4:
			printf("Conquistar 18 TERRIT�RIOS e ocupar cada um deles com pelo menos dois ex�rcitos.\n");
			break;
		case 5:
			printf("Conquistar na totalidade a ASIA e a �FRICA.\n");
			break;
		case 6:
			printf("Conquistar na totalidade a AM�RICA DO NORTE e a �FRICA.\n");
			break;
		case 7:
			printf("Conquistar 24 TERRIT�RIOS � sua escolha.\n");
			break;
		case 8:
			printf("Conquistar na totalidade a AM�RICA DO NORTE e a OCEANIA.\n");
			break;
		case 9:
			printf("Destruir totalmente OS EX�RCITOS AZUIS.\n");
			break;
		case 10:
			printf("Destruir totalmente OS EX�RCITOS AMARELOS.\n");
			break;
		case 11:
			printf("Destruir totalmente OS EX�RCITOS VERMELHOS.\n");
			break;
		case 12:
			printf("Destruir totalmente OS EX�RCITOS PRETOS.\n");
			break;
		case 13:
			printf("Destruir totalmente OS EX�RCITOS BRANCO.\n");
			break;
		case 14:
			printf("Destruir totalmente OS EX�RCITOS VERDES.\n");	
	}
	
	do{
	printf("Decretar vit�ria?(1.Sim 2.N�o):");
	scanf("%d",&decreto);
	if(decreto!=1 && decreto!=2)
		printf("Op��o inv�lida!\n");
	}
	while(decreto!=1 && decreto!=2);
	
	if(decreto == 1){
		printf("Parab�ns, voc� ganhou!\n");
		system("pause");
		exit(0);
	}
	
}



void passa_vez(){
	
	
	
	/*atualizar a vari�vel vez_jogador, limpar a tela e fazer o c�lculo de quantas tropas o novo jogador ir� ganhar, baseado
	no n�mero de territ�rios que ele tem ocupado. Mostrar na tela todos os territ�rios ocupados com o numero de tropas ao lado
	e um contador de tropas livres para distribuir. Testar se o jogador possui algum continente e fazer outros contadores de tropas
	mas dedicados a um continente. Quando todos os contadores chegarem a zero abre o menu de jogo.*/
	
	int d_uni=0,d_ames=0,d_amen=0,d_eur=0,d_afr=0,d_asi=0,d_oce=0;
	int mov,flag,total=1,esc;
	reg_jog *pj;
	
	
	vez_jogador++;
	
	if(vez_jogador==0)
		vez_jogador=1;
	
	if(vez_jogador>n_jogadores){
		vez_jogador=1;
		rodada++;
	}
	
	for(pj = inij->prox; (pj != NULL && pj->conteudo.codigo!=vez_jogador); pj = pj->prox);
	
	d_uni=pj->conteudo.terr_ocup/2;
	if(d_uni<3)
		d_uni=3;
	
	flag=verifica_ocup(1,4,pj);		//testa pra ver se o jogador atual possui toda a Am�rica do Sul
	if(flag==1)
		d_ames=2;
	flag=verifica_ocup(5,13,pj);	//testa pra ver se o jogador atual possui toda a Am�rica do Norte
	if(flag==1)
		d_amen=5;
	flag=verifica_ocup(14,20,pj);	//testa pra ver se o jogador atual possui toda a Europa
	if(flag==1)
		d_eur=5;
	flag=verifica_ocup(21,26,pj);	//testa pra ver se o jogador atual possui toda a Africa
	if(flag==1)
		d_afr=3;
	flag=verifica_ocup(27,38,pj);	//testa pra ver se o jogador atual possui toda a �sia
	if(flag==1)
		d_asi=7;
	flag=verifica_ocup(39,42,pj);	//testa pra ver se o jogador atual possui toda a Oceania
	if(flag==1)
		d_oce=2;
	
	
	system("cls");
	
	while(total>0){
		system("cls");
		
		printf("Tropas para distribuir em qualquer territ�rio ocupado:%d\n",d_uni);
		printf("Tropas para distribuir na Am�rica do Sul:%d\n",d_ames);
		printf("Tropas para distribuir na Am�rica do Norte:%d\n",d_amen);
		printf("Tropas para distribuir na Europa:%d\n",d_eur);
		printf("Tropas para distribuir na Africa:%d\n",d_afr);
		printf("Tropas para distribuir na �sia:%d\n",d_asi);
		printf("Tropas para distribuir Oceania:%d\n",d_oce);
		printf("--------------------------------------\n ");
		printf("Escolha o territ�rio para o qual deseja mover as tropas\n\n");
		
		esc=mostra_territorios();
		
		printf("Digite quantas tropas deseja colocar:");
		scanf("%d",&mov);
		
		distribui_tropas(1,4,&d_uni,&d_ames,pj,esc,mov);
		distribui_tropas(5,13,&d_uni,&d_amen,pj,esc,mov);
		distribui_tropas(14,20,&d_uni,&d_eur,pj,esc,mov);
		distribui_tropas(21,26,&d_uni,&d_afr,pj,esc,mov);
		distribui_tropas(27,38,&d_uni,&d_asi,pj,esc,mov);
		distribui_tropas(39,42,&d_uni,&d_oce,pj,esc,mov);
		
		
		total=d_uni+d_ames+d_amen+d_eur+d_afr+d_asi+d_oce;
	}
}

void carrega_territorios(){
	
	int c,j;
	FILE *file;
	territorio temp;
	
	file = fopen("territorios", "rb");
	if (!file){
		printf("Nao conseguiu criar o arquivo");
		system("pause");
		return;
	}
	

	for (c=0;c<42;c++){
		fread(&temp, sizeof(territorio), 1, file);
		insere_terr(temp);		
	}
	fclose(file);
	
}



