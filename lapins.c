#include "librairies.h"
#include "lapins.h"

void lapinSpawner(int posX, int posY, LapinList** ListeDesLapins)
{
		Lapin* Lapin=malloc(sizeof(Lapin));
		Lapin->posX = posX;
		Lapin->posY = posY;
		Lapin->healthpoints = 9;
		Lapin->CaseDecision = 't';
		appendLapinList(ListeDesLapins, Lapin);
}

void appendLapinList(LapinList** ListeDesLapins, Lapin* Lapin)
{
	LapinList *element;
	element = calloc(1,sizeof(*element));
	element->Lapin = Lapin;
	element->next = *ListeDesLapins;
	*ListeDesLapins = element;
}

LapinList* lapinEater(LapinList **List, Lapin* Lapin)
{
	LapinList* PointeurCourant;
	LapinList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
		{
			if (PointeurCourant->Lapin == Lapin)
			{
				if (PointeurPrecedent == NULL)
				{ 	
					*List = PointeurCourant->next;
				} 
				else
				{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
				}
			LapinList* ptrToReturn = PointeurCourant->next;
			free(PointeurCourant);break;
			return ptrToReturn;
			}
		}
	return NULL;
}

void affichageLapin(Lapin* Lapin)
{
		couleur("37");
		printf("\033[%d;%dH🐇",Lapin->posX,Lapin->posY);
		couleur("0");
}

void affichagePartielLapin(char** MatriceMap, Lapin* Lapin)
{
	char caractere;
	caractere = MatriceMap[Lapin->posX][Lapin->posY];
	printf("\033[%d;%dH",Lapin->posX,Lapin->posY);
	switch(caractere) //a epurer, le champ des lapins ne contient pas autant de caracteres 
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
				//caracteres par default
				default: printf("%c",caractere);break;
			}
}

Position* positionFutureLapin(Lapin* Lapin)
{
	Position* Position = malloc(sizeof(Position));
	Position->posX = Lapin->posX;
	Position->posY = Lapin->posY;
	if(Lapin->CaseDecision == 't')
	{
		switch(rand()%9)
		{
			case 0: 
				Position->posX = Position->posX -1;
				Position->posY = Position->posY -1;
				return Position;
			case 2:
				Position->posX = Position->posX -1;
				return Position;
			case 3:
				Position->posX = Position->posX -1;
				Position->posY = Position->posY +1;
				return Position;
			case 4:
				Position->posY = Position->posY -1;
				return Position;
			case 5: 
				return Position;
			case 6:
				Position->posX = Position->posX +1;
				Position->posY = Position->posY -1;
				return Position;
			case 7:
				Position->posX = Position->posX +1;
				return Position;
			case 8:
				Position->posY = Position->posY +1;
				Position->posX = Position->posX +1;
				return Position;
			case 1:
				Position->posY = Position->posY +1;
				return Position;
			default:
				return Position;
		}
	}
	else if(Lapin->CaseDecision == 'b')
	{
		Position->posX = Position->posX +1;
		return Position;
	}
	else if(Lapin->CaseDecision == 'h')
	{
		Position->posX = Position->posX -1;
		return Position;
	}
	else if(Lapin->CaseDecision == 'd')
	{
		Position->posY = Position->posY +1;
		return Position;
	}
	else
	{
		Position->posY = Position->posY -1;
		return Position;
	}
}

int Voisins(Lapin* Lapin, char** MatriceDecision)
{
	int i;
	int j;
	int c = -1;
	for (i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			if(MatriceDecision[Lapin->posX -1 + i][Lapin->posY -1 + j] == 'R')
			{
				c = c + 1;
			}
		}
	}
return c;
}

void roulementLapinsPosition(char** MatriceMap, char** MatriceDecision, LapinList** ListeDesLapins)
{
LapinList *tmp;
tmp = *ListeDesLapins;
while (tmp != NULL)
	{	
		Position* NextPosition = positionFutureLapin(tmp->Lapin); // Afin de free plus tard
		if(tmp->Lapin->healthpoints < 1)
		{
			affichagePartielLapin(MatriceMap, tmp->Lapin);
			tmp = lapinEater(ListeDesLapins, tmp->Lapin);
		}
		else
		{
			if (Voisins(tmp->Lapin, MatriceDecision) < 2)
			{
				affichagePartielLapin(MatriceMap, tmp->Lapin);
				tmp->Lapin->healthpoints = tmp->Lapin->healthpoints - 1;
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = tmp->Lapin->CaseDecision;
				tmp->Lapin->posX = NextPosition->posX;
				tmp->Lapin->posY = NextPosition->posY;
				tmp->Lapin->CaseDecision = MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY];
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = 'R';
				affichageLapin(tmp->Lapin);
				tmp = tmp->next;
			}
			else if(Voisins(tmp->Lapin, MatriceDecision) > 6)
			{
				affichagePartielLapin(MatriceMap, tmp->Lapin);
				tmp->Lapin->healthpoints = tmp->Lapin->healthpoints - 4;
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = tmp->Lapin->CaseDecision;
				tmp->Lapin->posX = NextPosition->posX;
				tmp->Lapin->posY = NextPosition->posY;
				tmp->Lapin->CaseDecision = MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY];
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = 'R';
				affichageLapin(tmp->Lapin);
				tmp = tmp->next;
			}
			else if(Voisins(tmp->Lapin, MatriceDecision) == 4)
			{
				affichagePartielLapin(MatriceMap, tmp->Lapin);
				tmp->Lapin->healthpoints = tmp->Lapin->healthpoints + 5;
				lapinSpawner(30+rand()%13, 5+rand()%29, ListeDesLapins); //Si un Lapin a exactement 4 voisins, alors un Lapin nait dans le champ
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = tmp->Lapin->CaseDecision;
				tmp->Lapin->posX = NextPosition->posX;
				tmp->Lapin->posY = NextPosition->posY;
				tmp->Lapin->CaseDecision = MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY];
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = 'R';
				affichageLapin(tmp->Lapin);	
				tmp = tmp->next;
			}
			else
			{
				affichagePartielLapin(MatriceMap, tmp->Lapin);
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = tmp->Lapin->CaseDecision;
				tmp->Lapin->posX = NextPosition->posX;
				tmp->Lapin->posY = NextPosition->posY;
				tmp->Lapin->CaseDecision = MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY];
				MatriceDecision[tmp->Lapin->posX][tmp->Lapin->posY] = 'R';
				affichageLapin(tmp->Lapin);
				tmp = tmp->next;
			}
		}
		free(NextPosition);
	}
}

//🔥⛽