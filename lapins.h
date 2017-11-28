#ifndef position

typedef struct Position
{
	int posX;
	int posY;
			
} Position;

#endif

	typedef struct Lapin
{
	int posX;
	int posY;
	char CaseDecision;
	int healthpoints;
} Lapin;

typedef struct LapinList // Liste chainee de tramways pour la gestion du trafic
{
	Lapin* Lapin;
	struct LapinList *next;
} LapinList;

void lapinSpawner(int posX, int posY, LapinList** ListeDesLapins);

void appendLapinList(LapinList** ListeDesLapins, Lapin* Lapin);

LapinList* lapinEater(LapinList **List, Lapin* Lapin);

void affichageLapin(Lapin* Lapin);

void affichagePartielLapin(char** MatriceMap, Lapin* Lapin);

Position* positionFutureLapin(Lapin* Lapin);

int Voisins(Lapin* Lapin, char** MatriceDecision);

void roulementLapinsPosition(char** MatriceMap, char** MatriceDecision, LapinList** ListeDesLapins);