#include "librairies.h"

#define boats


enum Sens // Enumeration des directions possibles pour un vehicule
{
	HAUT,
	DROITE,
	GAUCHE,
	BAS,
};

typedef enum Sens Sens;

enum Modele	// Enumeration des differents types de vehicules
{
	Voilier,
	Catamaran,
	Barque,
	Flotteur,
	Bateau_de_Croisiere,
	Ferry,
};

typedef enum Modele Modele;

typedef struct Boat{
	int posX;
	int posY;
	char custom;
	Sens Sens;	
	char CaseDecision;
	}Boat;

typedef struct Coordonnees
{
	int posX;
	int posY;
			
} Coordonnees;

typedef struct BoatList // Liste chainee des Bateaux
{
	Boat* Boat;
	struct BoatList *next;
} BoatList;

void boatSpawner(int posX, int posY, Sens Sens, char a, char** MatriceDecision, BoatList** ListeDesBoats); //Fonction initialisant un Bateau allant dans la Direction Direction a la position (posX,posY)

void appendBoatList(BoatList **List,Boat* Boat); //Fonction ajoutant un Boat a une BoatList

BoatList* boatEater(BoatList **List, Boat* Boat); //Supprime un element d'une BoatList

void visualiserBoatList(BoatList *List); //Affiche les positions des differents bateaux contenus dans la BoatList

Sens sensAleatoire(Sens A, Sens B); // Renvoie aléatoirement le Sens A ou B

void setNewPositionBoat(Boat* Boat); //Met a jour la position du boat dans sa struct

void setNewBoatSens(Boat* Boat, char ** MatriceDecision, BoatList *ListeDesBoats); //Met a jour le Sens du boat en fonction du coefficient de la MatriceDecision sur lequel il se trouve

void roulementBoatsPosition(char ** MatriceMap,char** MatriceDecision, BoatList **List); // Met a jour toutes les positions des boat d'une BoatList

Coordonnees* positionFutureBoat(Boat* Boat); //Renvoie un struct Coordonnees qui est la position future du Boat

void affichageBoat(Boat* B); //Fonction d'affichage de bateau

void EaterOrNot(Boat* Boat, BoatList** ListeDesBoats); //Fonction testant si oui ou non le bateau est en fin de map

char AleatoireCustomBoat(); //Renvoie aleatoirement un skin de bateau

void affichagePartielBoat(char ** matrice, Boat * B);