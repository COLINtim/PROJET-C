#include "librairies.h"
#include "pietons.h"

void pietonSpawner(int posX, int posY, Direction Direction, PietonList** ListeDesPietons)
{
		Pieton* Pieton=malloc(sizeof(Pieton));
		Pieton->posX = posX;
		Pieton->posY = posY;
		Pieton->CaseDecision = 'S';
		Pieton->Direction = Direction;
		appendPietonList(ListeDesPietons, Pieton);
}

void appendPietonList(PietonList** ListeDesPietons, Pieton* Pieton)
{
	PietonList *element;
	element = calloc(1,sizeof(*element));
	element->Pieton = Pieton;
	element->next = *ListeDesPietons;
	*ListeDesPietons = element;
}

PietonList* pietonEater(PietonList **List, Pieton* Pieton)
{
	PietonList* PointeurCourant;
	PietonList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
		{
			if (PointeurCourant->Pieton == Pieton)
			{
				if (PointeurPrecedent == NULL)
				{ 	
					*List = PointeurCourant->next;
				} 
				else
				{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
				}
			PietonList* ptrToReturn = PointeurCourant->next;
			free(PointeurCourant);break;
			return ptrToReturn;
			}
		}
	return NULL;
}

void affichagePieton(Pieton* Pieton)
{
		couleur("37");
		printf("\033[%d;%dH🚶",Pieton->posX,Pieton->posY);

}

void affichagePartielPieton(char ** MatriceMap, Pieton* Pieton)
{
	char caractere;
	char caractere2;

		caractere = MatriceMap[Pieton->posX][Pieton->posY];
		caractere2 = MatriceMap[Pieton->posX][Pieton->posY+1];

		printf("\033[%d;%dH",Pieton->posX,Pieton->posY);
		
		switch(caractere){
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
				//caracteres spéciaux:
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
				case 'H': couleur("32");printf("▓");couleur("0");break;
				//caracteres par default
				default: printf("%c",caractere);break;
		}		

		printf("\033[%d;%dH",Pieton->posX,Pieton->posY+1);

		switch(caractere2)
		{
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
				//caracteres spéciaux:
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
				case 'H': couleur("32");printf("▓");couleur("0");break;
				//caracteres par default
				default: printf("%c",caractere2);break;
			}
}

void setNewPietonDirection(Pieton* Pieton, char ** MatriceDecision, PietonList *ListeDesPietons)
{
	switch(MatriceDecision[Pieton->posX][Pieton->posY])
	{
		case 'd':
			Pieton->Direction = EST; 
			break;
		case 'g':
			Pieton->Direction = OUEST; 
			break;
		case 'h':
			Pieton->Direction = NORD; 
			break;
		case 'b':
			Pieton->Direction = SUD; 
	}

}

Position* positionFuturePieton(Pieton* Pieton)
{
	Position* Position = malloc(sizeof(Position));
	Position->posX = Pieton->posX;
	Position->posY = Pieton->posY;
	switch(Pieton->Direction)
	{
		case NORD: 
			Position->posX = Position->posX -1;
			return Position;
		case SUD:
			Position->posX = Position->posX +1;
			return Position;
		case EST:
			Position->posY = Position->posY +1;
			return Position;
		case OUEST:
			Position->posY = Position->posY -1;
			return Position;
		default:
			return Position;
	}
}

int ObstaclePieton(char ** MatriceDecision, int i, int j)
{
	if(MatriceDecision[i][j] == 'f' || MatriceDecision[i][j] == 'P')
	{
		return 1;
	}
	else if(MatriceDecision[i][j] == 'E')
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void roulementPietonsPosition(char ** MatriceMap, char** MatriceDecision, PietonList** ListeDesPietons)
{
PietonList *tmp;
tmp = *ListeDesPietons;
while (tmp != NULL)
	{	
		Position* NextPosition = positionFuturePieton(tmp->Pieton); // Afin de free plus tard
		if (ObstaclePieton(MatriceDecision, NextPosition->posX, NextPosition->posY) == 2)
		{
			affichagePartielPieton(MatriceMap, tmp->Pieton);
			tmp->Pieton->posX = NextPosition->posX;
			tmp->Pieton->posY = NextPosition->posY;
			affichagePieton(tmp->Pieton);
			tmp = pietonEater(ListeDesPietons, tmp->Pieton);
		}
		else if (ObstaclePieton(MatriceDecision, NextPosition->posX, NextPosition->posY) == 1)
		{
			affichagePartielPieton(MatriceMap, tmp->Pieton);
			affichagePieton(tmp->Pieton);
			tmp = tmp->next;
		}
		else
		{
			if(tmp->Pieton->CaseDecision == 'D')
			{
					affichagePartielPieton(MatriceMap, tmp->Pieton);
					tmp->Pieton->posX = NextPosition->posX;
					tmp->Pieton->posY = NextPosition->posY;
					affichagePieton(tmp->Pieton);
					tmp->Pieton->CaseDecision = 'F'; //Passage en mode fantome
					tmp = tmp->next;
			}
			else if(tmp->Pieton->CaseDecision == 'F') //Mode fantome
			{
				tmp->Pieton->posX = NextPosition->posX;
				tmp->Pieton->posY = NextPosition->posY;
				if(MatriceDecision[NextPosition->posX][NextPosition->posY] == 'A')
				{
					tmp->Pieton->CaseDecision = 'A';
				}
				tmp = tmp->next;
			}
			else 
			{ 
				affichagePartielPieton(MatriceMap, tmp->Pieton);
				tmp->Pieton->posX = NextPosition->posX;
				tmp->Pieton->posY = NextPosition->posY;
				tmp->Pieton->CaseDecision = MatriceDecision[tmp->Pieton->posX][tmp->Pieton->posY];
				setNewPietonDirection(tmp->Pieton, MatriceDecision, *ListeDesPietons);
				affichagePieton(tmp->Pieton);
				tmp = tmp->next;	
			}
	
		}
			free(NextPosition);
	}
}


