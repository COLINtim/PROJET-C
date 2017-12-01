#include "librairies.h"
#include "tramways.h"

void tramwaySpawner(int posX, int posY, Direction Direction, TramwayList** ListeDesTramways)
{
		Tramway* Tram = malloc(sizeof(Tramway));
		Tram->posX = posX;
		Tram->posY = posY;
		Tram->CaseDecision = 'S';
		Tram->Direction = Direction;
		Tram->compteur = 0; 
		Tram->compteur2 = -1;
		appendTramwayList(ListeDesTramways, Tram);
}

TramwayEater* tramwayEaterInit()
{
	TramwayEater* Eater = malloc(sizeof(TramwayEater));
	Eater->decr = 5;
	return Eater;
}

void eaterAffichage(TramwayEater* Eater, int NumeroDeLigne)
{
	if(Eater->decr == 0)
	{
		Eater->decr = 5;
	}
	else
	{
		if(NumeroDeLigne == 1)
		{
			switch(Eater->decr)
			{
				case 4:
					printf("\033[%d;%dH│\n",63,118);	
					Eater->decr = Eater->decr -1; break;
				case 3:
					printf("\033[%d;%dH│\n",64,118);	
					Eater->decr = Eater->decr -1; break;
				case 2:
					printf("\033[%d;%dH│\n",65,118);	
					Eater->decr = Eater->decr -1; break;
				case 1:
					printf("\033[%d;%dH│\n",66,118);	//64-67 , 119 │
					Eater->decr = Eater->decr -1; break;
				default:
				break;
			}
		}
		else //NumeroDeLigne == 2
		{
			switch(Eater->decr)
			{
				case 4:
					printf("\033[%d;%dH─\n",58,5);
					Eater->decr = Eater->decr -1; break; //59 2-5─
				case 3:
					printf("\033[%d;%dH─\n",58,4);
					Eater->decr = Eater->decr -1; break;
				case 2:
					printf("\033[%d;%dH─\n",58,3);
					Eater->decr = Eater->decr -1; break;
				case 1:
					printf("\033[%d;%dH─\n",58,2);
					printf("\033[%d;%dH─\n",58,1);
					Eater->decr = Eater->decr -1; break;
				default:
				break;
			}
		}
	}
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
	if(Tram->posX == 56) //SPAWN 1
	{
		if(Tram->posY <4)
		{
			couleur("37");
			printf("\033[%d;%dH∎\n",Tram->posX,Tram->posY);	
			couleur("0");
		}
		else
		{
			couleur("37");
			printf("\033[%d;%dH∎\n",Tram->posX,Tram->posY);	
			affichagePartielTramway(MatriceMap, Tram);
			couleur("0");
		}
	}
	else if(Tram->posY == 114)		//SPAWN 2
	{
		if(Tram->posX > 65)
		{
			couleur("37");
			printf("\033[%d;%dH∎\n",Tram->posX,Tram->posY);
			couleur("0");
		}
		else
		{
			couleur("37");
			printf("\033[%d;%dH∎\n",Tram->posX,Tram->posY);	
			affichagePartielTramway(MatriceMap, Tram);
			couleur("0");
		}
	}
	else //RESTE DU TEMPS
	{
		couleur("37");
		printf("\033[%d;%dH∎\n",Tram->posX,Tram->posY);	
		affichagePartielTramway(MatriceMap, Tram);	
		couleur("0");
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
	else if(Tramway->posX == 58 && Tramway-> posY == 114)
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
			printf("─\n");
		}
		else if(testPositionTramway(Tramway) == 2) //2EME
		{
			printf("\033[%d;%dH",56,116);
			printf("─\n");
		}
		else if(testPositionTramway(Tramway) == 3) //3EME
		{
			printf("\033[%d;%dH",56,117);
			printf("─\n");
		}
		else if(testPositionTramway(Tramway) == 7) //CORNER 1
		{
			printf("\033[%d;%dH",56,114);
			printf("─\n");
		}
		else if(testPositionTramway(Tramway) == 4) //1ERE CASE APRES LE 2EME CORNER
		{
			printf("\033[%d;%dH",59,114);
			printf("│\n");
		}
		else if(testPositionTramway(Tramway) == 5) //2EME
		{
			printf("\033[%d;%dH",60,114);
			printf("│\n");
		}
		else if(testPositionTramway(Tramway) == 6) //3EME
		{
			printf("\033[%d;%dH",61,114);
			printf("│\n");
		}
		else if(testPositionTramway(Tramway) == 8) //CORNER 2
		{
			printf("\033[%d;%dH",62,114);
			printf("│\n");
		}
		else
		{
		switch(Tramway->Direction)
			{
			case NORD:
				caractere = MatriceMap[Tramway->posX+4][Tramway->posY];
				printf("\033[%d;%dH",Tramway->posX+4,Tramway->posY);
				break;
			case EST:
				caractere = MatriceMap[Tramway->posX][Tramway->posY-4];
				printf("\033[%d;%dH",Tramway->posX,Tramway->posY-4);
				break;
			case OUEST:
				if(Tramway->CaseDecision != 'F')
				{
					couleur("37");
					printf("\033[%d;%dH\n",Tramway->posX,Tramway->posY+1);
					printf("\033[%d;%dH\n",Tramway->posX,Tramway->posY+2);
					printf("\033[%d;%dH\n",Tramway->posX,Tramway->posY+3);	
					couleur("0");
				}
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
				case '%': couleur("48;5;94");printf("▒");couleur("0");break;
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

void roulementTramwaysPosition(char** MatriceMap, char** MatriceDecision, TramwayList** ListeDesTramways, TramwayEater* TramwayEater1, TramwayEater* TramwayEater2)
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
			if(tmp->Tramway->posX > 60) //s'il s'agit de la Ligne 1
			{
				TramwayEater1->decr = TramwayEater1->decr -1;
			}
			else //sinon c'est la ligne 2
			{
				TramwayEater2->decr = TramwayEater2->decr -1;
				printf("\033[%d;%dH─\n",58,6);
			}
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

void feuxDeTram(char ***MatriceDecision, char **MatriceMap, Tramway * T1, Tramway * T2){
	
	if(T1->posY == 81){T1->compteur2=0;}
	if(T2->posY == 97){T2->compteur2=0;}
	//printf("\033[67;1H%d",T1->posY);

	if(T1->compteur2 >T2->compteur2){
		
		if(T1->compteur2 >= 0){

			switch(T1->compteur2){

				case 0: couleur("41"); printf("\033[54;85H ");printf("\033[60;91H ");couleur("0");
						(*MatriceDecision)[54][86]='f';(*MatriceDecision)[60][89]='f';
						break;
				case 1: couleur("33"); printf("\033[55;86H─");printf("\033[59;90H─");couleur("0");break;
				case 2: couleur("33"); printf("\033[55;87H─");printf("\033[59;89H─");couleur("0");break;
				case 3: couleur("33"); printf("\033[55;88H─");printf("\033[59;88H─");couleur("0");break;
				case 4: couleur("33"); printf("\033[55;89H─");printf("\033[59;87H─");couleur("0");break;
				case 5: couleur("33"); printf("\033[55;90H─");printf("\033[59;86H─");couleur("0");break;
				case 15: printf("\033[55;90H ");printf("\033[59;86H ");break;
				case 16: printf("\033[55;89H ");printf("\033[59;87H ");break;
				case 17: printf("\033[55;88H ");printf("\033[59;88H ");break;
				case 18: printf("\033[55;87H ");printf("\033[59;89H ");break;
				case 19: printf("\033[55;86H ");printf("\033[59;90H ");break;
				case 20: T1->compteur2=-1;
			}
			if (T1->compteur2 != -1){T1->compteur2++;}
		}
		if(T2->compteur2 >= 0){

			switch(T2->compteur2){

				case 0: couleur("41"); printf("\033[54;85H ");printf("\033[60;91H ");couleur("0");
						(*MatriceDecision)[54][86]='f';(*MatriceDecision)[60][89]='f';
						break;
				case 1: couleur("33"); printf("\033[55;86H─");printf("\033[59;90H─");couleur("0");break;
				case 2: couleur("33"); printf("\033[55;87H─");printf("\033[59;89H─");couleur("0");break;
				case 3: couleur("33"); printf("\033[55;88H─");printf("\033[59;88H─");couleur("0");break;
				case 4: couleur("33"); printf("\033[55;89H─");printf("\033[59;87H─");couleur("0");break;
				case 5: couleur("33"); printf("\033[55;90H─");printf("\033[59;86H─");couleur("0");break;
				case 15: printf("\033[55;90H ");printf("\033[59;86H ");break;
				case 16: printf("\033[55;89H ");printf("\033[59;87H ");break;
				case 17: printf("\033[55;88H ");printf("\033[59;88H ");break;
				case 18: printf("\033[55;87H ");printf("\033[59;89H ");break;
				case 19: printf("\033[55;86H ");printf("\033[59;90H ");break;
				case 20: T2->compteur2=-1;
			}
			if (T2->compteur2 != -1){T2->compteur2++;}
		}

	}else if(T1->compteur2 <=T2->compteur2){

		if(T2->compteur2 >= 0){

			switch(T2->compteur2){

				case 0: couleur("41"); printf("\033[54;85H ");printf("\033[60;91H ");couleur("0");
						(*MatriceDecision)[54][86]='f';(*MatriceDecision)[60][89]='f';
						break;
				case 1: couleur("33"); printf("\033[55;86H─");printf("\033[59;90H─");couleur("0");break;
				case 2: couleur("33"); printf("\033[55;87H─");printf("\033[59;89H─");couleur("0");break;
				case 3: couleur("33"); printf("\033[55;88H─");printf("\033[59;88H─");couleur("0");break;
				case 4: couleur("33"); printf("\033[55;89H─");printf("\033[59;87H─");couleur("0");break;
				case 5: couleur("33"); printf("\033[55;90H─");printf("\033[59;86H─");couleur("0");break;
				case 15: printf("\033[55;90H ");printf("\033[59;86H ");break;
				case 16: printf("\033[55;89H ");printf("\033[59;87H ");break;
				case 17: printf("\033[55;88H ");printf("\033[59;88H ");break;
				case 18: printf("\033[55;87H ");printf("\033[59;89H ");break;
				case 19: printf("\033[55;86H ");printf("\033[59;90H ");break;
				case 20: T2->compteur2=-1;
			}
			if (T2->compteur2 != -1){T2->compteur2++;}
		}
		if(T1->compteur2 >= 0){

			switch(T1->compteur2){

				case 0: couleur("41"); printf("\033[54;85H ");printf("\033[60;91H ");couleur("0");
						(*MatriceDecision)[54][86]='f';(*MatriceDecision)[60][89]='f';
						break;
				case 1: couleur("33"); printf("\033[55;86H─");printf("\033[59;90H─");couleur("0");break;
				case 2: couleur("33"); printf("\033[55;87H─");printf("\033[59;89H─");couleur("0");break;
				case 3: couleur("33"); printf("\033[55;88H─");printf("\033[59;88H─");couleur("0");break;
				case 4: couleur("33"); printf("\033[55;89H─");printf("\033[59;87H─");couleur("0");break;
				case 5: couleur("33"); printf("\033[55;90H─");printf("\033[59;86H─");couleur("0");break;
				case 15: printf("\033[55;90H ");printf("\033[59;86H ");break;
				case 16: printf("\033[55;89H ");printf("\033[59;87H ");break;
				case 17: printf("\033[55;88H ");printf("\033[59;88H ");break;
				case 18: printf("\033[55;87H ");printf("\033[59;89H ");break;
				case 19: printf("\033[55;86H ");printf("\033[59;90H ");break;
				case 20: T1->compteur2=-1;
			}
			if (T1->compteur2 != -1){T1->compteur2++;}
		}
	}
	if (T1->compteur2 == -1 && T2->compteur2 == -1){
		couleur("42");
		printf("\033[54;85H ");
		printf("\033[60;91H ");
		couleur("0");
		(*MatriceDecision)[54][86]='o';
		(*MatriceDecision)[60][89]='o';
	}
}


int compteurDeTramways(TramwayList** ListeDesTramways){
	int i=0;
	TramwayList *tmp;
	tmp = *ListeDesTramways;
	while(tmp != NULL){
		i++;
		tmp = tmp->next;
	}
	return i;
}