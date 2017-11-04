#include "librairies.h"
#include "boats.h"




// FONCTIONS RELATIVES AUX BATEAUX ET A LEURS DECISIONS

Boat* BoatSpawner(int posX, int posY, Sens Sens)
{
	Boat* Boat=malloc(sizeof(Boat));
	Boat->posX=posX;
	Boat->posY=posY;
	Boat->Sens = Sens;
	return Boat;
}

void AppendBoatList(BoatList **List,Boat* Boat)
{
	BoatList *element;
	element = malloc(sizeof(*element));
	element->Boat = Boat;
	element->next = *List;
	*List = element;
}

void BoatEater(BoatList **List, Boat* Boat)
{
	BoatList* PointeurCourant;
	BoatList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for(PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next){
			if (PointeurCourant->Boat == Boat){
				if (PointeurPrecedent == NULL){ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
					*List = PointeurCourant->next;} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
				else{
					PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
									}
			free(PointeurCourant);break;
								}
						}
}

void VisualiserBoatList(BoatList *List)
{
	BoatList *tmp;
	tmp = List;
	while (tmp != NULL)
		{
			printf("posX:%d\n",tmp->Boat->posX);
			printf("posY:%d\n",tmp->Boat->posY);
			tmp = tmp->next;
		}
}
	
