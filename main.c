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
	/* TESTS RELATIFS à L'AFFICHAGE
	system("clear");	
	affichage();
	clock_t temps;
	Chrono= temps/CLOCKS_PER_SEC;
	TrafficLightList TrafficLightList='NULL'; 
	void InitialisationTrafficLights();
	*/

// TESTS RELATIFS AUX FEUX
/*
TrafficLightList* Liste=NULL;
TrafficLight* FEU1 = createTrafficLight(4, 5, VERT);
TrafficLight* FEU2 = createTrafficLight(3, 6, ROUGE);
appendTrafficLightList(&Liste, FEU1);
appendTrafficLightList(&Liste, FEU2);
visualiserTrafficLightList(Liste);	
roulement_feux(Liste);
visualiserTrafficLightList(Liste);

OK

*/


// TESTS RELATIFS AUX VEHICULES 
/*

VehiculeList* Liste = NULL;
Vehicule* Vehicule1 = oldVehiculeSpawner(4,3,NORD);
Vehicule* Vehicule2 = oldVehiculeSpawner(6,7,SUD);

appendVehiculeList(&Liste,Vehicule1);
appendVehiculeList(&Liste,Vehicule2);

printf("Visualisation de la liste remplie:\n");
visualiserVehiculeList(Liste);
printf("On retire now Vehicule 1 puis on affiche la liste\n");
vehiculeEater(&Liste, Vehicule1);
visualiserVehiculeList(Liste);
printf("fin du programme \n");

OK

*/


//TESTS RELATIFS AUX BATEAUUUUUUUX


/*
BoatList* Liste = NULL;
Boat* Voilier = boatSpawner(4,5,SUD);
Boat* Catamaran = oatSpawner(8,9,EST);
appendBoatList(&Liste,Catamaran);
appendBoatList(&Liste,Voilier);
printf("On affiche la Liste qui a 2 elements \n");
visualiserBoatList(Liste);
boatEater(&Liste, Catamaran);
printf("On affiche la liste qui n'a plus qu'un element\n");
visualiserBoatList(Liste);

OK

*/


//TESTS RELATIFS A LA DECISION

/*

char ** MatriceDecision = MatrixInit();

textToMatrix(MatriceDecision, "dec.txt");

showMatrix(MatriceDecision);

roulementFeuxDecision(MatriceDecision);

printf("\n\n\n\n");

showMatrix(MatriceDecision);

OK

*/




//TESTS RELATIFS AUX VEHICULES ET A LEURS MOUVEMENTS


/*
srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

char ** MatriceDecision = matrixInit(NBC, NBL);

textToMatrix(MatriceDecision, "dec.txt");

showMatrix(MatriceDecision);

VehiculeList* ListeDesVehicules = NULL;

//(20,193) est une Position de Spawner de Vehicule

vehiculeSpawner(28, 152, EST, FAIBLE, MatriceDecision, &ListeDesVehicules);

int k=0;

for(k=0; k<20; k++)
{
roulementVehiculesPosition(MatriceDecision, &ListeDesVehicules);
}

showMatrix(MatriceDecision);

*/

//OK FONCTIONNE ! Meme les virages (:


//TESTS RELATIFS AUX BATEAUX ET A LEURS MOUVEMENTS


/*
srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

char ** MatriceDecision = matrixInit(NBC, NBL);

textToMatrix(MatriceDecision, "dec.txt");

showMatrix(MatriceDecision);

BoatList* ListeDesBoats = NULL;

boatSpawner(22, 1, DROITE, MatriceDecision, &ListeDesBoats);

int i=0;
for(i=0; i<212; i++){
roulementBoatsPosition(MatriceDecision, &ListeDesBoats);
}
showMatrix(MatriceDecision);

//ça marche ! les D et A representent "Disparaitre" et "Apparaitre", Les Eaters en fin de map font segfault, reste à trouver pourquoi

*/

//affichageMap();

printf("\e[?25l");
/*
system("cat Accueil.txt");

int k;
int z;
for(k = 0; k< 100 ; k++)
	{
		for(z = 0; z<6000000; z++)
		{
			if (z%60000 == 0)
			{
					printf("\r Loading ... %d/100",k);
			}
		}
	}
*/
/*
system("xdotool key CTRL+underscore");
system("xdotool key CTRL+underscore");
system("xdotool key CTRL+underscore");
*/


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

PietonList* ListeDesPietons = NULL;

LapinList* ListeDesLapins = NULL;

boatSpawner(22, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);

boatSpawner(26, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);

vehiculeSpawner(22, 194, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);

vehiculeSpawner(24, 130, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);

helicoptereSpawner(3, 3, 'c', &ListeDesHelicopteres);

pietonSpawner(3, 96, SUD, &ListeDesPietons);

lapinSpawner(37, 21, &ListeDesLapins);

//tramwaySpawner(65, 114, 1, 0, NORD, &ListeDesTramways);
tramwaySpawner(56, 0, 0, EST, &ListeDesTramways);

int i = 0;

for(i=0; i<100; i++)
{
roulementPietonsPosition(MatriceMap, MatriceDecision, &ListeDesPietons);
roulementBoatsPosition(MatriceMap, MatriceDecision, &ListeDesBoats);
roulementVehiculesPosition(MatriceMap, &MatriceDecision, &ListeDesVehicules);
roulementHelicopteresPosition(MatriceMap, MatriceDecision, &ListeDesHelicopteres);
roulement_feux(&Liste, &MatriceDecision);
//roulementTramwaysPosition(MatriceMap, MatriceDecision, &ListeDesTramways);
//boatSpawner(21+rand()%6, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats); //A ce rythme là c'est la bataille navale lol

if(i==3)
{
	vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
}
if(i==10)
{
	vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
}
if(i==30)
{
	vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
}
if(i==90)
{
	vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
	i=0;
}
if(i%15 == 0)
{
	roulementLapinsPosition(MatriceMap, MatriceDecision, &ListeDesLapins);
}

	//tramwaySpawner(65, 114, j+1, 0, NORD, &ListeDesTramways);	
for(int j = 0; j<20000000; j++){} 
}
	return 0;
}

//57 119