#include "librairies.h"
#include "vehicules.h"

// FONCTIONS RELATIVES AUX VEHICULES ET A LEURS DECISIONS

Position* PositionFuture(Vehicule* vehicule)
{
	Position* Position = NULL;
	switch(vehicule->Direction) 
	{
		case NORD: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)+1;
			return Position;
		case EST: 
			Position->posX=(vehicule->posX)+1;
			Position->posY=vehicule->posY;
			return Position;
		case OUEST: 
			Position->posX=(vehicule->posX)-1;
			Position->posY=vehicule->posY;
			return Position;
		default: 
			Position->posX=vehicule->posX;
			Position->posY=(vehicule->posY)-1;
			return Position;
	}
}

void NewPositionVehicule(Vehicule* vehicule)
{
	vehicule->posX = PositionFuture(vehicule)->posX;
	vehicule->posY = PositionFuture(vehicule)->posY;
}


void RoulementVehiculePositionListAndMatrix(char** MatriceDecision, char** MatricePositionVehicules, VehiculeList **List)
{
	VehiculeList *tmp;
	tmp = *List;
	while (tmp != NULL)
		{
			if(MatricePositionVehicules[PositionFuture(tmp->Vehicule)->posX][PositionFuture(tmp->Vehicule)->posY]=='o')
			{
				MatricePositionVehicules[tmp->Vehicule->posX][tmp->Vehicule->posY]='o'; //La ou la voiture etait devient de la route (place libre)
				NewPositionVehicule(tmp->Vehicule); //On actualise la position de la voiture dans la structure
				NewVehiculeDirection(tmp->Vehicule,MatriceDecision, *List); //On actualise la Direction de la voiture en fonction de la MatriceDecision
				MatricePositionVehicules[tmp->Vehicule->posX][tmp->Vehicule->posY]='c'; //On actualise la MatricePositionVehicules pour signaler qu'une voiture se trouve maintenant a cette position
			}
			else if(MatricePositionVehicules[PositionFuture(tmp->Vehicule)->posX][PositionFuture(tmp->Vehicule)->posY]=='c')
			{

			}
			else if(MatricePositionVehicules[PositionFuture(tmp->Vehicule)->posX][PositionFuture(tmp->Vehicule)->posY]=='f')
			{

			}
		}
}


void VehiculeEater(VehiculeList **List, Vehicule* Vehicule)
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

	
void AppendVehiculeList(VehiculeList **List, Vehicule* Vehicule)
{
	VehiculeList *element;
	element = malloc(sizeof(*element));
	element->Vehicule = Vehicule;
	element->next = *List;
	*List = element;
}

Vehicule* VehiculeSpawner(int posX, int posY, Direction Direction)
{
	Vehicule* Veh=malloc(sizeof(Vehicule));
	Veh->posX=posX;
	Veh->posY=posY;
	Veh->Direction=Direction;
	return Veh;
}

void VisualiserVehiculeList(VehiculeList *List)
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

void NewVehiculeDirection(Vehicule* Vehicule, char ** MatriceDecision, VehiculeList *ListeDesVehicules)
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
		Vehicule->Direction = DirectionAleatoire(EST,NORD); break;
	case 'v':
		Vehicule->Direction = DirectionAleatoire(SUD,OUEST); break;
	case 'x':
		Vehicule->Direction = DirectionAleatoire(OUEST,NORD); break;
	case 'y':
		Vehicule->Direction = DirectionAleatoire(EST,SUD); break;
	case 'E':
		VehiculeEater(&ListeDesVehicules,Vehicule);
	}
}

Direction DirectionAleatoire(Direction A, Direction B)
{
	int i = rand()%2;
	if (i%2==0){
			return A;}
	else{
			return B;}
}


void PlaceTerminale(int posX, int posY)
{
	printf("\33[%d;%dH",posX,posY);
}
	

