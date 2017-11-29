#ifndef position

typedef struct Position
{
	int posX;
	int posY;
			
} Position;

#endif

#ifndef direction

enum Direction // Enumeration des directions possibles pour une entité
{
	NORD,
	EST,
	OUEST,
	SUD,
};

typedef enum Direction Direction;

#endif

#ifndef tram

#define tram

	typedef struct Tramway
{
	int posX;
	int posY;
	int vitesse;
	char CaseDecision;
	Direction Direction;
	int compteur;
	int compteur2;
	int virage;
} Tramway;

#endif
typedef struct TramwayList // Liste chainee de tramways pour la gestion du trafic
{
	Tramway* Tramway;
	struct TramwayList *next;
} TramwayList;

typedef struct TramwayEater
{
	int decr;
	
} TramwayEater; 

void tramwaySpawner(int posX, int posY, Direction Direction, TramwayList** ListeDesTramways); //Fait apparaitre un Tramway (Spawner) //Fait apparaitre un Tramway (Spawner)

void appendTramwayList(TramwayList** ListeDesTramways, Tramway* Tram); // Fonction ajoutant un wagon de Tramway à une Liste de Tramways

TramwayList* tramwayEater(TramwayList **List, Tramway* Tramway); // Eater de Tramway

void affichageTramway(char** MatriceMap, Tramway* Tram); // Affiche un wagon de Tramway

void roulementTramwaysPosition(char** MatriceMap, char** MatriceDecision, TramwayList** ListeDesTramways, TramwayEater* TramwayEater1, TramwayEater* TramwayEater2); // Fait avancer tous les Tramways présents dans la ListeDesTramways

void setNewTramwayDirection(Tramway* Tramway, char ** MatriceDecision, TramwayList *ListeDesTramways); // Met a jour la position du Tramway dans sa structure

Position* positionFutureTramway(Tramway* Tramway); // Renvoit la position future d'un wagon de Tramway

int ObstacleTramway(char ** MatriceDecision, int i, int j); //Fonction faisant la disjontion de cas pour le Tramway afin de rendre roulementTramwaysPosition plus lisible

void affichagePartielTramway(char ** MatriceMap, Tramway * Tramway);

int testPositionTramway(Tramway* Tramway);

TramwayEater* tramwayEaterInit();

void eaterAffichage(TramwayEater* TramwayEater, int NumeroDeLigne);

void feuxDeTram(char ***MatriceDecision, char **MatriceMap, Tramway * T1, Tramway * T2);

int compteurDeTramways(TramwayList** ListeDesTramways);