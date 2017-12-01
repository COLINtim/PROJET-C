#include "librairies.h"
#include "helicopteres.h"

void helicoptereSpawner(int posX, int posY,char axe, HelicoptereList** ListeDesHelicopteres)
{
	Helicoptere* Helico=malloc(sizeof(Helicoptere));
	Helico->posX = posX;
	Helico->posY = posY;
	Helico->axe = axe;
	appendHelicoptereList(ListeDesHelicopteres, Helico);
}

void appendHelicoptereList(HelicoptereList** ListeDesHelicopteres, Helicoptere* Helico)
{
	HelicoptereList *element;
	element = calloc(1,sizeof(*element));
	element->Helicoptere = Helico;
	element->next = *ListeDesHelicopteres;
	*ListeDesHelicopteres = element;
}

HelicoptereList* helicoptereEater(HelicoptereList **List, Helicoptere* Helicoptere)
{
	HelicoptereList* PointeurCourant;
	HelicoptereList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
	{
		if (PointeurCourant->Helicoptere == Helicoptere)
		{
			if (PointeurPrecedent == NULL)
			{ 	
				*List = PointeurCourant->next;
			} 
			else
			{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
			}
		HelicoptereList* ptrToReturn = PointeurCourant->next;
		free(PointeurCourant);break;
		return ptrToReturn;
		}
	}
	return NULL;
}

void affichageHelicoptere(Helicoptere* Helico)
{
	couleur("37");
	printf("\033[%d;%dH🚁",Helico->posX,Helico->posY); 

}

Position* positionFutureHelicoptere(Helicoptere* Helico) // Commentaire sur le codage des axes en bas de la fonction
{
	Position* Position = malloc(sizeof(Position));
	Position->posX = Helico->posX;
	Position->posY = Helico->posY;
	int i;
	i=rand()%2;
	switch(Helico->axe) 
	{
		case 'u': 
			Position->posX=(Helico->posX)-1;
			if(i%2 == 0)
			{
				Helico->axe = 'a';
			}
			else
			{
				Helico->axe = 'b';
			}
			return Position;
		case 'r': 
			Position->posY=(Helico->posY)+1;
			if(i%2 == 0)
			{
				Helico->axe = 'a';
			}
			else
			{
				Helico->axe = 'c';
			}
			return Position;
		case 'l': 
			Position->posY=(Helico->posY)-1;
			if(i%2 == 0)
			{
				Helico->axe = 'b';
			}
			else
			{
				Helico->axe = 'e';
			}
			return Position;
		case 'd': 
			Position->posX=(Helico->posX)+1;
			if(i%2 == 0)
			{
				Helico->axe = 'e';
			}
			else
			{
				Helico->axe = 'c';
			}
			return Position;
		case 'a': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)-1;	
			}
			else
			{
				Position->posX=Helico->posX;
				Position->posY=(Helico->posY)+1;
			}
			return Position;
		case 'b': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)-1;
			}
			else
			{
				Position->posY=(Helico->posY)-1;
			}
			return Position;
		case 'c': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)+1;
			}
			else
			{
				Position->posY=(Helico->posY)+1;
			}
			return Position;
		case 'e': 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)+1;
			}
			else
			{
				Position->posY=(Helico->posY)-1;
			}
			return Position;
		default:
			return Position;
	}
}

//Helico trajectoire diagonale en moyenne : u=UP ; r=RIGHT ; l=LEFT ; d=DOWN ; a=UP&&RIGHT ; b=UP&&LEFT ; c=DOWN&&RIGHT ; e=DOWN&&LEFT

void roulementHelicopteresPosition(char** MatriceMap, char** MatriceDecision, HelicoptereList** ListeDesHelicopteres)
{
	HelicoptereList *tmp;
	tmp = *ListeDesHelicopteres;
	while (tmp != NULL)
		{	
			Position* NextPosition = positionFutureHelicoptere(tmp->Helicoptere); // Afin de free plus tard
			if (NextPosition->posX==1 || NextPosition->posY==1 || NextPosition->posX==66 || NextPosition->posY==194)
			{
				affichagePartielHelicoptere(MatriceMap, tmp->Helicoptere);
				tmp->Helicoptere->posX = NextPosition->posX;
				tmp->Helicoptere->posY = NextPosition->posY;
				//affichageHelicoptere(tmp->Helicoptere);
				tmp = helicoptereEater(ListeDesHelicopteres, tmp->Helicoptere);
			}
			else
			{
			affichagePartielHelicoptere(MatriceMap, tmp->Helicoptere);
			tmp->Helicoptere->posX = NextPosition->posX;
			tmp->Helicoptere->posY = NextPosition->posY;
			affichageHelicoptere(tmp->Helicoptere);
			tmp = tmp->next;
			}
		free(NextPosition);
		}
}

void affichagePartielHelicoptere(char ** MatriceMap, Helicoptere * Helicoptere)
{

	char caractere;;
	
	for(int i = 0; i<2; i++){

		caractere = MatriceMap[Helicoptere->posX][Helicoptere->posY+i];
		printf("\033[%d;%dH",Helicoptere->posX,Helicoptere->posY+i);
		
		switch(caractere){
				//herbe
				case '#': couleur("48;5;22");couleur("38;5;46");printf("♨");couleur("0");break;
				case '?': couleur("48;5;22");printf(" ");couleur("0");break;
				//eau
				case '~': couleur("46");printf(" ");couleur("0");break;
				case '$': couleur("48;5;45");printf(" ");couleur("0");break;
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
				case 'p': printf(" ");break;
				case 'Z': couleur("48;5;52");printf(" ");couleur("0");break;
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
				case '%': couleur("38;5;228");printf("▒");couleur("0");break;
				case '*': printf("▓");break;
				//caracteres par default
				default: printf("%c",caractere);break;
		}
	}			
}