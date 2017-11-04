#include "librairies.h"


enum Sens // Enumeration des directions possibles pour un vehicule
{
	HAUT,
	DROITE,
	GAUCHE,
	BAS,
};

typedef enum Sens Sens;

typedef struct Boat{
	int posX;
	int posY;
	char custom[30];
	Sens Sens;	
	}Boat;

typedef struct BoatList // Liste chainee des Bateaux
{
	Boat* Boat;
	struct BoatList *next;
} BoatList;

Boat* BoatSpawner(int posX, int posY, Sens Sens); //Fonction initialisant un Bateau allant dans la Direction Direction a la position (posX,posY)

void AppendBoatList(BoatList **List,Boat* Boat); //Fonction ajoutant un Boat a une BoatList

void BoatEater(BoatList **List, Boat* Boat); //Supprime un element d'une BoatList

void VisualiserBoatList(BoatList *List); //Affiche les positions des differents bateaux contenus dans la BoatList
