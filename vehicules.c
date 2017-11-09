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


void roulementVehiculesPosition(char** MatriceDecision, VehiculeList** ListeDesVehicules)
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
					//affichageVoiture(tmp->Vehicule);
					//ANIMATION DE REMPLISSAGE DU PLEIN?
					tmp->Vehicule->Compteur = tmp->Vehicule->Compteur +1;
				}

				else
				{
				MatriceDecision[tmp->Vehicule->posX][tmp->Vehicule->posY] = tmp->Vehicule->CaseDecision; //La ou la voiture etait devient de la route (place libre)
				setNewPositionVehicule(tmp->Vehicule); //On actualise la position de la voiture dans la structure 
				tmp->Vehicule->CaseDecision = MatriceDecision[NextPosition->posX][NextPosition->posY]; // MAJ de la case decision
				setNewVehiculeDirection(tmp->Vehicule, MatriceDecision, *ListeDesVehicules); //On actualise la Direction du vehicule
				MatriceDecision[NextPosition->posX][NextPosition->posY] = 'c'; //On actualise la MatricePositionVehicules pour signaler qu'une voiture se trouve maintenant a cette position
				//affichageVoiture(tmp->Vehicule);
				}
			}
			else 
			{
				//affichageVoiture(tmp->Vehicule);
				
			}
			tmp = tmp->next;
			free(NextPosition);
		}
}


void vehiculeEater(VehiculeList **List, Vehicule* Vehicule)
{
	VehiculeList* PointeurCourant;
	VehiculeList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next){
			if (PointeurCourant->Vehicule == Vehicule){
				if (PointeurPrecedent == NULL){ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
					*List = PointeurCourant->next;} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
				else{
					PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
									}
			free(PointeurCourant);break;
								}
						}
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
	printf("\33[%d;%dH",posX,posY);
}

void affichageVehicule(Vehicule* V){
	switch(V->custom){
		case 'v': couleur("42");
			printf("\033[%d;%dH%c",V->posY,V->posX,V->custom);
			couleur("0");
		case 'o': couleur("43");
			printf("\033[%d;%dH%c",V->posY,V->posX,V->custom);
			couleur("0");
		case 'r': couleur("41");
			printf("\033[%d;%dH%c",V->posY,V->posX,V->custom);
			couleur("0");
		case 'b': couleur("45");
			printf("\033[%d;%dH%c",V->posY,V->posX,V->custom);
			couleur("0");
		case 's': couleur("47");
			printf("\033[%d;%dH%c",V->posY,V->posX,V->custom);
			couleur("0");
	}
	
}

