#include "librairies.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char key_pressed(){
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {
		ungetc(c, stdin); result = getchar();
	}
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affichageMap(){
	FILE* fichier=NULL;
	char caractere;
	fichier =fopen("map.txt","r");
	if(fichier!=NULL){
		printf("\033[0;0H");
		do{	
			caractere=fgetc(fichier);
			switch(caractere){
				case '#': couleur("45");printf("♨");couleur("0");break;
				
				case '~': couleur("46");printf(" ");couleur("0");break;
				case 's': couleur("32");printf("¤");couleur("0");break;
				case '|': couleur("32");printf("|");couleur("0");break;
				case 'r': couleur("32");printf("─");couleur("0");break;
				case 'u': couleur("32");printf("│");couleur("0");break;
				case 'x': couleur("34");printf(" ");couleur("0");break;
				case 'y': couleur("32");printf("☰");couleur("0");break;
				
			 	case 'g': couleur("32");printf("←");couleur("0");break;
				case 'd': couleur("32");printf("→");couleur("0");break;
				case 'h': couleur("32");printf("↑");couleur("0");break;
				case 'b': couleur("32");printf("↓");couleur("0");break;
				case 'p': couleur("44");printf(" ");couleur("0");break;
				case 'n': printf("⛱️");break;
		
				default: printf("%c",caractere);break;
			}
		}while (caractere!=EOF);
		fclose(fichier);
	}else{printf("probleme d'affichage, le fichier est vide\n");}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void affichageTramwayHaut(Tramway T){
	int calcul=0;
	if (T[0]='fin'){
	}else{	
		if (T[0].posX<=118){
			for (int i=0; i<8; i++){
				printf("\033[%d;%dH%c",T[i].posY,T[i].posX,T[i].custom);
			}
		}	
		calcul = T[0].posX-118;
		printf("\033[%d;%dH%c",T[0].posY+calcul,118,T[0].custom);
		affichageTramwayHaut(T+1);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affichageTramwayBas(Tramway T){
	int calcul=0;
	if (T[0]='fin'){
	}else{	
		if (T[0].posX<=114){
			for (int i=0; i<8; i++){
				printf("\033[%d;%dH%c",T[i].posY,T[i].posX,T[i].custom);
			}
		}	
		calcul = T[0].posX-114;
		printf("\033[%d;%dH%c",T[0].posY+calcul,114,T[0].custom);
		affichageTramwayHaut(T+1);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affichagePieton(Pieton P){
	printf("\033[%d;%dH%c",P.y,P.x,P.custom);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affichageComplet(Tramway ** TS,Vehicule ** VS, Pieton ** TS){
	affichageMap();
	for(int j=0; j<longueur.VS; j++){.
		affichageVoiture(VS[j]);
	}
	for(int i=0; i<longueur.TS; i++){	
		affichageTram(TS[i]);
	}
	for(int k=0; k<longueur.PS; k++){
		affichagePieton(PS[k]);
	}
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void initVehicule(Vehicule * V){

	srand(time(NULL));
	
	switch(rand()%6){
		case 0:V->custom[0]='🚘';
		case 1:V->custom[0]='🚔';
		case 2:V->custom[0]='🚍';
		case 3:V->custom[0]='🚘';
		case 4:V->custom[0]='🚖';
		default :V->custom[0]='🚘';
	}
	switch(rand()%6){
		case 0:V->custom[1]='v';
		case 1:V->custom[1]='r';
		case 2:V->custom[1]='o';
		case 3:V->custom[1]='b';
		case 4:V->custom[1]='s';
		default :V->custom[1]='b';
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void intiBoat(Boat * B){

	srand(time(NULL));
	
	switch(rand()%6){
		case 0:B->custom[0]='⛴';
		case 1:B->custom[0]='🛳';
		case 2:B->custom[0]='🛥';
		case 3:B->custom[0]='⛵️';
		case 4:B->custom[0]='🍩';
		default :B->custom[0]='⛴';
	}
	switch(rand()%6){
		case 0:B->custom[1]='v';
		case 1:B->custom[1]='r';
		case 2:B->custom[1]='o';
		case 3:B->custom[1]='b';
		case 4:B->custom[1]='s';
		default :B->custom[1]='b';
	}
}
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

