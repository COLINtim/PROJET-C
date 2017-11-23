#include "librairies.h"
#include "boats.h"
#include "trafficlights.h"
#include "vehicules.h"
#include "decision.h"
#include "affichage.h"
//#include "tramways.h"

int main()
{	
	system("clear");
	
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
	if(affichage == 1){
		printf("\033[37;110H‡\n");
		couleur("43");printf("\033[37;49H ");printf("\033[37;132H ");couleur("0");
		for(int m=0;m<58;m++){
			printf("\033[37;%dH",50+m);couleur("42");printf(" ");couleur("0");printf("🚘\n");
			for(int j = 0; j<10000000; j++){} 
		}
		
		
		for (int m=0; m<20; m+=2){
			printf("\033[37;%dH",111+m);couleur("31");printf("🔥\n");couleur("0");
			for(int j = 0; j<20000000; j++){} 
		}
		
	}else{
		couleur("43");printf("\033[21;57H ");printf("\033[21;121H ");couleur("0");
		for(int m=0;m<61;m++){
			printf("\033[21;%dH",58+m);couleur("42");printf(" ");couleur("0");printf("🚘\n");
			for(int j = 0; j<10000000; j++){} 
		}
		
	}















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
TrafficLight* FEU1 = createTrafficLight(4, 5, 200);
TrafficLight* FEU2 = createTrafficLight(3, 6, 24);
appendTrafficLightList(&Liste, FEU1);
appendTrafficLightList(&Liste, FEU2);
//visualiserTrafficLightList(Liste);	
for(int i=0;i<300;i++){
	roulement_feux(&Liste);
	for(int j = 0; j<20000000; j++){} 
}
//visualiserTrafficLightList(Liste);

//OK
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



system("setterm -cursor off");

system("clear");

affichageMap();

srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

char ** MatriceDecision = matrixInit(NBC, NBL);

char ** MatriceMap = matrixInit(NBC,NBL);

textToMatrix(MatriceMap, "map1.txt");

textToMatrix(MatriceDecision, "dec.txt");

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

//showMatrix(MatriceDecision);
//printf("%c", MatriceDecision[20][60]);


BoatList* ListeDesBoats = NULL; 

VehiculeList* ListeDesVehicules = NULL;

//TramwayList* ListeDesTramways = NULL;

//boatSpawner(21, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
boatSpawner(23, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
boatSpawner(26, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);

vehiculeSpawner(26, 150, SUD, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
vehiculeSpawner(1, 86, SUD, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);

//tramwaySpawner(56, 0, 1, 0, EST, &ListeDesTramways);

int i;
char touche;
while(touche != 'q')
{	
	i++;
	
	roulement_feux(&Liste, &MatriceDecision);
	roulementBoatsPosition(MatriceMap, &MatriceDecision, &ListeDesBoats);
	roulementVehiculesPosition(MatriceMap, &MatriceDecision, &ListeDesVehicules);

	//roulementTramwaysPosition(MatriceMap, MatriceDecision, &ListeDesTramways);

	if(i==30){
		boatSpawner(26, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
	}
	if(i==50){
		boatSpawner(23, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
	}
	if(i==60){
		vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
	}
	if(i==80){
		vehiculeSpawner(1, 86, SUD, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
	}
	if(i>=100){
		vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
		i=0;
	}

	for(int j = 0; j<20000000; j++){} 
	printf("\033[67;0H");
	touche = key_pressed();
	printf("\033[67;0H ");
}

printf("\033[67;0H");

system("setterm -cursor on");
	return 0;
}

