#include "librairies.h"
#include "decision.h"

char** matrixInit()
{
	int i;
	char** Matrice = calloc(NBL, sizeof(char*));
	for(i = 0; i<NBL; i++) 
	{
		Matrice[i] = calloc(NBC, sizeof(char));
	}
	return Matrice;
}

void textToMatrix(char** Matrice, char* nomdufichiertexte)
{
	int i;	
	FILE* fichier = NULL;
	fichier=fopen(nomdufichiertexte, "r");
	size_t nombrecolomn = (size_t)NBC;
	for(i=0; i<NBL; i++) 
	{		
			getline(&Matrice[i], &nombrecolomn, fichier);

	}
	fclose(fichier);
}
