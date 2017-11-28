#include "librairies.h"
#include "tramways.h"

void tramwaySpawner(int posX, int posY, int compteur, Direction Direction, TramwayList** ListeDesTramways)
{
		Tramway* Tram=malloc(sizeof(Tramway));
		Tram->posX = posX;
		Tram->posY = posY;
		Tram->CaseDecision = 'S';
		Tram->Direction = Direction;
		Tram->compteur = compteur; 
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

void affichageTramway(char** MatriceMap, Tramway* Tram)
{
	if(Tram->posX == 56)
	{
		if(Tram->posY <4)
		{
			couleur("37");
			printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);	
		}
		else
		{
			couleur("37");
			printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);	
			affichagePartielTramway(MatriceMap, Tram);
		}
	}
	else if(Tram->posY == 114)
	{
		if(Tram->posX > 61)
		{
			couleur("37");
			printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);
		}
		else
		{
			couleur("37");
			printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);	
			affichagePartielTramway(MatriceMap, Tram);
		}
	}
	else
	{
		couleur("37");
		printf("\033[%d;%dH🚋",Tram->posX,Tram->posY);	
		affichagePartielTramway(MatriceMap, Tram);	
	}
}


int testPositionTramway(Tramway* Tramway)
{
	if(Tramway->posX == 57 && Tramway-> posY == 118)
	{
		return 1;
	}
	else if(Tramway->posX == 56 && Tramway-> posY == 118)
	{
		return 7;
	}
	else if(Tramway->posX == 59 && Tramway-> posY == 116)
	{
		return 8;
	}
	else if(Tramway->posX == 58 && Tramway-> posY == 118)
	{
		return 2;
	}
	else if(Tramway->posX == 59 && Tramway-> posY == 118)
	{
		return 3;
	}
	if(Tramway->posX == 58 && Tramway-> posY == 111)
	{
		return 4;
	}
	else if(Tramway->posX == 58 && Tramway-> posY == 112)
	{
		return 5;
	}
	else if(Tramway->posX == 58 && Tramway-> posY == 113) //Les else if sont une disjonction de cas des positions des virages
	{
		return 6;
	}
	else
	{
		return 0;
	}
}



void affichagePartielTramway(char ** MatriceMap, Tramway * Tramway)
{

	char caractere;
		if(testPositionTramway(Tramway) == 1) //1ERE CASE APRES LE 1ER CORNER
		{
			printf("\033[%d;%dH",56,115);
			printf("─");
		}
		else if(testPositionTramway(Tramway) == 2) //2EME
		{
			printf("\033[%d;%dH",56,116);
			printf("─");
		}
		else if(testPositionTramway(Tramway) == 3) //3EME
		{
			printf("\033[%d;%dH",56,117);
			printf("─");
		}
		else if(testPositionTramway(Tramway) == 4) //1ERE CASE APRES LE 2EME CORNER
		{
			printf("\033[%d;%dH",60,116);
			printf("│");
		}
		else if(testPositionTramway(Tramway) == 5) //2EME
		{
			printf("\033[%d;%dH",61,116);
			printf("│");
		}
		else if(testPositionTramway(Tramway) == 6) //3EME
		{
			printf("\033[%d;%dH",62,116);
			printf("│");
		}
		else if(testPositionTramway(Tramway) == 7) //CORNER 1
		{
			printf("\033[%d;%dH",56,114);
			printf("─");
		}
		else if(testPositionTramway(Tramway) == 8) //CORNER 2
		{
			printf("\033[%d;%dH",61,116);
			printf("│");
		}
		else
		{
		switch(Tramway->Direction)
			{
			case NORD:
				caractere = MatriceMap[Tramway->posX-4][Tramway->posY];
				printf("\033[%d;%dH",Tramway->posX-4,Tramway->posY);
				break;
			case EST:
				caractere = MatriceMap[Tramway->posX][Tramway->posY-4];
				printf("\033[%d;%dH",Tramway->posX,Tramway->posY-4);
				break;
			case OUEST:
				caractere = MatriceMap[Tramway->posX][Tramway->posY+4];
				printf("\033[%d;%dH",Tramway->posX,Tramway->posY+4);
				break;
			case SUD:
				caractere = MatriceMap[Tramway->posX-4][Tramway->posY];
				printf("\033[%d;%dH",Tramway->posX-4,Tramway->posY);
				break;
			}
		switch(caractere)
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
			tmp->Tramway->posX = NextPosition->posX;
			tmp->Tramway->posY = NextPosition->posY;
			affichageTramway(MatriceMap, tmp->Tramway);
			tmp = tramwayEater(ListeDesTramways, tmp->Tramway);
		}
		else if (ObstacleTramway(MatriceDecision, NextPosition->posX, NextPosition->posY) == 1)
		{
			affichageTramway(MatriceMap, tmp->Tramway);
			tmp = tmp->next;
		}
		else
		{
			if(tmp->Tramway->CaseDecision == 'D')
			{
					affichagePartielTramway(MatriceMap, tmp->Tramway);
					tmp->Tramway->posX = NextPosition->posX;
					tmp->Tramway->posY = NextPosition->posY;
					affichageTramway(MatriceMap, tmp->Tramway);
					tmp->Tramway->CaseDecision = 'F'; //Passage en mode fantome
					tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'F') //Mode fantome
			{
				affichagePartielTramway(MatriceMap, tmp->Tramway);
				tmp->Tramway->posX = NextPosition->posX;
				tmp->Tramway->posY = NextPosition->posY;
				if(MatriceDecision[NextPosition->posX][NextPosition->posY] == 'A')
				{
					tmp->Tramway->CaseDecision = 'A';
				}
				tmp = tmp->next;
			}
			else if(tmp->Tramway->CaseDecision == 'w' && tmp->Tramway->compteur < 21) //Arret a la station
			{
				tmp->Tramway->compteur = tmp->Tramway->compteur +1;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				affichageTramway(MatriceMap, tmp->Tramway);
				tmp = tmp->next;
			}
			else 
			{ 
				affichagePartielTramway(MatriceMap, tmp->Tramway);
				tmp->Tramway->compteur = 0;
				tmp->Tramway->posX = NextPosition->posX;
				tmp->Tramway->posY = NextPosition->posY;
				tmp->Tramway->CaseDecision = MatriceDecision[tmp->Tramway->posX][tmp->Tramway->posY];
				setNewTramwayDirection(tmp->Tramway, MatriceDecision, *ListeDesTramways);
				affichageTramway(MatriceMap, tmp->Tramway);
				tmp = tmp->next;	
			}
	
		}
			free(NextPosition);
	}
}

/*void feuxDeTram(char ***MatriceDecision, char **MatriceMap, Tramway * T1, Tramway * T2)
{
	//test
	if(T1->compteur2 > T2->compteur2)
	{

		if(T1->posX == 56 && T1->posY == 83)
			{
				T1->compteur2 = 0;
			} 
		if(T1->posX == 58 && T1->posY == 96)
			{
				T2->compteur2 = 0;
			}
		if(T1->compteur2 >= 0)
		{

			switch(T1->compteur2)
			{

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("43"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("43"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("43"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("43"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("43"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
			}
			if (T1->compteur2 != -1){T1->compteur2++;}
		}
		if(T2->compteur2 >= 0){

			switch(T2->compteur2)
			{

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("43"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("43"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("43"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("43"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("43"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
			}
			if (T2->compteur2 != -1){T2->compteur2++;}
		}

	}	
		//si il y a le tram: on rentre dans la boucle de feux (modification du dec.txt et affichage du feux en rouge)

		//boucle feux: on boucle sur 8 frames (|  TTTT  |) 2 premieres on abaisse la barriere et les 2 dernieres on releve.

		//apres ça on réaffiche en vert tout en modifiant le dec.txt.


	
	else if(T1->compteur2 <= T2->compteur2)
	{
		if(T2->posX == 57 && T2->posY == 81)
			{
				T1->compteur2 = 0;
			} 
		if(T2->posX == 59 && T2->posY == 97)
			{
				T2->compteur2 = 0;
			}
		if(T2->compteur2 >= 0)
		{

			switch(T2->compteur2)
			{

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("33"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("33"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("33"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("33"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("33"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
				case 15: printf("\033[56;91H ");printf("\033[60;87H ");break;
				case 16: printf("\033[56;90H ");printf("\033[60;90H ");break;
				case 17: printf("\033[56;89H ");printf("\033[60;89H ");break;
				case 18: printf("\033[56;88H ");printf("\033[60;88H ");break;
				case 19: printf("\033[56;87H ");printf("\033[60;87H ");break;
				case 20: T2->compteur2=-1;
			}
			if (T2->compteur2 != -1)
				{
					T2->compteur2++;
				}
		}
		if(T1->compteur2 >= 0){

			switch(T1->compteur2)
			{

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("43"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("43"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("43"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("43"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("43"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
				case 15: printf("\033[56;91H ");printf("\033[60;87H ");break;
				case 16: printf("\033[56;90H ");printf("\033[60;90H ");break;
				case 17: printf("\033[56;89H ");printf("\033[60;89H ");break;
				case 18: printf("\033[56;88H ");printf("\033[60;88H ");break;
				case 19: printf("\033[56;87H ");printf("\033[60;87H ");break;
				case 20: T1->compteur2=-1;
			}
			if (T1->compteur2 != -1)
				{
					T1->compteur2++;
				}
		}
	}
	if (T1->compteur2 == -1 && T2->compteur2 == -1)
	{
		couleur("42");
		printf("\033[55;86H ");
		printf("\033[60;92H ");
		couleur("0");
		(*MatriceDecision)[55][87]='o';
		(*MatriceDecision)[60][91]='o';
	}
}
*/

//56,118 Corner ligne 1