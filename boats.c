#include "librairies.h"
#include "boats.h"


// FONCTIONS RELATIVES AUX BATEAUX ET A LEURS DECISIONS

void appendBoatList(BoatList** ListeDesBoats, Boat* Boat)
{
	BoatList *element;
	element = calloc(1,sizeof(*element));
	element->Boat = Boat;
	element->next = *ListeDesBoats;
	*ListeDesBoats = element;
}

void boatSpawner(int posX, int posY, Sens Sens, char a, char** MatriceDecision, BoatList** ListeDesBoats)
{
	Boat* Bateau = calloc(1,sizeof(Boat));
	Bateau->posX = posX;
	Bateau->posY = posY;
	Bateau->Sens = Sens;
	Bateau->custom = a;
	Bateau->CaseDecision = 'S';
	MatriceDecision[posX][posY] = 'L';
	appendBoatList(ListeDesBoats, Bateau);
}

void boatEater(BoatList **List, Boat* Boat)
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

void visualiserBoatList(BoatList *List)
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

Sens sensAleatoire(Sens A, Sens B)
{
	int i = rand()%2;
	if (i%2==0) 
	{
			return A;
	}
	else{
			return B;
		}
}

void setNewPositionBoat(Boat* Boat)
{
	Boat->posX = positionFutureBoat(Boat)->posX;
	Boat->posY = positionFutureBoat(Boat)->posY;
}
	
void setNewBoatSens(Boat* Boat, char ** MatriceDecision, BoatList *ListeDesBoats)
{
	switch(MatriceDecision[Boat->posX][Boat->posY])
	{
	case 'd':
		Boat->Sens = DROITE; break;
	case 'h':
		Boat->Sens = HAUT; break;
	case 'b':
		Boat->Sens = BAS; break;
	case 'g':
		Boat->Sens = GAUCHE; break;
	case 'x':
		Boat->Sens = sensAleatoire(GAUCHE,HAUT); break;
	case 'y':
		Boat->Sens = sensAleatoire(DROITE,BAS); break;
	case 'E':
		boatEater(&ListeDesBoats,Boat);
	}
}

Coordonnees* positionFutureBoat(Boat* Boat)
{
	Coordonnees* Coordonnees = malloc(sizeof(Coordonnees));
	switch(Boat->Sens) 
	{
		case HAUT: 
			Coordonnees->posX = (Boat->posX)-1;
			Coordonnees->posY = Boat->posY;
			return Coordonnees;
		case DROITE: 
			Coordonnees->posX = Boat->posX;
			Coordonnees->posY = (Boat->posY)+1;
			return Coordonnees;
		case GAUCHE: 
			Coordonnees->posX = Boat->posX;
			Coordonnees->posY = (Boat->posY)-1;
			return Coordonnees;
		case BAS: 
			Coordonnees->posX = (Boat->posX)+1;
			Coordonnees->posY = Boat->posY;
			return Coordonnees;
		default:
			Coordonnees->posX = Boat->posX;
			Coordonnees->posY = Boat->posY;
			return Coordonnees;

	}
}

void roulementBoatsPosition(char** MatriceDecision, BoatList** ListeDesBoats)
{
	BoatList *tmp;
	tmp = *ListeDesBoats;
	while (tmp !=NULL)
	{
		Coordonnees* NextCoordonnees = positionFutureBoat(tmp->Boat); //astuce pour bien gerer la memoire et free apres
		if(MatriceDecision[NextCoordonnees->posX][NextCoordonnees->posY]!='L')
		{
			if(tmp->Boat->CaseDecision == 'D') // S'il passe sous un pont
			{
					MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = tmp->Boat->CaseDecision; //On remet le D à sa place
					setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
					tmp->Boat->CaseDecision = 'F'; // Mode fantome, le bateau est sous le pont
			}
			else if(tmp->Boat->CaseDecision == 'E') // Si la case ou il se trouve est un Eater (fin de map)
			{
					boatEater(ListeDesBoats, tmp->Boat);
			}
			else if(tmp->Boat->CaseDecision == 'F') //Mode fantome, le bateau est sous le pont
			{
					if(MatriceDecision[NextCoordonnees->posX][NextCoordonnees->posY]=='A')
					{
						setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
						tmp->Boat->CaseDecision = MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]; //Mise à jour de sa CaseDecision
						MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = 'L'; // Mise a jour de la MatriceDecison
						affichageBoat(tmp->Boat);
					}
					else{
					setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
						}
			}
			else
			{
			MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = tmp->Boat->CaseDecision; //La case ou se trouvait le bateau redevient de l'eau
			setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
			tmp->Boat->CaseDecision = MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]; //Mise à jour de sa CaseDecision
			setNewBoatSens(tmp->Boat, MatriceDecision, *ListeDesBoats); //Mise a jour de la Direction du Bateau en fonction de la ou il se situe sur la MatriceDecison
			MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = 'L'; // Mise a jour de la MatriceDecison
			affichageBoat(tmp->Boat);
			}
		}
		else
		{
			//Printf le bateau a la meme position
		}
		tmp = tmp->next;
		free(NextCoordonnees);
	}
}

void affichageBoat(Boat* B){
	switch(B->custom){
		case 'v': couleur("46");
			printf("\033[%d;%dH⛵️",B->posX,B->posY);
			couleur("0");
			break;
		case 'o': couleur("46");
			printf("\033[%d;%dH🛥",B->posX,B->posY);
			couleur("0");
			break;
		case 'r': couleur("46");
			printf("\033[%d;%dH🍩",B->posX,B->posY);
			couleur("0");
			break;
		case 'b': couleur("46");
			printf("\033[%d;%dH⛴",B->posX,B->posY);
			couleur("0");
			break;
		case 's': couleur("46");
			printf("\033[%d;%dH🚘",B->posX,B->posY);
			couleur("0");
			break;
	}
}
