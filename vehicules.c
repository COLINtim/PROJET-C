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
	if(MatriceDecision[i][j]!='c'||MatriceDecision[i][j]!='f')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


void roulementVehiculesPosition(char ** MatriceMap,char** MatriceDecision, VehiculeList** ListeDesVehicules)
{
	VehiculeList *tmp;
	tmp = *ListeDesVehicules;
	while (tmp != NULL)
		{	
			Position* NextPosition = positionFuture(tmp->Vehicule); // Afin de free plus tard
			if(Obstacle(MatriceDecision, NextPosition->posX, NextPosition->posY)==0)
			{
				if((MatriceDecision[NextPosition->posX][NextPosition->posY]=='P')&&((tmp->Vehicule->Compteur)<8))
				{
					affichageVehicule(tmp->Vehicule);
					//ANIMATION DE REMPLISSAGE DU PLEIN?
					tmp->Vehicule->Compteur = tmp->Vehicule->Compteur +1;
					tmp = tmp->next;
				}
				else
				{
					MatriceDecision[tmp->Vehicule->posX][tmp->Vehicule->posY] = tmp->Vehicule->CaseDecision; //La ou la voiture etait devient de la route (place libre)
					affichagePartielVehicule(MatriceMap, tmp->Vehicule);
					setNewPositionVehicule(tmp->Vehicule); //On actualise la position de la voiture dans la structure 
					tmp->Vehicule->CaseDecision = MatriceDecision[NextPosition->posX][NextPosition->posY]; // MAJ de la case decision
					if(tmp->Vehicule->CaseDecision == 'E')
					{
						affichagePartielVehicule(MatriceMap, tmp->Vehicule);
						tmp = vehiculeEater(ListeDesVehicules, tmp->Vehicule);

					}
					else
					{	
						affichagePartielVehicule(MatriceMap, tmp->Vehicule);
						setNewVehiculeDirection(tmp->Vehicule, MatriceDecision, *ListeDesVehicules); //On actualise la Direction du vehicule
						MatriceDecision[NextPosition->posX][NextPosition->posY] = 'c'; //On actualise la MatricePositionVehicules pour signaler qu'une voiture se trouve maintenant a cette position
						affichageVehicule(tmp->Vehicule);	
						tmp = tmp->next;
					}
				}
			}
			else 
			{
				affichagePartielVehicule(MatriceMap, tmp->Vehicule);
				affichageVehicule(tmp->Vehicule);
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
		Vehicule->Direction = directionAleatoire(EST,NORD); break;
	case 'v':
		Vehicule->Direction = directionAleatoire(SUD,OUEST); break;
	case 'x':
		Vehicule->Direction = directionAleatoire(OUEST,NORD); break;
	case 'y':
		Vehicule->Direction = directionAleatoire(EST,SUD); break;
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
			printf("\033[%d;%dH\🚘",V->posX,V->posY);
			couleur("0");
			break;

		case 'o': 
			couleur("33");
			printf("\033[%d;%dH\🚘",V->posX,V->posY);
			couleur("0");
			break;

		case 'r': 
			couleur("31");
			printf("\033[%d;%dH\🚘",V->posX,V->posY);
			couleur("0");
			break;

		case 'b': 
			couleur("35");
			printf("\033[%d;%dH\🚘",V->posX,V->posY);
			couleur("0");
			break;

		case 's': printf("\033[%d;%dHv\n",V->posX,V->posY);break;
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
void affichagePartielVehicule(char ** matrice, Vehicule * V){

	char caractere;;
	
	for(int i = 0; i<2; i++){

		caractere = matrice[V->posX][V->posY+i];

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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 
void helicoptereSpawner(int posX, int posY, HelicoptereList** ListeDesHelicopteres)
{
	Helicoptere* Helico=malloc(sizeof(Helicoptere));
	Helico->posX = posX;
	Helico->posY = posY;
	appendHelicoptereList(ListeDesHelicopteres, Helico);
}

void roulementHelicopteresPosition(ListeDesHelicopteres)
{

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
		Helicoptere* ptrToReturn = PointeurCourant->next;
		free(PointeurCourant);break;
		return ptrToReturn;
		}
	}
	return NULL;
}

void roulementHelicopteresPosition(char** MatriceDecision, HelicoptereList** ListeDesHelicopteres)
{
	HelicoptereList *tmp;
	tmp = *ListeHelicopteres;
	while (tmp != NULL)
		{	
			Position* NextPosition = positionFutureHelicoptere(tmp->Helicoptere); // Afin de free plus tard
			Helicoptere->posX = NextPosition->posX;
			Helicoptere->posY = NextPosition->posY;
			affichageHelicoptere(tmp->Helicoptere);
			free(NextPosition);
		}
}

void affichageHelicoptere(Helicoptere* Helico)
{
	couleur("32");
	printf("\033[%d;%dH🚁",Helico->posX,Helico->posY);

}

Position* positionFutureHelicoptere(Helicoptere* Helico)
{
	Position* Position = malloc(sizeof(Position));
	int i;
	i=rand()%2;
	switch(Helico->axe) 
	{
		case u: 
			Position->posX=(Helico->posX)-1;
			Position->posY=Helico->posY;
			if(i%2 == 0)
			{
				Helico->axe = a;
			}
			else
			{
				Helico->axe = b;
			}
			return Position;
		case r: 
			Position->posX=Helico->posX;
			Position->posY=(Helico->posY)+1;
			if(i%2 == 0)
			{
				Helico->axe = a;
			}
			else
			{
				Helico->axe = c;
			}
			return Position;
		case l: 
			Position->posX=Helico->posX;
			Position->posY=(Helico->posY)-1;
			if(i%2 == 0)
			{
				Helico->axe = b;
			}
			else
			{
				Helico->axe = e;
			}
			return Position;
		case d: 
			Position->posX=(Helico->posX)+1;
			Position->posY=Helico->posY;
			if(i%2 == 0)
			{
				Helico->axe = e;
			}
			else
			{
				Helico->axe = c;
			}
			return Position;
		case a: 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)-1;
				Position->posY=Helico->posY;	
			}
			else
			{
				Position->posX=Helico->posX;
				Position->posY=(Helico->posY)+1;
			}
			return Position;
		case b: 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)-1;
				Position->posY=Helico->posY;
			}
			else
			{
				Position->posX=Helico->posX;
				Position->posY=(Helico->posY)-1;
			}
			return Position;
		case c: 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)+1;
				Position->posY=Helico->posY;
			}
			else
			{
				Position->posX=Helico->posX;
				Position->posY=(Helico->posY)+1;
			}
		case e: 
			if(i%2 == 0)
			{
				Position->posX=(Helico->posX)+1;
				Position->posY=Helico->posY;
			}
			else
			{
				Position->posX=Helico->posX;
				Position->posY=(Helico->posY)+1;
			}
		default:
			Position->posX = Helico->posX;
			Position->posY = Helico->posY;
			return Position;
	}
}

//Helico trajectoire diagonale en moyenne : u=UP ; r=RIGHT ; l=LEFT ; d=DOWN ; a=UP&&RIGHT ; b=UP&&LEFT ; c=DOWN&&RIGHT ; e=DOWN&&LEFT

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////:

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////