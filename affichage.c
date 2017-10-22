#include "librairies.h"
#include "affichage.h"

/*
void affichage(){// focntion affichant l'arrière plan amélioré a partir du document txt comprenant les caractere basiques.
	FILE* fichier=NULL;//creation du fichier qui contiendra le squelette de notre carte de circulation.
	char caractere;
	fichier =fopen("map.txt","r");// ouverture du fichier"squelette".
	if(fichier!=NULL){
		printf("\33[0;0H");//on place notre curseur en haut a gauche dans l'optique d'un affichage propre et claire.
		do{	
			caractere=fgetc(fichier);// nous recuperons les caracteres contenus dans le fichier "squelette".
			switch(caractere){//puis nous les remplaçont par les caracteres de notre choix lors de l'affichage sur le terminal.
				case '#': couleur("32");printf("♠️");couleur("0");break;
				case ':': couleur("33");printf("¦");couleur("0");break;
				case '~': couleur("46");printf("~");couleur("0");break;
			 	case 'g': printf("←");break;
				case 'd': printf("→");break;
				case 'h': printf("↑");break; 
				case 'b': printf("↓");break;
				case 'p': printf("◙");break; 			
				default: printf("%c",caractere);break;// ou nous reprenons le même caractere sinon. 
			}
		}while (caractere!=EOF);// tout cela se fait tant que la lecture du fichier n'est pas finie.
		fclose(fichier);// fermeture du fichier "squelette".
	}else{printf("probleme d'affichage, le fichier est vide\n");}// si le fichier "squelette" demandé n'existe pas.
}
*///ancien affichage

/**/
int** loadMap(){//66 et 194
	FILE * fichier=NULL;
	int ** tab=malloc(100*sizeof(int *));//on alloue l'espace au tableau
	char caractere;
	int condition=1;
	for (int i=0; i<100; i++){
		tab[i]=malloc(200*sizeof(int));
	}
	fichier=fopen("map.txt","r");
	
//fin de l'allocation
	for(int j=0;j<100;j++){
		for(int k=0; k<194; k++){
			caractere=fgetc(fichier);
			if(caractere==EOF){condition=0;break;}
			tab[j][k]=caractere;
		}
		if (condition==0){break;}	
	}
	fclose(fichier);
	return tab;
}

/**/
void affichageMap(int ** tab){
	for(int i=0; i<100; i++){
		for(int j=0; j<194; j++){
			printf("%c", tab[i][j]);
		}
	}
}
