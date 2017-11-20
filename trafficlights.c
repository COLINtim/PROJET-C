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
void modificationDeMatrice(TrafficLight * T, char *** MatriceDecision, char caractere){
	int i=0;
	if(T->posY == 86){(*MatriceDecision)[T->posX-1][T->posY]=caractere;
	}else{
		switch(T->posX){
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
void feuxDeTram(char ***MatriceDecision, char **MatriceMap, Tramway * T1, Tramway * T2){
	//test
	if(T1->compteur2 >T2->compteur2){

		if(T->posX == 56 && T->posY=83){T1->compteur2=0;} 
		if(T->posX == 58 && T->posY=96){T2->compteur2=0;}
		if(T1->compteur2 >= 0){

			switch(T1->compteur2){

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("43"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("43"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("43"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("43"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("43"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
			}
			if (T1->compteur2 != -1){T1->compteur2++;}
		}
		if(T2->compteur2 >= 0){

			switch(T2->compteur2){

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("43"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("43"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("43"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("43"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("43"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
			}
			if (T2->compteur2 != -1){T2->compteur2++;}
		}

	}	
		//si il y a le tram: on rentre dans la boucle de feux (modification du dec.txt et affichage du feux en rouge)

		//boucle feux: on boucle sur 8 frames (|  TTTT  |) 2 premieres on abaisse la barriere et les 2 dernieres on releve.

		//apres ça on réaffiche en vert tout en modifiant le dec.txt.


	
	else if(T1->compteur2 <=T2->compteur2){

		if(T->posX== 57 && T->posY=81){T1->compteur2=0;} 
		if(T->posX == 59 && T->posY=97){T2->compteur2=0;}
		if(T2->compteur2 >= 0){

			switch(T2->compteur2){

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("33"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("33"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("33"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("33"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("33"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
				case 15: printf("\033[56;91H ");printf("\033[60;87H ");break;
				case 16: printf("\033[56;90H ");printf("\033[60;90H ");break;
				case 17: printf("\033[56;89H ");printf("\033[60;89H ");break;
				case 18: printf("\033[56;88H ");printf("\033[60;88H ");break;
				case 19: printf("\033[56;87H ");printf("\033[60;87H ");break;
				case 20: T2->compteur2=-1;
			}
			if (T2->compteur2 != -1){T2->compteur2++;}
		}
		if(T1->compteur2 >= 0){

			switch(T1->compteur2){

				case 0: couleur("41"); printf("\033[55;86H ");printf("\033[60;92H ");couleur("0");
						(*MatriceDecision)[55][87]='f';(*MatriceDecision)[60][91]='f';
						break;
				case 1: couleur("43"); printf("\033[56;87H─");printf("\033[60;87H ");couleur("0");break;
				case 2: couleur("43"); printf("\033[56;88H─");printf("\033[60;88H ");couleur("0");break;
				case 3: couleur("43"); printf("\033[56;89H─");printf("\033[60;89H ");couleur("0");break;
				case 4: couleur("43"); printf("\033[56;90H─");printf("\033[60;90H ");couleur("0");break;
				case 5: couleur("43"); printf("\033[56;91H─");printf("\033[60;91H ");couleur("0");break;
				case 15: printf("\033[56;91H ");printf("\033[60;87H ");break;
				case 16: printf("\033[56;90H ");printf("\033[60;90H ");break;
				case 17: printf("\033[56;89H ");printf("\033[60;89H ");break;
				case 18: printf("\033[56;88H ");printf("\033[60;88H ");break;
				case 19: printf("\033[56;87H ");printf("\033[60;87H ");break;
				case 20: T1->compteur2=-1;
			}
			if (T1->compteur2 != -1){T1->compteur2++;}
		}
	}
	if (T1->compteur2 == -1 && T2->compteur2 == -1){
		couleur("42");
		printf("\033[55;86H ");
		printf("\033[60;92H ");
		couleur("0");
		(*MatriceDecision)[55][87]='o';
		(*MatriceDecision)[60][91]='o';
	}
}