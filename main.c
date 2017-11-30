#include "launcher.h"


int main(){
	system("setterm -cursor off");

	int * affichage = 0;

	lancementMenu(&affichage);

	if(affichage == 0){
		lancementModeSafe();
	}else{
		lancementModeDanger();
	}
	printf("\033[67;1Hfin de l'execution.\n");

	return 0;
}