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

BoatList* boatEater(BoatList **List, Boat* Boat)
{
	BoatList* PointeurCourant;
	BoatList* PointeurPrecedent;
	PointeurPrecedent = NULL; //pas de pointeur precedent pour le 1er element de la liste
	for (PointeurCourant = *List; PointeurCourant != NULL; PointeurPrecedent = PointeurCourant, PointeurCourant = PointeurCourant->next)
	{
			if (PointeurCourant->Boat == Boat)
			{
				if (PointeurPrecedent == NULL)
					{ 	/*cas ou on voudrait en fait supprimer le 1er element de la liste (Particulier)	*/
						*List = PointeurCourant->next;
					} /*on dit juste que le 1er element est en fait le 2e, et on free plus bas */
				else 
					{
						PointeurPrecedent->next = PointeurCourant->next; // on skip l'element a supprimer									
					}
					BoatList* ptrToReturn = PointeurCourant->next;
					free (PointeurCourant);break;
					return ptrToReturn;
			}
	}
return NULL;
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
		Boat->Sens = sensAleatoire(DROITE,HAUT); break;
	case 'y':
		Boat->Sens = sensAleatoire(DROITE,BAS); break;
	case 'E':
		break;
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

void roulementBoatsPosition(char ** MatriceMap,char** MatriceDecision, BoatList** ListeDesBoats)
{
	BoatList *tmp;
	tmp = *ListeDesBoats;
	while (tmp !=NULL)
	{
		Coordonnees* NextCoordonnees = positionFutureBoat(tmp->Boat); //astuce pour bien gerer la memoire et free apres
		if(MatriceDecision[NextCoordonnees->posX][NextCoordonnees->posY]=='L')
		{
			affichageBoat(tmp->Boat);
			tmp = tmp->next;
		}
		else
		{
			if(tmp->Boat->CaseDecision == 'D') // S'il passe sous un pont
			{
					MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = tmp->Boat->CaseDecision; //On remet le D à sa place
					affichagePartielBoat(MatriceMap,tmp->Boat); 
					setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
					tmp->Boat->CaseDecision = 'F'; // Mode fantome, le bateau est sous le pont
					tmp = tmp->next;
			}
			else if(tmp->Boat->CaseDecision == 'F') //Mode fantome, le bateau est sous le pont
			{
					if(MatriceDecision[NextCoordonnees->posX][NextCoordonnees->posY]=='A')
					{	
						affichagePartielBoat(MatriceMap,tmp->Boat);
						setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
						tmp->Boat->CaseDecision = MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]; //Mise à jour de sa CaseDecision
						MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = 'L'; // Mise a jour de la MatriceDecison
						affichageBoat(tmp->Boat);
						tmp = tmp->next;
					}
					else{
					setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
					tmp = tmp->next;
						}
			}
			else
			{

			MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = tmp->Boat->CaseDecision; //La case ou se trouvait le bateau redevient de l'eau
			affichagePartielBoat(MatriceMap,tmp->Boat);
			setNewPositionBoat(tmp->Boat); // Mise a jour de la position du Boat dans sa structure
			tmp->Boat->CaseDecision = MatriceDecision[tmp->Boat->posX][tmp->Boat->posY]; //Mise à jour de sa CaseDecision
			setNewBoatSens(tmp->Boat, MatriceDecision, *ListeDesBoats); //Mise a jour de la Direction du Bateau en fonction de la ou il se situe sur la MatriceDecison
			MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = 'L'; // Mise a jour de la MatriceDecison
			affichageBoat(tmp->Boat);
				if (tmp->Boat->CaseDecision == 'E')
				{
					affichagePartielBoat(MatriceMap,tmp->Boat);
					MatriceDecision[tmp->Boat->posX][tmp->Boat->posY] = 'E';
					tmp = boatEater(ListeDesBoats, tmp->Boat);
					couleur("46");printf("\033[%d;%dH \n",NextCoordonnees->posX,NextCoordonnees->posY);couleur("0");
				}
				else
				{
					tmp = tmp->next;	
				}
			}
		}
		free(NextCoordonnees);
	}
}

void affichageBoat(Boat* B){
	switch(B->custom){
		case 'v': 
		couleur("30");
		couleur("46");
			printf("\033[%d;%dH⛴\n",B->posX,B->posY);
			couleur("0");
			break;
		case 'o': 
		couleur("30");
		couleur("46");
			printf("\033[%d;%dH⛴\n",B->posX,B->posY);
			couleur("0");
			break;
		case 'r': 
		couleur("30");
		couleur("46");
			printf("\033[%d;%dH⛴\n",B->posX,B->posY);
			couleur("0");
			break;
		case 'b': 
		couleur("30");
		couleur("46");
			printf("\033[%d;%dH⛴\n",B->posX,B->posY);
			couleur("0");
			break;
	}
}

char AleatoireCustomBoat()
{
	switch(rand()%4)
	{
		case 0: 
		return 'v'; break;
		case 1: 
		return 'r'; break;
		case 2:
		return 'o'; break;
		default:
		return 'b'; break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
void affichagePartielBoat(char ** matrice, Boat * B){

	char caractere;;
	
	for(int i = 0; i<2; i++){

		caractere = matrice[B->posX][B->posY+i];

		printf("\033[%d;%dH",B->posX,B->posY+i);
		
		switch(caractere){
				//herbe
				case '#': couleur("38;5;46");printf("♨");couleur("0");break;
				case '?': couleur("48;5;22");printf(" ");couleur("0");break;
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
				case '%': printf("▒");break;
				case '*': printf("▓");break;
				//caracteres par default
				default: printf("%c",caractere);break;
		}
	}			
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

