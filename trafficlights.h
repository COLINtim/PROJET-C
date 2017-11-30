#include "librairies.h"


typedef struct TrafficLight	
{
	int color;
	int posX;
	int posY;
	int Compteur;
} TrafficLight;

typedef struct TrafficLightList // Liste chainee des feux pour le roulement des feux sur la carte
{
	TrafficLight* TrafficLight;
	struct TrafficLightList *next;
} TrafficLightList;

TrafficLight* createTrafficLight(int posX, int posY, int color); //Permet d'instancier un feu

void appendTrafficLightList(TrafficLightList **list, TrafficLight*);	//Permet d'ajouter un feu a la liste chainee

void roulement_feux(TrafficLightList ** List, char *** MatriceDecision);//Fonction prenant en argument une liste de feu et incrémentant leur état de 1 unité. (vert => orange, etc ... modulo 4)

void affichageFeu(TrafficLight* trafficLight); //Fonction d'affichage de trafficlights

void modificationDeMatrice(TrafficLight * T, char *** MatriceDecision, char caractere);

void feuxPietons(char *** MatriceDecision);