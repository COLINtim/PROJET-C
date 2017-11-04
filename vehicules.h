#include "librairies.h"

enum Direction // Enumeration des directions possibles pour un vehicule
{
	NORD,
	EST,
	OUEST,
	SUD,
};

typedef enum Direction Direction;

enum type	// Enumeration des differents types de vehicules
{
	Jaguar,
	Peugeot,
	Fiat,
	Porsche,
	Ferrari,
	Batmobile,
	Renault,
};

typedef enum type type;

enum Carburant	// Enumeration des differents etats du carburant pour un vehicule
{
	VIDE,
	FAIBLE,
	MOYEN,
	PLEIN,
};

typedef enum Carburant Carburant;

typedef struct Position
{
	int posX;
	int posY;
			
} Position;

typedef struct Vehicule
{
	Direction Direction;
	int posX;
	int posY;
	int vitesse;
	char custom[30];
	Carburant Carburant;
			
} Vehicule;

typedef struct VehiculeList // Liste chainee de vehicules pour la gestion du trafic
{
	Vehicule* Vehicule;
	struct VehiculeList *next;
} VehiculeList;

Position* PositionFuture(Vehicule* vehicule); //Fonction renvoyant un struct Position (qui sera la position de vehicule à la frame suivante) en fonction de sa Direction

void VehiculeEater(VehiculeList **List, Vehicule* Vehicule); //Fonction ayant pour but de supprimer de la liste VehiculeList les Vehicules sortant de la map. L'appeler lorsque PositionFuture(Vehicule) renvoit une position dont au moins une coordonnée est hors de la map

void AppendVehiculeList(VehiculeList **List, Vehicule* Vehicule); //Fonction permettant d'ajouter un Vehicule à la liste des Vehicules (à appeler après le Spawner)

Vehicule* VehiculeSpawner(int posX, int posY,Direction Direction); //renvoie un pointeur de vehicule ayant pour position (x,y) et pour Direction Direction

void VisualiserVehiculeList(VehiculeList *List); //permet de visualiser une liste de vehicules (affiche les positions de ces vehicules)

void NewVehiculeDirection(Vehicule* Vehicule, char ** MatriceDecision, VehiculeList *ListeDesVehicules); //Fonction determinant la direction future de la voiture en fonction de la case sur laquelle elle se trouve (carrefour, ou route) /!\ Etablir un code permettant de faire la disjonction de cas de cette fonction

void Deplacement(Vehicule* Vehicule); //Affiche le vehicule a sa prochaine position dans le terminal

Direction DirectionAleatoire(Direction A, Direction B);

void PlaceTerminale(int posX, int posY); //Fonction permettant de s'éviter la syntaxe trop lourde du placement du curseur dans le terminal

void NewPositionVehicule(Vehicule* vehicule); //Met a jour la position de la voiture dans sa struct
