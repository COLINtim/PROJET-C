#include "librairies.h"
#include "boats.h"
#include "trafficlights.h"
#include "vehicules.h"
#include "decision.h"
#include "affichage.h"
#include "pietons.h"
#include "tramways.h"
#include "helicopteres.h"
#include "lapins.h"

int main()
{
	system("clear");
	system("setterm -cursor off");
	
	char key;
	int affichage = 0;
	affichageMenu("menu1.txt");
	while(key != ' '){

		if(key == 'z'){
			affichage = 0;
			affichageMenu("menu1.txt");
		}

		if(key == 's'){
			affichage = 1;
			affichageMenu("menu2.txt");
		}
		
		for(int f=0; f<10000000;f++){}
		printf("\033[68;0H");
		key = key_pressed();
	}

	system("clear");

	affichageMap();

	srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

	char ** MatriceDecision = matrixInit(NBC, NBL);

	char ** MatriceMap = matrixInit(NBC,NBL);

	textToMatrix(MatriceDecision, "dec.txt");

	textToMatrix(MatriceMap, "map1.txt");

	TrafficLightList* Liste=NULL;

	TrafficLight* FEU1 = createTrafficLight(21, 59, 100);//rouge inter
	TrafficLight* FEU2 = createTrafficLight(21, 86, 100);
	TrafficLight* FEU3 = createTrafficLight(21, 119,100);
	TrafficLight* FEU4 = createTrafficLight(27, 92, 100);
	TrafficLight* FEU5 = createTrafficLight(22, 94, 12);//rouge
	TrafficLight* FEU6 = createTrafficLight(26, 84, 12);
	TrafficLight* FEU7 = createTrafficLight(44, 48, 12);
	TrafficLight* FEU8 = createTrafficLight(50, 56, 12);
	TrafficLight* FEU9 = createTrafficLight(45, 58, 100);
	TrafficLight* FEU10 = createTrafficLight(49, 46, 100);


	appendTrafficLightList(&Liste, FEU1);
	appendTrafficLightList(&Liste, FEU2);
	appendTrafficLightList(&Liste, FEU3);
	appendTrafficLightList(&Liste, FEU4);
	appendTrafficLightList(&Liste, FEU5);
	appendTrafficLightList(&Liste, FEU6);
	appendTrafficLightList(&Liste, FEU7);
	appendTrafficLightList(&Liste, FEU8);
	appendTrafficLightList(&Liste, FEU9);
	appendTrafficLightList(&Liste, FEU10);

	BoatList* ListeDesBoats = NULL; 

	VehiculeList* ListeDesVehicules = NULL;

	HelicoptereList* ListeDesHelicopteres = NULL;

	TramwayList* ListeDesTramways = NULL;

	//PietonList* ListeDesPietons = NULL;

	LapinList* ListeDesLapins = NULL;

	boatSpawner(22, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);

	boatSpawner(26, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);

	vehiculeSpawner(22, 194, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);

	vehiculeSpawner(24, 130, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);

	helicoptereSpawner(3, 3, 'c', &ListeDesHelicopteres);

	//pietonSpawner(3, 96, SUD, &ListeDesPietons);

	lapinSpawner(37, 21, &ListeDesLapins);

	//tramwaySpawner(65, 114, 1, 0, NORD, &ListeDesTramways);
	tramwaySpawner(56, 0, 0, EST, &ListeDesTramways);

	int i = 0;
	char touche;
	while(touche != 'q'){

		if(touche == ' '){

			touche = 'a';

			while(touche != ' '){

				printf("\033[67;0H");
				touche = key_pressed();
				printf("\033[67;0H ");
			}
		}
		i++;
		//roulementPietonsPosition(MatriceMap, MatriceDecision, &ListeDesPietons);
		roulementBoatsPosition(MatriceMap, MatriceDecision, &ListeDesBoats);
		roulementVehiculesPosition(MatriceMap, &MatriceDecision, &ListeDesVehicules);
		roulementHelicopteresPosition(MatriceMap, MatriceDecision, &ListeDesHelicopteres);
		roulement_feux(&Liste, &MatriceDecision);
		//roulementTramwaysPosition(MatriceMap, MatriceDecision, &ListeDesTramways);
		//boatSpawner(21+rand()%6, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats); //A ce rythme là c'est la bataille navale lol

		if(i==1)
		{
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
		}
		if(i==10)
		{
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
		}
		if(i==30)
		{
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
		}
		if(i==90)
		{	
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			i=0;
		}
		if(i%15 == 0)
		{
			roulementLapinsPosition(MatriceMap, MatriceDecision, &ListeDesLapins);
		}

		//tramwaySpawner(65, 114, j+1, 0, NORD, &ListeDesTramways);	
		for(int j = 0; j<20000000; j++){} 
		printf("\033[67;0H");
		touche = key_pressed();
		printf("\033[67;0H ");
	}

	system("setterm -sursor off");
	return 0;
}

//57 119