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

	typedef struct Helicoptere
{
	int posX;
	int posY;
	char axe;
} Helicoptere;

typedef struct HelicoptereList // Liste chainee d'helicopteres pour la gestion du trafic
{
	Helicoptere* Helicoptere;
	struct HelicoptereList *next;
} HelicoptereList;

void helicoptereSpawner(int posX, int posY,char axe, HelicoptereList** ListeDesHelicopteres); //Spawner d'Helicoptere

void roulementHelicopteresPosition(char** MatriceMap, char** MatriceDecision, HelicoptereList** ListeDesHelicopteres); // Fait avancer tous les Helicopteres d'une Liste D'helicopteres

void appendHelicoptereList(HelicoptereList** ListeDesHelicopteres, Helicoptere* Helico); // Ajoute un helicoptere a Une Liste d'helicopteres

HelicoptereList* helicoptereEater(HelicoptereList **List, Helicoptere* Helicoptere); // Fait disparaitre et désalloue dynamiquement un helicoptere

void affichagePartielHelicoptere(char ** MatriceMap, Helicoptere * Helicoptere);