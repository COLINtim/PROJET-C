#include "launcher.h"

void lancementMenu(int * affichage){
	system("clear");
	
	char key;
	
	affichageMenu("menu1.txt");
	while(key != ' '){

		if(key == 'z'){
			(*affichage) = 0;
			affichageMenu("menu1.txt");
		}

		if(key == 's'){
			(*affichage) = 1;
			affichageMenu("menu2.txt");
		}
		
		for(int f=0; f<10000000;f++){}
		printf("\033[68;0H");
		key = key_pressed();
	}
}


void randomSpawnPieton(PietonList** ListeDesPietons)
{
	int i = rand()%3;
	switch(i)
	{
		case 0:
		pietonSpawner(66, 127, NORD, ListeDesPietons); break;
		case 1:
		pietonSpawner(66, 128, NORD, ListeDesPietons); break;
		case 2:
		pietonSpawner(66, 129, NORD, ListeDesPietons); break;
	}
}

void randomSpawnBoat(char ** MatriceDecision, BoatList** ListeDesBoats)
{
	boatSpawner(21+rand()%6,1, DROITE, AleatoireCustomBoat(), MatriceDecision, ListeDesBoats);
}

void randomSpawnLapin(LapinList** ListeDesLapins)
{
	int i = rand()%15;
	int j = rand()%30;
	lapinSpawner(28 + i, 3 + j, ListeDesLapins);
}

void randomSpawnHelicoptere(HelicoptereList** ListeDesHelicopteres)
{
	int i = rand()%4;
	int r = rand()%66;
	int j = rand()%194;
	switch(i)
	{
		case 0: //spawn en haut de la map sur une colonne aleatoirement choisie
		helicoptereSpawner(2, j, 'd', ListeDesHelicopteres); break;

		case 1: //spawn a gauche de la map sur une ligne aleatoirement choisie
		helicoptereSpawner(r, 2, 'r', ListeDesHelicopteres); break;

		case 2: //spawn en bas de map sur une colonne aleatoirement choisie
		helicoptereSpawner(66, j, 'u', ListeDesHelicopteres); break;

		case 3: //spawn a droite de la map sur une ligne aleatoirement choisie
		helicoptereSpawner(r, 194, 'l', ListeDesHelicopteres); break;
	}
}

void randomSpawnVehicule(char** MatriceDecision, VehiculeList** ListeDesVehicules)
{
	int i = rand()%13;
	switch(i)
	{
		case 0:
		vehiculeSpawner(22, 194, OUEST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 1:
		vehiculeSpawner(47, 2, EST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 2:
		vehiculeSpawner(1, 60, SUD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 3:
		vehiculeSpawner(1, 86, SUD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 4:
		vehiculeSpawner(2, 120, SUD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 5:
		vehiculeSpawner(22, 194, OUEST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 6: 
		vehiculeSpawner(45, 194, OUEST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 7:
		vehiculeSpawner(66, 53, NORD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 8:
		vehiculeSpawner(66, 89, NORD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules);break;
		case 9:
		vehiculeSpawner(1, 60, SUD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		vehiculeSpawner(45, 194, OUEST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 10:
		vehiculeSpawner(22, 194, OUEST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		vehiculeSpawner(47, 2, EST, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 11:
		vehiculeSpawner(1, 60, SUD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		case 12:
		vehiculeSpawner(66, 53, NORD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		vehiculeSpawner(2, 120, SUD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
		default:
		vehiculeSpawner(66, 53, NORD, i%2, AleatoireCustomVehicule(), MatriceDecision, ListeDesVehicules); break;
	}

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lancementModeSafe(){

	system("clear");

	affichageMap();

	srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

	char ** MatriceDecision = matrixInit(NBC, NBL);

	char ** MatriceMap = matrixInit(NBC,NBL);

	textToMatrix(MatriceDecision, "dec.txt");

	textToMatrix(MatriceMap, "map1.txt");

	TrafficLightList* Liste=NULL;
	creationDesFeux(&Liste);

	TramwayEater* TramwayEater1 = tramwayEaterInit();
	TramwayEater* TramwayEater2 = tramwayEaterInit();

	BoatList* ListeDesBoats = NULL; 

	VehiculeList* ListeDesVehicules = NULL;

	HelicoptereList* ListeDesHelicopteres = NULL;

	TramwayList* ListeDesTramways = NULL;

	PietonList* ListeDesPietons = NULL;

	//LapinList* ListeDesLapins = NULL;

	tramwaySpawner(67, 114, NORD, &ListeDesTramways);
	tramwaySpawner(56, 0, EST, &ListeDesTramways);	

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

		details();

		if(i==1 || i%3000 == 0)
		{/*
		randomSpawnLapin(&ListeDesLapins);
		randomSpawnLapin(&ListeDesLapins);
		randomSpawnLapin(&ListeDesLapins);*/
		}

		//tramwaySpawner(67, 114, NORD, &ListeDesTramways);
		//tramwaySpawner(56, 0, EST, &ListeDesTramways);

		
		if(i%420 == 400)
		{
			tramwaySpawner(56, 0, EST, &ListeDesTramways);	
		}

		if(i%420 == 372)
		{
			tramwaySpawner(67, 114, NORD, &ListeDesTramways);
		}
		

		if(i%5 == 0)
		{

		randomSpawnVehicule(MatriceDecision, &ListeDesVehicules);

		randomSpawnBoat(MatriceDecision, &ListeDesBoats);
		}

		if(i%3 == 0)
		{
			roulementPietonsPosition(MatriceMap, &MatriceDecision, &ListeDesPietons);
		}

		if(i%60 == 0)
		{
			randomSpawnPieton(&ListeDesPietons);
		}

		roulementBoatsPosition(MatriceMap, MatriceDecision, &ListeDesBoats);

		roulementVehiculesPosition(MatriceMap, &MatriceDecision, &ListeDesVehicules);

		roulementHelicopteresPosition(MatriceMap, MatriceDecision, &ListeDesHelicopteres);

		roulement_feux(&Liste, &MatriceDecision);
		feuxPietons(&MatriceDecision);

		int j = rand()%1000;
		if (j%1000 == 0)
		{
			randomSpawnHelicoptere(&ListeDesHelicopteres);
		}
		
		if(i%2==0){
			
			if(compteurDeTramways(&ListeDesTramways) == 2){
				feuxDeTram(&MatriceDecision, MatriceMap,ListeDesTramways->Tramway , ListeDesTramways->next->Tramway);
			}

			roulementTramwaysPosition(MatriceMap, MatriceDecision, &ListeDesTramways, TramwayEater1, TramwayEater2);
			eaterAffichage(TramwayEater1,1);
			eaterAffichage(TramwayEater2,2);
		}
		if(i%15 == 0)
		{
			//roulementLapinsPosition(MatriceMap, MatriceDecision, &ListeDesLapins);
		}

		for(int j = 0; j<20000000; j++){} 
		printf("\033[67;0H");
		touche = key_pressed();
		printf("\033[67;0H ");
	}

	system("setterm -cursor on");
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lancementModeDanger(){

	system("clear");

	affichageMap();

	srand(time(NULL)); //Permet d'avoir une graine vraiment aleatoire, sinon directionAleatoire renvoit toujours la meme Direction

	char ** MatriceDecision = matrixInit(NBC, NBL);

	char ** MatriceMap = matrixInit(NBC,NBL);

	textToMatrix(MatriceDecision, "dec.txt");

	textToMatrix(MatriceMap, "map1.txt");

	TrafficLightList* Liste=NULL;
	creationDesFeux(&Liste);

	TramwayEater* TramwayEater1 = tramwayEaterInit();
	TramwayEater* TramwayEater2 = tramwayEaterInit();

	BoatList* ListeDesBoats = NULL; 

	VehiculeList* ListeDesVehicules = NULL;

	HelicoptereList* ListeDesHelicopteres = NULL;

	TramwayList* ListeDesTramways = NULL;

	TramwayList* ListeDesAnimes = NULL;

	PietonList* ListeDesPietons = NULL;

	//LapinList* ListeDesLapins = NULL;

	VehiculeList*  ListeAnime = NULL;

	vehiculeSpawner(1, 86, SUD, FAIBLE, 's', MatriceDecision, &ListeAnime);

	tramwaySpawner(67, 114, NORD, &ListeDesTramways);
	tramwaySpawner(56, 0, EST, &ListeDesTramways);

	tramwaySpawner(56, 0, EST, &ListeDesAnimes);
	MatriceDecision[44][86] = '+';
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

		details();
		
		if(i==1 || i%3000 == 0)
		{/*
		randomSpawnLapin(&ListeDesLapins);
		randomSpawnLapin(&ListeDesLapins);
		randomSpawnLapin(&ListeDesLapins);*/
		}

		//tramwaySpawner(67, 114, NORD, &ListeDesTramways);
		//tramwaySpawner(56, 0, EST, &ListeDesTramways);

		
		if(i%420 == 400)
		{
			tramwaySpawner(56, 0, EST, &ListeDesTramways);	
		}

		if(i%420 == 372)
		{
			tramwaySpawner(67, 114, NORD, &ListeDesTramways);
		}
		

		if(i%5 == 0)
		{

		randomSpawnVehicule(MatriceDecision, &ListeDesVehicules);

		randomSpawnBoat(MatriceDecision, &ListeDesBoats);
		}

		if(i%7 == 0)
		{
			roulementPietonsPosition(MatriceMap, &MatriceDecision, &ListeDesPietons);
		}

		if(i%10 == 0)
		{
			randomSpawnPieton(&ListeDesPietons);
		}		
		
		animation1(&ListeAnime, &ListeDesAnimes, &MatriceDecision, MatriceMap);

		roulementBoatsPosition(MatriceMap, MatriceDecision, &ListeDesBoats);

		roulementVehiculesPosition(MatriceMap, &MatriceDecision, &ListeDesVehicules);

		roulementHelicopteresPosition(MatriceMap, MatriceDecision, &ListeDesHelicopteres);

		roulement_feux(&Liste, &MatriceDecision);
		feuxPietons(&MatriceDecision);
		
		if(i%2==0){
			
			if(compteurDeTramways(&ListeDesTramways) == 2){
				feuxDeTram(&MatriceDecision, MatriceMap,ListeDesTramways->Tramway , ListeDesTramways->next->Tramway);
			}

			roulementTramwaysPosition(MatriceMap, MatriceDecision, &ListeDesTramways, TramwayEater1, TramwayEater2);
			eaterAffichage(TramwayEater1,1);
			eaterAffichage(TramwayEater2,2);
		}

		if(i==1)
		{
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			boatSpawner(22, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
		}
		if(i==10)
		{
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			boatSpawner(22, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
		}
		if(i==30)
		{
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			boatSpawner(26, 1, DROITE, AleatoireCustomBoat(), MatriceDecision, &ListeDesBoats);
		}
		if(i==90)
		{	
			vehiculeSpawner(22, 193, OUEST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			vehiculeSpawner(47, 2, EST, FAIBLE, AleatoireCustomVehicule(), MatriceDecision, &ListeDesVehicules);
			i=0;
		}
		if(i%15 == 0)
		{
			//roulementLapinsPosition(MatriceMap, MatriceDecision, &ListeDesLapins);
		}

		//tramwaySpawner(65, 114, j+1, 0, NORD, &ListeDesTramways);	
		for(int j = 0; j<20000000; j++){} 
		printf("\033[67;0H");
		touche = key_pressed();
		printf("\033[67;0H ");
	}

	system("setterm -cursor on");
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void creationDesFeux(TrafficLightList ** Liste){

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


	appendTrafficLightList(&(*Liste), FEU1);
	appendTrafficLightList(&(*Liste), FEU2);
	appendTrafficLightList(&(*Liste), FEU3);
	appendTrafficLightList(&(*Liste), FEU4);
	appendTrafficLightList(&(*Liste), FEU5);
	appendTrafficLightList(&(*Liste), FEU6);
	appendTrafficLightList(&(*Liste), FEU7);
	appendTrafficLightList(&(*Liste), FEU8);
	appendTrafficLightList(&(*Liste), FEU9);
	appendTrafficLightList(&(*Liste), FEU10);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void details(){
	printf("\033[67;1H     ");
	//printf("\033[28;187H  ");
	//printf("\033[29;187H  ");
	//printf("\033[30;187H  ");
	//printf("\033[31;187H  ");
	printf("\033[32;187H  ");
	printf("\033[33;187H  ");
	printf("\033[34;187H  ");
	printf("\033[46;86H  ");
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void animation1(VehiculeList ** ListeDesVehicules, TramwayList ** ListeTramways, char *** MatriceDecision, char ** MatriceMap){
	//creer la voiture et le tram de sorte qu'ils se rencontre au point de coordonées
	//voiture et tram n'appartenant pas au listes, ils ont leur porpres directives (ils avances tous les deux de maniere rectiligne)
	//la voiture arrive un peu avant, le personnage sort , il est en panne !
	//le tram arrive et ne s'arrete pas.
	//collision et flammes.
	
	VehiculeList * tmp;
	tmp = * ListeDesVehicules;

	if(tmp->Vehicule->posX < 56){

		Position* NextPosition = positionFuture(tmp->Vehicule);

		if((*MatriceDecision)[NextPosition->posX][NextPosition->posY] == 'f')
		{
			affichageVehicule(tmp->Vehicule);
		}
		else if((*MatriceDecision)[NextPosition->posX][NextPosition->posY] =='c')
		{
			affichageVehicule(tmp->Vehicule);
		}	
		else
		{
			if(tmp->Vehicule->CaseDecision == 'F')
			{
				if((*MatriceDecision)[NextPosition->posX][NextPosition->posY] == 'A')
				{
					affichagePartielVehicule(MatriceMap, tmp->Vehicule);
					tmp->Vehicule->posX++;
					tmp->Vehicule->CaseDecision = (*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY];
					(*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY] = 'c';
					affichageVehicule(tmp->Vehicule);
					
				}
				else
				{	
						tmp->Vehicule->posX++;
				}
			}else{

				(*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY] = tmp->Vehicule->CaseDecision; //La ou la voiture etait devient de la route (place libre)
				affichagePartielVehicule(MatriceMap, tmp->Vehicule);
				tmp->Vehicule->posX++; //On actualise la position de la voiture dans la structure 
				tmp->Vehicule->CaseDecision = (*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY]; // MAJ de la case decision

				if(tmp->Vehicule->CaseDecision == 'E')
				{
					affichagePartielVehicule(MatriceMap, tmp->Vehicule);
					tmp = vehiculeEater(ListeDesVehicules, tmp->Vehicule);	

				}
				else if(tmp->Vehicule->CaseDecision == '+')
				{
					(*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY] = tmp->Vehicule->CaseDecision;
					affichagePartielVehicule(MatriceMap, tmp->Vehicule);
					tmp->Vehicule->posX++;
					tmp->Vehicule->CaseDecision = 'F';
					

				}
				else
				{	
					affichagePartielVehicule(MatriceMap, tmp->Vehicule);
					(*MatriceDecision)[tmp->Vehicule->posX][tmp->Vehicule->posY] = 'c'; //On actualise la MatricePositionVehicules pour signaler qu'une voiture se trouve maintenant a cette position
					affichageVehicule(tmp->Vehicule);	
					
				}
			}
		}
		
	}else{

		
		switch(tmp->Vehicule->posX){

			case 57: printf("\033[%d;%dH🚶", 56, tmp->Vehicule->posY+2);break;
			case 60: printf("\033[%d;%dH──", 56, tmp->Vehicule->posY+2);printf("\033[%d;%dH🚶", 56+1, tmp->Vehicule->posY+1);break;
			case 61: printf("\033[%d;%dH─", 56+1, tmp->Vehicule->posY+1);printf("\033[%d;%dH🚶", 56+1, tmp->Vehicule->posY);break;
			case 63: printf("\033[%d;%dH?", 56+1, tmp->Vehicule->posY+2);break;

			case 110: printf("\033[%d;%dH!", 56+1, tmp->Vehicule->posY+2);break;
		}
		
		if(120 <= tmp->Vehicule->posX){

			if(tmp->Vehicule->posY >= 100){
				couleur("31");
				printf("\033[55;%dH🔥🔥",tmp->Vehicule->posY-1);
				printf("\033[56;%dH🔥",tmp->Vehicule->posY+1);
				printf("\033[57;%dH🔥🔥",tmp->Vehicule->posY-1);
				couleur("0");
			}

			if(tmp->Vehicule->posY < 100){
				printf("\033[%d;%dH─∎∎∎∎🚘", 56, tmp->Vehicule->posY-5);
				if(tmp->Vehicule->posY%2 == 0){
					couleur("31");
					printf("\033[%d;%dH🔥", 57, tmp->Vehicule->posY-1);
					printf("\033[%d;%dH🔥", 55, tmp->Vehicule->posY-1);
					couleur("0");
				}
				tmp->Vehicule->posY++;
			}

		}
		tmp->Vehicule->posX++;
	}
}

