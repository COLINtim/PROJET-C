#include "librairies.h"

typedef struct Tramway{
	int vitesse;
	char custom[30];
	int longueur;
	}Tramway;

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

enum Color	//Enumeration des couleurs pour les feux
{
	VERT,
	ORANGE,
	ROUGE,
	ROUGEINTER
};

typedef enum Color Color;

enum Timers	//Enumeration des temps requis pour les roulements des feux 
{
	TIMER_GREEN = 6,
	TIMER_ORANGE = 3,
	TIMER_ROUGE = 9,
	TIMER_ROUGEINTER = 1
};

typedef enum Timers Timers;

typedef struct TrafficLight	
{
	Color Current_Color;
	Timers TimeForSwitch;
	int posX;
	int posY;
} TrafficLight;


typedef struct TrafficLightList // Liste chainee des feux pour le roulement des feux sur la carte
{
	TrafficLight* TrafficLight;
	struct TrafficLightList *next;
} TrafficLightList;

typedef struct Boat{
	int posX;
	int posY;
	char custom[30];
	Direction Direction;	
	}Boat;

typedef struct BoatList // Liste chainee des Bateaux
{
	Boat* Boat;
	struct BoatList *next;
} BoatList;

/*
typedef struct Chrono Chrono{
	double Time;
	double Time_
*/

void AppendBoatList(BoatList **List,Boat* Boat);

void vagues();
void feux();

TrafficLight *CreateTrafficLight(int posX, int posY, Color color); //Permet d'instancier un feu

void AppendList(TrafficLightList **list, TrafficLight*);	//Permet d'ajouter un feu a la liste chainee

void InitialisationTrafficLights();				//Fonction theorique permettant l'initialisation de tous les feux de la map (a mettre en debut de loadmap())

void ShowTrafficLight(TrafficLight TrafficLight);		//Permet d'afficher les informations relatives à un feu (un peu inutile mais permet de tester la cohérence du code)

void VisualiserTrafficLightList(TrafficLightList *List);	//Permet d'afficher toutes les positions des feux en parcourant la liste chainee des feux (same)

clock_t StartChrono(double* montre);				//Fonction permettant de lancer un chronometre (marche pas encore)

double VisualiserChrono(double* montre);			//Fonction permettant de regarder le chronometre (marche pas encore)

void Roulement_feux(TrafficLightList *List);		//Fonction prenant en argument une liste de feu et incrémentant leur état de 1 unité. (vert => orange, etc ... modulo 4)

void GestionDesFeux(TrafficLightList *List); //Fonction gérant les feux de la map en fonction d'un chronomètre qu'elle initialise. Ici elle ne prend en argument qu'une seule Liste de Feux, mais on peut la généraliser pour qu'elle en prenne plus. Tout dépend du choix qu'on fait sur la gestion des feux : 2 familles de feux, 1 famille de feux par carrefour ... etc

Position* PositionFuture(Vehicule* vehicule); //Fonction renvoyant un struct Position (qui sera la position de vehicule à la frame suivante) en fonction de sa Direction

void VehiculeEater(VehiculeList **List, Vehicule* Vehicule); //Fonction ayant pour but de supprimer de la liste VehiculeList les Vehicules sortant de la map. L'appeler lorsque PositionFuture(Vehicule) renvoit une position dont au moins une coordonnée est hors de la map

void AppendVehiculeList(VehiculeList **List, Vehicule* Vehicule); //Fonction permettant d'ajouter un Vehicule à la liste des Vehicules (à appeler après le Spawner)

Vehicule* VehiculeSpawner(int posX, int posY,Direction Direction); //renvoie un pointeur de vehicule ayant pour position (x,y) et pour Direction Direction

void VisualiserVehiculeList(VehiculeList *List); //permet de visualiser une liste de vehicules (affiche les positions de ces vehicules)

void Decision(Vehicule* Vehicule, char ** map); //Fonction determinant la direction future de la voiture en fonction de la case sur laquelle elle se trouve (carrefour, ou route) /!\ Etablir un code permettant de faire la disjonction de cas de cette fonction

void Deplacement(Vehicule* Vehicule); //Affiche le vehicule a sa prochaine position dans le terminal

void PlaceTerminale(int posX, int posY); //Fonction permettant de s'éviter la syntaxe trop lourde du placement du curseur dans le terminal

Boat* BoatSpawner(int posX, int posY, Direction Direction); //Fonction initialisant un Bateau allant dans la Direction Direction a la position (posX,posY)

void AppendBoatList(BoatList **List,Boat* Boat); //Fonction ajoutant un Boat a une BoatList

void BoatEater(BoatList **List, Boat* Boat); //Supprime un element d'une BoatList

void VisualiserBoatList(BoatList *List); //Affiche les positions des differents bateaux contenus dans la BoatList
