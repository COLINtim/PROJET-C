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

	typedef struct Pieton
{
	int posX;
	int posY;
	int vitesse;
	char CaseDecision;
	Direction Direction;

} Pieton;

typedef struct PietonList // Liste chainee de tramways pour la gestion du trafic
{
	Pieton* Pieton;
	struct PietonList *next;
} PietonList;

void pietonSpawner(int posX, int posY, Direction Direction, PietonList** ListeDesPietons); 

void appendPietonList(PietonList** ListeDesPietons, Pieton* Pieton);

PietonList* pietonEater(PietonList **List, Pieton* Pieton);

void affichagePieton(Pieton* Pieton);

void affichagePartielPieton(char ** MatriceMap, Pieton* Pieton);

void setNewPietonDirection(Pieton* Pieton, char ** MatriceDecision, PietonList *ListeDesPietons);

Position* positionFuturePieton(Pieton* Pieton);

int ObstaclePieton(char ** MatriceDecision, int i, int j);

void roulementPietonsPosition(char ** MatriceMap, char** MatriceDecision, PietonList** ListeDesPietons);

