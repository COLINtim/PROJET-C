#include "librairies.h"
#include "affichage.h"


#define NBC 194 
#define NBL 65
//system("setterm -cursor off");
int main()
{	
	system("clear");
	srand(time(NULL));
	int rd=rand()%6;
	affichageMap();
	Vehicule * vehicule1 = VehiculeSpawner(49,66,NORD);
	vehicule1=initVehicule(rd,vehicule1);
	int chrono=0;
	
	//while(1==1){	
		affichageMap();
		affichageVoiture(*vehicule1);
		vehicule1->posY=vehicule1->posY-1;
		chrono=0;
		while(chrono<100000000){
			chrono++;	
		}

	//}

	/* TESTS RELATIFS à L'AFFICHAGE
	system("clear");
	affichageMap();
	clock_t temps;
	Chrono= temps/CLOCKS_PER_SEC;
	TrafficLightList TrafficLightList='NULL'; 
	void InitialisationTrafficLights();
	*/

// TESTS RELATIFS AUX FEUX
/*
TrafficLightList* Liste=NULL;
TrafficLight* FEU1 = CreateTrafficLight(4, 5, VERT);
TrafficLight* FEU2 = CreateTrafficLight(3, 6, ROUGE);
AppendList(&Liste, FEU1);
AppendList(&Liste, FEU2);
VisualiserTrafficLightList(Liste);	
Roulement_feux(Liste);
VisualiserTrafficLightList(Liste);

OK

*/


// TESTS RELATIFS AUX VEHICULES 

/*
VehiculeList* Liste = NULL;
Vehicule* Vehicule1 = VehiculeSpawner(4,3,NORD);
Vehicule* Vehicule2 = VehiculeSpawner(6,7,SUD);

AppendVehiculeList(&Liste,Vehicule1);
AppendVehiculeList(&Liste,Vehicule2);

printf("Visualisation de la liste remplie:\n");
VisualiserVehiculeList(Liste);
printf("On retire now Vehicule 1 puis on affiche la liste\n");
VehiculeEater(&Liste, Vehicule1);
VisualiserVehiculeList(Liste);
printf("fin du programme \n");

OK
*/

//TESTS RELATIFS AUX BATEAUUUUUUUX


/*
BoatList* Liste = NULL;
Boat* Voilier = BoatSpawner(4,5,SUD);
Boat* Catamaran = BoatSpawner(8,9,EST);
AppendBoatList(&Liste,Catamaran);
AppendBoatList(&Liste,Voilier);
printf("On affiche la Liste qui a 2 elements \n");
VisualiserBoatList(Liste);
BoatEater(&Liste, Catamaran);
printf("On affiche la liste qui n'a plus qu'un element\n");
VisualiserBoatList(Liste);

OK

*/


//TESTS RELATIFS A LA DECISION

/*
char ** MatriceDecision = MatrixInit(NBC, NBL);

TextToMatrix(NBC, NBL, MatriceDecision, "dec.txt");

ShowMatrix(NBC, NBL, MatriceDecision);

RoulementFeuxDecision(NBC, NBL,MatriceDecision);

printf("\n\n\n\n");

ShowMatrix(NBC, NBL, MatriceDecision);

OK

*/


//TESTS RELATIFS AUX VEHICULES
/*

char ** MatricePositionVehicules = MatrixInit(NBC, NBL);

TextToMatrix(NBC, NBL, MatricePositionVehicules, "MatricePositionVehicules.txt");

ShowMatrix(NBC, NBL, MatricePositionVehicules);

PAS ENCORE FAIT/FINI

*/


	return 0;
}

