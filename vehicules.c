#include "librairies.h"
#include "vehicules.h"


// FONCTIONS RELATIVES AUX VEHICULES ET A LEURS DECISIONS

Position* positionFuture(Vehicule* vehicule)
{
	Position* Position = malloc(sizeof(Position));
	switch(vehicule->Direction) 
	{
		case NORD: 
			Position->posX=(vehicule->posX)-1;
			Position->posY=vehicule->posY;
			return Position;
		case EST: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)+1;
			return Position;
		case OUEST: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)-1;
			return Position;
		case SUD: 
			Position->posX=(vehicule->posX)+1;
			Position->posY=vehicule->posY;
			return Position;
		default:
			Position->posX = vehicule->posX;
			Position->posY = vehicule->posY;
			return Position;
	}
}

void setNewPositionVehicule(Vehicule* vehicule)
{
	vehicule->posX = positionFuture(vehicule)->posX;
	vehicule->posY = positionFuture(vehicule)->posY;
}

int Obstacle(char** MatriceDecision, int i, int j)
{
	if(MatriceDecision[i][j]!='c')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void roulementVehiculesPosition(char ** MatriceMap,char*** MatriceDecision, VehiculeList** ListeDesVehicules)
{
	VehiculeList *tmp;
	tmp = *ListeDesVehicules;
	while (tmp != NULL)
		{	
			Position* NextPosition = positionFuture(tmp->Vehicule); // Afin de free plus tard
			
			if((*MatriceDecision)[NextPosition->posX][NextPosition->posY] == 'f' || (*MatriceDecision)[NextPosition->posX][NextPosition->posY] =='c')
			{
				//affichagePartielVehicule(MatriceMap, tmp->Vehicule);
				affichageVehicule(tmp->Vehicule);
				tmp = tmp ->next;
			}		
			else
			{
				if(((*MatriceDecision)[NextPosition->posX][NextPosition->posY]=='P')&&((tmp->Vehicule->Compteur)<31))
				{
					affichageVehicule(tmp->Vehicule);
					animationDeRemplissage(tmp->Vehicule);
					tmp->Vehicule->Compteur = tmp->Vehicule->Compteur +1;
					tmp = tmp->next;
				}
				else
				{
					(*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY] = tmp->Vehicule->CaseDecision; //La ou la voiture etait devient de la route (place libre)
					affichagePartielVehicule(MatriceMap, tmp->Vehicule);
					setNewPositionVehicule(tmp->Vehicule); //On actualise la position de la voiture dans la structure 
					tmp->Vehicule->CaseDecision = (*MatriceDecision)[NextPosition->posX][NextPosition->posY]; // MAJ de la case decision
					if(tmp->Vehicule->CaseDecision == 'E')
					{
						affichagePartielVehicule(MatriceMap, tmp->Vehicule);
						tmp = vehiculeEater(ListeDesVehicules, tmp->Vehicule);

					}
					else
					{	
						affichagePartielVehicule(MatriceMap, tmp->Vehicule);
						setNewVehiculeDirection(tmp->Vehicule, (*MatriceDecision), *ListeDesVehicules); //On actualise la Direction du vehicule
						(*MatriceDecision)[NextPosition->posX][NextPosition->posY] = 'c'; //On actualise la MatricePositionVehicules pour signaler qu'une voiture se trouve maintenant a cette position
						affichageVehicule(tmp->Vehicule);	
						tmp = tmp->next;
					}
				}
			}
			free(NextPosition);
		}
}


VehiculeList* vehiculeEater(VehiculeList **List, Vehicule* Vehicule)
{
	VehiculeList* PointeurCourant;
	VehiculeList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
	{
		if (PointeurCourant->Vehicule == Vehicule)
		{
			if (PointeurPrecedent == NULL)
			{ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
				*List = PointeurCourant->next;
			} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
			else
			{
				PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
			}
		VehiculeList* ptrToReturn = PointeurCourant->next;
		free(PointeurCourant);break;
		return ptrToReturn;
		}
	}
	return NULL;
}
	
void appendVehiculeList(VehiculeList** ListeDesVehicules, Vehicule* Vehicule)
{
	VehiculeList *element;
	element = calloc(1,sizeof(*element));
	element->Vehicule = Vehicule;
	element->next = *ListeDesVehicules;
	*ListeDesVehicules = element;
}

void vehiculeSpawner(int posX, int posY, Direction Direction, Carburant Carburant, char a, char** MatriceDecision, VehiculeList** ListeDesVehicules)
{
	Vehicule* Veh = malloc(sizeof(Vehicule));
	Veh->posX=posX;
	Veh->posY=posY;
	Veh->Compteur = 0;
	Veh->custom = a;
	Veh->CaseDecision = 'S';
	Veh->Direction = Direction;
	Veh->Carburant = Carburant;
	Veh->virage = 0;
	MatriceDecision[posX][posY] = 'c';
	appendVehiculeList(ListeDesVehicules, Veh);
}

Vehicule* oldVehiculeSpawner(int posX, int posY, Direction Direction)
{
	Vehicule* Veh=malloc(sizeof(Vehicule));
	Veh->posX=posX;
	Veh->posY=posY;
	Veh->Direction=Direction;
	return Veh;
}

void visualiserVehiculeList(VehiculeList *List)
{
	VehiculeList *tmp;
	tmp = List;

	while (tmp != NULL) 
	{
			printf("posX:%d\n",tmp->Vehicule->posX);
			printf("posY:%d\n",tmp->Vehicule->posY);
			tmp = tmp->next;
	}
}

void setNewVehiculeDirection(Vehicule* Vehicule, char ** MatriceDecision, VehiculeList *ListeDesVehicules)
{
	switch(MatriceDecision[Vehicule->posX][Vehicule->posY])
	{
	
	case 'd':
		Vehicule->Direction = EST; break;
	case 'h':
		Vehicule->Direction = NORD; break;
	case 'b':
		Vehicule->Direction = SUD; break;
	case 'g':
		Vehicule->Direction = OUEST; break;
	case 'z':
		if(Vehicule->virage != 2)
		{
			Vehicule->Direction = directionAleatoire(EST,NORD); break;
			Vehicule->virage = Vehicule->virage +1;
		}
		else
		{
			Vehicule->virage = 0;
		}
	case 'v':
		if(Vehicule->virage != 2)
		{
			Vehicule->Direction = directionAleatoire(SUD,OUEST); break;
			Vehicule->virage = Vehicule->virage +1;
		}
		else
		{
			Vehicule->virage = 0;
		}
	case 'x':
		if(Vehicule->virage != 2)
		{
			Vehicule->Direction = directionAleatoire(OUEST,NORD); break;
			Vehicule->virage = Vehicule->virage +1;
		}
		else
		{
			Vehicule->virage = 0;
		}
	case 'y':
		if(Vehicule->virage != 2)
		{
			Vehicule->Direction = directionAleatoire(EST,SUD); break;
			Vehicule->virage = Vehicule->virage +1;
		}
		else
		{
			Vehicule->virage = 0;
		}
	case 'E':
		vehiculeEater(&ListeDesVehicules,Vehicule);
	case 'a':
		if(Vehicule->Carburant == FAIBLE)
		{
			Vehicule->Direction = SUD;
		}
		// FAIRE UNE ANIMATION?
	}
}

Direction directionAleatoire(Direction A, Direction B)
{
	int i = rand()%2;
	if (i%2==1) {
			return A;
	}
	else {

			return B;
	}
}


void placeTerminale(int posX, int posY)
{
	printf("\033[%d;%dH",posX,posY);
}

void affichageVehicule(Vehicule* V)
{
/*
🚔
🏇
🔥
🚖
🚍
🚘
*/	switch(V->custom)
	{
		case 'v': 
			couleur("32");
			printf("\033[%d;%dH🚘\n",V->posX,V->posY);
			couleur("0");
			break;

		case 'o': 
			couleur("33");
			printf("\033[%d;%dH🚘\n",V->posX,V->posY);
			couleur("0");
			break;

		case 'r': 
			couleur("31");
			printf("\033[%d;%dH🔥\n",V->posX,V->posY);
			couleur("0");
			break;

		case 'b': 
			couleur("35");
			printf("\033[%d;%dH🚘\n",V->posX,V->posY);
			couleur("0");
			break;

		case 's': printf("\033[%d;%dH🚍\n",V->posX,V->posY);break;
	}
}

char AleatoireCustomVehicule()
{
	switch(rand()%5)
	{
		case 0: 
		return 'v'; break;
		case 1: 
		return 'r'; break;
		case 2:
		return 'o'; break;
		case 3:
		return 'b'; break;
		default:
		return 's'; break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
void affichagePartielVehicule(char ** MatriceMap, Vehicule * V){

	char caractere;;
	
	for(int i = 0; i<2; i++){

		caractere = MatriceMap[V->posX][V->posY+i];

		printf("\033[%d;%dH",V->posX,V->posY+i);
		
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

void animationDeRemplissage(Vehicule * V)
{
	switch(V->Compteur)
	{
		case 0: printf("\033[%d;%dH🚶", V->posX-1, V->posY);
				couleur("35");
				printf("\033[%d;%dH", V->posX+1, V->posY-3);printf("╭═════╮");
				printf("\033[%d;%dH", V->posX+2, V->posY-3);printf("╰═════╯");
				couleur("0");
				break;

		case 1: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 2: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 3: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 4: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 5: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 6: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 7: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 8: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 9: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 10: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 11: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 12: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 13: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 14: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 15: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 16: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 17: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 18: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 19: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 20: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 21: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 22: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 23: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 24: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 25: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 26: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 27: couleur("35");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		case 28: couleur("34");printf("\033[%d;%dH╭", V->posX-1, V->posY-1);couleur("0");break;
		
		case 29: printf("\033[%d;%dH ", V->posX-1, V->posY-1);break;
		case 30: printf("\033[%d;%dH ", V->posX-1, V->posY);
				printf("\033[%d;%dH", V->posX+1, V->posY-3);printf("╭─────╮");
				printf("\033[%d;%dH", V->posX+2, V->posY-3);printf("╰─────╯");
				//EFFACER PIETON
				break;
	}//🚶🏃‍🚶‍🏃
	//on prend une voiture puis on fait l'animation en un certain nombre de frame comme pour la barriere.
	//le personnage sort de son vehicule
	//bouge
	//fait le plein
	//reviens vers sa porte
	//rentre dans sa voiture
}