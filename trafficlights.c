#include "librairies.h"
#include "trafficlights.h"

// FONCTIONS RELATIVES AUX FEUX

TrafficLight* createTrafficLight(int posX, int posY, Color color)
{
	TrafficLight* Traffic=malloc(sizeof(TrafficLight));
	Traffic->posX = posX;
	Traffic->posY = posY;
	Traffic->Current_Color = color;
	Traffic->TimeForSwitch = color;
	Traffic->Compteur = 0;
	return Traffic;
}


void appendTrafficLightList(TrafficLightList **List, TrafficLight *TrafficLight)
{
	TrafficLightList *element;
	element = malloc(sizeof(*element));
	element->TrafficLight=TrafficLight;
	element->next = *List;
	*List = element;
}	

void visualiserTrafficLightList(TrafficLightList *List)
{
	TrafficLightList *tmp;
	tmp = List;
	while (tmp != NULL)	{
			printf("Position en X:%d\n", tmp->TrafficLight->posX);
			printf("Position en Y:%d\n", tmp->TrafficLight->posY);
			printf("Couleur Courrante: %d \n",tmp->TrafficLight->Current_Color);
			printf("Temps requis pour changer de couleur: %d \n",tmp->TrafficLight->TimeForSwitch);
			tmp = tmp->next;
						}
}

void showTrafficLight(TrafficLight Feu)
{
	printf("Position en X: %d \n", Feu.posX);
	printf("Position en Y: %d \n", Feu.posY);
	printf("Couleur Courrante: %d \n",Feu.Current_Color);
	printf("Temps requis pour changer de couleur: %d \n",Feu.TimeForSwitch);
}


/*
clock_t startChrono(double* montre)
{
	clock_t temps;
	double Chrono = temps / CLOCKS_PER_SEC;
	*montre = Chrono;
}

double visualiserChrono(double* montre)
{
	return *montre;
}	
*/	
	

void roulementFeux(TrafficLightList *List)
{
	TrafficLightList *tmp;
	tmp = List;
	while(tmp != NULL) 
	{
			if(tmp->TrafficLight->Compteur > tmp->TrafficLight->TimeForSwitch)
			{
				tmp->TrafficLight->Current_Color+=1%4;
				tmp->TrafficLight->TimeForSwitch+=1%4;
				tmp->TrafficLight->Compteur = 0;
				tmp = tmp->next;
			}
			else
			{
				tmp->TrafficLight->Compteur = tmp->TrafficLight->Compteur + 1;
			}
	}
}

void affichageFeu(TrafficLight* T){
	switch(T->Current_Color){
		case 0: couleur("42");
			printf("\033[%d;%dH ",T->posY,T->posX);
			couleur("0");
			break;
		case 1: couleur("43");
			printf("\033[%d;%dH ",T->posY,T->posX);
			couleur("0");
			break;
		case 2: couleur("41");
			printf("\033[%d;%dH ",T->posY,T->posX);
			couleur("0");
			break;
		case 3: couleur("41");
			printf("\033[%d;%dH ",T->posY,T->posX);
			couleur("0");
			break;
	}
}

/* A TESTER, pas sûr que ça fonctionne mais l'idée de cette fonction simplifierait grandement le fonctionnement des feux
	
void GestionDesFeux(TrafficLightList *List)
{
	clock_t temps = 0;
	
	if((double)temps / CLOCKS_PER_SEC >= (List->TrafficLight->TimeForSwitch)) {
			Roulement_feux(List);
			GestionDesFeux(List);	
	}
}

*/
