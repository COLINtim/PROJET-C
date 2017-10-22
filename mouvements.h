#include "librairies.h"

typedef struct TRAMWAY{
	}TRAMWAY;

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

typedef struct Vehicule
{
	Direction Direction;
	int posX;
	int posY;
	int vitesse;
	type type;
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

/*
typedef struct Chrono Chrono{
	double Time;
	double Time_
*/


void vagues();
void feux();

TrafficLight *CreateTrafficLight(int posX, int posY, Color color); //Permet d'instancier un feu

void AppendList(TrafficLightList **list, TrafficLight*);	//Permet d'ajouter un feu a la liste chainee

void InitialisationTrafficLights();				//Fonction theorique permettant l'initialisation de tous les feux de la map (a mettre en debut de loadmap())

void ShowTrafficLight(TrafficLight TrafficLight);		//Permet d'afficher les informations relatives Ã  un feu (un peu inutile mais permet de tester la cohÃ©rence du code)

void VisualiserTrafficLightList(TrafficLightList *List);	//Permet d'afficher toutes les positions des feux en parcourant la liste chainee des feux (same)

clock_t StartChrono(double* montre);				//Fonction permettant de lancer un chronometre (marche pas encore)

double VisualiserChrono(double* montre);			//Fonction permettant de regarder le chronometre (marche pas encore)

void Roulement_feux(TrafficLightList *List);		//Fonction prenant en argument une liste de feu et incrÃ©mentant leur Ã©tat de 1 unitÃ©. (vert => orange, etc ... modulo 4)

void GestionDesFeux(TrafficLightList *List); //Fonction gÃ©rant les feux de la map en fonction d'un chronomÃ¨tre qu'elle initialise. Ici elle ne prend en argument qu'une seule Liste de Feux, mais on peut la gÃ©nÃ©raliser pour qu'elle en prenne plus. Tout dÃ©pend du choix qu'on fait sur la gestion des feux : 2 familles de feux, 1 famille de feux par carrefour ... etc
	 
