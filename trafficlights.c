#include "librairies.h"
#include "trafficlights.h"

// FONCTIONS RELATIVES AUX FEUX

TrafficLight* createTrafficLight(int posX, int posY, int color)
{
	TrafficLight* Traffic=malloc(sizeof(TrafficLight));
	Traffic->posX = posX;
	Traffic->posY = posY;
	Traffic->color = color;
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
/*
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

*/
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
	

void roulement_feux(TrafficLightList ** List, char *** MatriceDecision)
{
	TrafficLightList *tmp;
	tmp = *List;
	while(tmp != NULL) {

			if(tmp->TrafficLight->Compteur >= tmp->TrafficLight->color){

				switch(tmp->TrafficLight->color) {

					case 100: tmp->TrafficLight->color = 12;break;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'f');break;
				
					case 12: tmp->TrafficLight->color = 64;break;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'f');break;
				
					case 64: tmp->TrafficLight->color = 20;break;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'o');break;
				
					case 20: tmp->TrafficLight->color = 100;break;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'o');break;
				}

				affichageFeu(tmp->TrafficLight);
				tmp->TrafficLight->Compteur = 0;

				tmp = tmp->next;

			}else{

				affichageFeu(tmp->TrafficLight);
				tmp->TrafficLight->Compteur++;

				tmp = tmp->next;
			}
	}
}
//////////////////////////////////////////////////////////////////////////
void modificationDeMatrice(TrafficLight * T, char *** MatriceDecision, char caractere){
	int i=0;
	switch(T->posX){
		case 20: (*MatriceDecision)[T->posX][T->posY+2]=caractere;break;
		case 43: (*MatriceDecision)[T->posX][T->posY+2]=caractere;break;
		case 26: (*MatriceDecision)[T->posX-1][T->posY]=caractere;break;
		case 49: (*MatriceDecision)[T->posX-1][T->posY]=caractere;break;
		case 22: (*MatriceDecision)[T->posX+1][T->posY]=caractere;break;
		case 44: (*MatriceDecision)[T->posX+1][T->posY]=caractere;break;
		case 27: (*MatriceDecision)[T->posX][T->posY-2]=caractere;break;
		case 50: (*MatriceDecision)[T->posX][T->posY-2]=caractere;break;
	}
}
//////////////////////////////////////////////////////////////////////////
void affichageFeu(TrafficLight* trafficLight){
	
	switch(trafficLight->color){
		case 64: couleur("42");
			printf("\033[%d;%dH ",trafficLight->posX,trafficLight->posY);
			couleur("0");
			break;
		case 20: couleur("43");
			printf("\033[%d;%dH ",trafficLight->posX,trafficLight->posY);
			couleur("0");
			break;
		case 100: couleur("41");
			printf("\033[%d;%dH ",trafficLight->posX,trafficLight->posY);
			couleur("0");
			break;
		case 12: couleur("41");
			printf("\033[%d;%dH ",trafficLight->posX,trafficLight->posY);
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
