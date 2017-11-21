#include "librairies.h"
#include "tramways.h"

void tramwaySpawner(int posX, int posY, int numerowagon, int compteur, Direction Direction, TramwayList** ListeDesTramways)
{
		Tramway* Tram=malloc(sizeof(Tramway));
		Tram->posX = posX;
		Tram->posY = posY;
		Tram->CaseDecision = 'S';
		Tram->Direction = Direction;
		Tram->numerowagon = numerowagon;
		Tram->compteur = compteur; 
		Tram->compteur2 = 0;
		appendTramwayList(ListeDesTramways, Tram);
}

void appendTramwayList(TramwayList** ListeDesTramways, Tramway* Tram)
{
	TramwayList *element;
	element = calloc(1,sizeof(*element));
	element->Tramway = Tram;
	element->next = *ListeDesTramways;
	*ListeDesTramways = element;
}

TramwayList* tramwayEater(TramwayList **List, Tramway* Tramway)
{
	TramwayList* PointeurCourant;
	TramwayList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
		{
			if (PointeurCourant->Tramway == Tramway)
			{
				if (PointeurPrecedent == NULL)
				{ 	
					*List = PointeurCourant->next;
				} 
				else
				{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
				}
			TramwayList* ptrToReturn = PointeurCourant->next;
			free(PointeurCourant);break;
			return ptrToReturn;
			}
		}
	return NULL;
}

void affichageTramway(Tramway* Tram)
{
		couleur("37");
		printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);

}

void setNewTramwayDirection(Tramway* Tramway, char ** MatriceDecision, TramwayList *ListeDesTramways)
{
	switch(MatriceDecision[Tramway->posX][Tramway->posY])
	{
		case 'd':
		case 'l':
		case 'j':
			Tramway->Direction = EST; 
			break;
		case 'g':
		case 'r':
		case 'k':
			Tramway->Direction = OUEST; 
			break;
		case 'h':
			Tramway->Direction = NORD; 
			break;
		case 'b':
			Tramway->Direction = SUD; 
	}

}

void stationTramway(Tramway* Tramway)
{
	Tramway->compteur = Tramway->compteur +1;
}

void resetcompteurTramway(Tramway* Tramway)
{
		Tramway->compteur = 0;
}

Position* positionFutureTramway(Tramway* Tramway)
{
	Position* Position = malloc(sizeof(Position));
	Position->posX = Tramway->posX;
	Position->posY = Tramway->posY;
	switch(Tramway->Direction)
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

int ObstacleTramway(char ** MatriceDecision, int i, int j)
{
	if(MatriceDecision[i][j] == 'f' || MatriceDecision[i][j] == 'c')
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

void roulementTramwaysPosition(char** MatriceMap, char** MatriceDecision, TramwayList** ListeDesTramways)
{
TramwayList *tmp;
tmp = *ListeDesTramways;
while (tmp != NULL)
	{	
		Position* NextPosition = positionFutureTramway(tmp->Tramway); // Afin de free plus tard
		if (ObstacleTramway(MatriceDecision, NextPosition->posX, NextPosition->posY) == 2)
		{
			if(tmp->Tramway->numerowagon == 4)
			{
				affichagePartielTramway(MatriceMap, tmp->Tramway);
			}
			tmp->Tramway->posX = NextPosition->posX;
			tmp->Tramway->posY = NextPosition->posY;
			affichageTramway(tmp->Tramway);
			tmp = tramwayEater(ListeDesTramways, tmp->Tramway);
		}
		else if (ObstacleTramway(MatriceDecision, NextPosition->posX, NextPosition->posY) == 1)
		{
			affichageTramway(tmp->Tramway);
		}
		else
		{
			if(tmp->Tramway->CaseDecision == 'D')
			{
				if(tmp->Tramway->numerowagon == 4)
				{
					affichagePartielTramway(MatriceMap, tmp->Tramway);
				}
					resetcompteurTramway(tmp->Tramway);
					tmp->Tramway->posX = NextPosition->posX;
					tmp->Tramway->posY = NextPosition->posY;
					affichageTramway(tmp->Tramway);
					tmp->Tramway->CaseDecision = 'F'; //Passage en mode fantome
					tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'F') //Mode fantome
			{
				if(tmp->Tramway->numerowagon == 4)
				{
					affichagePartielTramway(MatriceMap, tmp->Tramway);
				}
				tmp->Tramway->posX = NextPosition->posX;
				tmp->Tramway->posY = NextPosition->posY;
				if(MatriceDecision[NextPosition->posX][NextPosition->posY] == 'A')
				{
					tmp->Tramway->CaseDecision = 'A';
				}
				tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'w' && tmp->Tramway->numerowagon == 1 && tmp->Tramway->compteur < 21) //Arret a la station
			{
				stationTramway(tmp->Tramway);
				tmp->Tramway->compteur = tmp->Tramway->compteur +1;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				affichageTramway(tmp->Tramway);
				tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'x' && tmp->Tramway->numerowagon == 2 && tmp->Tramway->compteur < 21) //Arret a la station
			{
				stationTramway(tmp->Tramway);
				tmp->Tramway->compteur = tmp->Tramway->compteur +1;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				affichageTramway(tmp->Tramway);
				tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'y' && tmp->Tramway->numerowagon == 3 && tmp->Tramway->compteur < 21) //Arret a la station
			{
				stationTramway(tmp->Tramway);
				tmp->Tramway->compteur = tmp->Tramway->compteur +1;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				affichageTramway(tmp->Tramway);
				tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'z' && tmp->Tramway->numerowagon == 4 && tmp->Tramway->compteur < 21) //Arret a la station
			{
				affichagePartielTramway(MatriceMap, tmp->Tramway);
				stationTramway(tmp->Tramway);
				tmp->Tramway->compteur = tmp->Tramway->compteur +1;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				affichageTramway(tmp->Tramway);
				tmp = tmp->next;
			}
			else 
			{ 
				if(tmp->Tramway->numerowagon == 4)
				{
				affichagePartielTramway(MatriceMap, tmp->Tramway);
				}
				tmp->Tramway->posX = NextPosition->posX;
				tmp->Tramway->posY = NextPosition->posY;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				setNewTramwayDirection(tmp->Tramway, MatriceDecision, *ListeDesTramways);
				affichageTramway(tmp->Tramway);
				tmp = tmp->next;	
			}
	
		}
			free(NextPosition);
	}
}

void affichagePartielTramway(char ** MatriceMap, Tramway * Tramway)
{

	char caractere;;
	
	for(int i = 0; i<2; i++){

		caractere = MatriceMap[Tramway->posX][Tramway->posY+i];

		printf("\033[%d;%dH",Tramway->posX,Tramway->posY+i);
		
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

}
