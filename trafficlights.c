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
	
void roulement_feux(TrafficLightList ** List, char *** MatriceDecision)
{
	TrafficLightList *tmp;
	tmp = *List;
	while(tmp != NULL) {

			if(tmp->TrafficLight->Compteur >= tmp->TrafficLight->color){

				switch(tmp->TrafficLight->color) {

					case 100: tmp->TrafficLight->color = 12;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'f');break;
				
					case 12: tmp->TrafficLight->color = 64;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'o');break;
				
					case 64: tmp->TrafficLight->color = 20;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'o');break;
				
					case 20: tmp->TrafficLight->color = 100;modificationDeMatrice(tmp->TrafficLight,&(*MatriceDecision),'f');break;
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
void affichageFeu(TrafficLight* trafficLight){
	
	switch(trafficLight->color){
		case 64: couleur("42");
			printf("\033[%d;%dH ",trafficLight->posX-1,trafficLight->posY-1);
			couleur("0");
			break;
		case 20: couleur("43");
			printf("\033[%d;%dH ",trafficLight->posX-1,trafficLight->posY-1);
			couleur("0");
			break;
		case 100: couleur("41");
			printf("\033[%d;%dH ",trafficLight->posX-1,trafficLight->posY-1);
			couleur("0");
			break;
		case 12: couleur("41");
			printf("\033[%d;%dH ",trafficLight->posX-1,trafficLight->posY-1);
			couleur("0");
			break;
	}
}

void modificationDeMatrice(TrafficLight * T, char *** MatriceDecision, char caractere)
{
	if(T->posY == 86)
	{
		(*MatriceDecision)[T->posX-1][T->posY]=caractere;
	}
	else
	{
		switch(T->posX)
		{
			case 21: (*MatriceDecision)[T->posX-1][T->posY+1]=caractere;break;
			case 44: (*MatriceDecision)[T->posX-1][T->posY+1]=caractere;break;
			case 27: (*MatriceDecision)[T->posX-1][T->posY-3]=caractere;break;
			case 50: (*MatriceDecision)[T->posX-1][T->posY-3]=caractere;break;
			case 22: (*MatriceDecision)[T->posX][T->posY-1]=caractere;break;
			case 45: (*MatriceDecision)[T->posX][T->posY-1]=caractere;break;
			case 26: (*MatriceDecision)[T->posX-2][T->posY-1]=caractere;break;
			case 49: (*MatriceDecision)[T->posX-2][T->posY-1]=caractere;break;
		}
	}
}

void feuxPietons(char *** MatriceDecision){
	if((*MatriceDecision)[20][60] == 'o'){
		(*MatriceDecision)[20][66] = '+';
	}else{
		(*MatriceDecision)[20][66] = 'o';
	}
	if((*MatriceDecision)[20][87] == 'o'){
		(*MatriceDecision)[20][89] = '+';
	}else{
		(*MatriceDecision)[20][89] = 'o';
	}
	if((*MatriceDecision)[22][93] == 'o'){
		(*MatriceDecision)[25][93] = '+';
	}else{
		(*MatriceDecision)[25][93] = 'o';
	}
	
}