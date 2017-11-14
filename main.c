#include "librairies.h"
#include "boats.h"
#include "trafficlights.h"
#include "vehicules.h"
#include "decision.h"
#include "affichage.h"

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

system("setterm -cursor off");

system("clear");

affichageMap();

srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

char ** MatriceDecision = matrixInit(NBC, NBL);

char ** MatriceMap = matrixInit(NBC,NBL);

textToMatrix(MatriceMap, "map1.txt");

textToMatrix(MatriceDecision, "dec.txt");

BoatList* ListeDesBoats = NULL; 

VehiculeList* ListeDesVehicules = NULL;

boatSpawner(21, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
boatSpawner(23, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
boatSpawner(26, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);

vehiculeSpawner(47, 1, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
vehiculeSpawner(1, 86, SUD, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
vehiculeSpawner(22, 194, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);

int i=0;
for(i; i<300;i++)
{

	roulementBoatsPosition(MatriceMap, MatriceDecision, &ListeDesBoats);
	roulementVehiculesPosition(MatriceMap, MatriceDecision, &ListeDesVehicules);
	for(int j = 0; j<20000000; j++){} 
	printf("\033[67;0H");
	
}
printf("\033[67;0H");

	return 0;
}

