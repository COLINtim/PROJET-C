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
				//herbe
				case '#': couleur("45");printf("♨");couleur("0");break;
				//eau
				case '~': couleur("46");printf(" ");couleur("0");break;
				//caracteres liés a la route
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
				case 'n': printf("⛱");break;
				//caracters spéciaux:
				case 'k': printf("═");break;
				case 'l': printf("╚");break;
				case 'm': printf("║");break;
				case 'o': printf("╝");break;
				case 'q': printf("╗");break;
				case 't': printf("╔");break;
				case 'v': printf("─");break;
				case 'w': printf("│");break;
				case 'z': printf("┐");break;
				case 'a': printf("┌");break;
				case 'c': printf("┘");break;
				case 'e': printf("└");break;
				case 'f': printf("╮");break;
				case 'i': printf("╯");break;
				case 'j': printf("╰");break;
				case '!': printf("╭");break;
				case '%': printf("▒");break;
				case '*': printf("▓");break;
				//case 'H': couleur("32");printf("▓");couleur("0");break;
				//caracteres par default
				default: printf("%c",caractere);break;
			}
		}while (caractere!=EOF);
		fclose(fichier);
	}else{printf("probleme d'affichage, le fichier est vide\n");}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void affichageMenu(char * nomDuFichier){
	FILE * fichier = NULL;
	char caractere;
	fichier =fopen(nomDuFichier,"r");
	if(fichier!=NULL){
		printf("\033[0;0H");
		do{	
			caractere=fgetc(fichier);
			switch(caractere){

				/*case 'k': couleur("48;5;15");couleur("38;5;0");printf("═");couleur("0");break;
				case 'l': couleur("48;5;15");couleur("38;5;0");printf("╚");couleur("0");break;
				case 'm': couleur("48;5;15");couleur("38;5;0");printf("║");couleur("0");break;
				case 'o': couleur("48;5;15");couleur("38;5;0");printf("╝");couleur("0");break;
				case 'q': couleur("48;5;15");couleur("38;5;0");printf("╗");couleur("0");break;
				case 't': couleur("48;5;15");couleur("38;5;0");printf("╔");couleur("0");break;
				*/
				case 'v': couleur("38;5;4");printf("─");couleur("0");break;
				case 'w': couleur("38;5;4");printf("│");couleur("0");break;
				case 'h': couleur("38;5;4");couleur("32");printf("↑");couleur("0");break;
				case 'b': couleur("38;5;4");couleur("32");printf("↓");couleur("0");break;
				
				//case 'e': printf("└");break;
				case 'f': couleur("38;5;4");printf("╮");couleur("0");break;
				case 'i': couleur("38;5;4");printf("╯");couleur("0");break;
				case 'j': couleur("38;5;4");printf("╰");couleur("0");break;
				case '!': couleur("38;5;4");printf("╭");couleur("0");break;
				case '%': printf("▒");break;
				case '*': printf("▓");break;
				case 'D': couleur("38;5;208");printf("S");couleur("0");break;
				case 'S': couleur("38;5;21");printf("S");couleur("0");break;
				case 'P': printf(" ");couleur("0");break;
				case 'R': couleur("38;5;46");printf("$");couleur("0");break;
				case 'K': couleur("38;5;51");printf("$");couleur("0");break;
				case '$': couleur("38;5;196");printf("$");couleur("0");break;
				//carateres menus
				//case 'M': couleur("32");printf("🌼");couleur("0");break;//ansi color sur wikipedia ##############
				/*case 'm': couleur("1;41");printf("▓");couleur("0");break;
				case 'E': couleur("42");printf(" ");couleur("0");break;
				case 'e': couleur("1;42");printf("▓");couleur("0");break;
				case 'N': couleur("43");printf(" ");couleur("0");break;
				case 'n': couleur("1;43");printf("▓");couleur("0");break;
				case 'U': couleur("44");printf(" ");couleur("0");break;
				case 'u': couleur("1;44");printf("▓");couleur("0");break;*/
				//caracteres par default
				default: couleur("38;5;208");printf("%c",caractere);couleur("0");break;
			}
		}while(caractere!=EOF);
		fclose(fichier);
	}
}