#include "librairies.h"
#include "affichage.h"
#include "mouvements.h"

int main()
{
	/*system("clear");
	affichage();
	clock_t temps;
	Chrono= temps/CLOCKS_PER_SEC;
	TrafficLightList TrafficLightList='NULL';
	void InitialisationTrafficLights();
	*/


TrafficLightList* Liste=NULL;
TrafficLight* FEU1 = CreateTrafficLight(4, 5, VERT);
TrafficLight* FEU2 = CreateTrafficLight(3, 6, ROUGE);
AppendList(&Liste, FEU1);
AppendList(&Liste, FEU2);
VisualiserTrafficLightList(Liste);
Roulement_feux(Liste);
VisualiserTrafficLightList(Liste);



	return 0;
}

