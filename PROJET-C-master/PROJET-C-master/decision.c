#include "librairies.h"
#include "decision.h"

char** MatrixInit(int NBC, int NBL)
{
	int i;
	char** Matrice = calloc(NBL, sizeof(char*));
	for(i = 0; i<NBL; i++)
	{
		Matrice[i] = calloc(NBC, sizeof(char));
	}
	return Matrice;
}

void TextToMatrix(int NBC, int NBL, char** Matrice, char* nomdufichiertexte)
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



void ShowMatrix(int NBC, int NBL, char** Matrice)
{
	int i;
	for(i = 0; i < NBL; i++)
	{
		printf("%s", Matrice[i]);
	}
	printf("\nfin affichage\n");
}
	
char swap(char a)
{
	if(a=='o')
		{
			return 'f';
		}
	else{
		return 'o';
	}
}

void RoulementFeuxDecision(int NBC, int NBL, char ** Matrice)
{
	int i;
	int j;
	for(i=0; i < NBL; i++)
	{
		for(j=0; j < NBC; j++)
			{
				if(Matrice[i][j]=='o')
					{
						Matrice[i][j]='f';
					}
				if(Matrice[i][j]=='f')
					{
						Matrice[i][j]='o';
					}
			}
	}
}		

/* PAR FAMILLE DE FEUX => Pas de bug mais les coordonnées semblent fausses ... smh
	//FEUX HORIZONTAUX
	
	MATRIX[59][86]=swap(MATRIX[59][86]);
	MATRIX[59][90]=swap(MATRIX[59][90]);

	MATRIX[55][86]=swap(MATRIX[55][86]);
	MATRIX[55][90]=swap(MATRIX[55][90]);
	
	MATRIX[49][49]=swap(MATRIX[49][49]);
	MATRIX[49][53]=swap(MATRIX[49][53]);
	
	MATRIX[43][49]=swap(MATRIX[43][49]);
	MATRIX[43][53]=swap(MATRIX[43][53]);

	MATRIX[20][60]=swap(MATRIX[20][60]);
	MATRIX[20][64]=swap(MATRIX[20][64]);
	
	MATRIX[20][86]=swap(MATRIX[20][86]);
	MATRIX[20][90]=swap(MATRIX[20][90]);
	
	MATRIX[20][120]=swap(MATRIX[20][120]);
	MATRIX[20][124]=swap(MATRIX[20][124]);
	
	MATRIX[26][86]=swap(MATRIX[26][86]);
	MATRIX[26][90]=swap(MATRIX[26][90]);

	//FEUX VERTICAUX

	MATRIX[45][45]=swap(MATRIX[45][45]);
	MATRIX[45][47]=swap(MATRIX[45][47]);
	
	MATRIX[57][45]=swap(MATRIX[57][45]);
	MATRIX[57][47]=swap(MATRIX[57][47]);
	
	MATRIX[57][22]=swap(MATRIX[57][22]);
	MATRIX[57][24]=swap(MATRIX[57][24]);
	
	MATRIX[67][22]=swap(MATRIX[67][22]);
	MATRIX[67][24]=swap(MATRIX[67][24]);
	
	MATRIX[84][22]=swap(MATRIX[84][22]);
	MATRIX[84][24]=swap(MATRIX[84][24]);
	
	MATRIX[92][22]=swap(MATRIX[92][22]);
	MATRIX[92][24]=swap(MATRIX[92][24]);
	
	MATRIX[116][22]=swap(MATRIX[116][22]);
	MATRIX[116][24]=swap(MATRIX[116][24]);
	
	MATRIX[128][22]=swap(MATRIX[128][22]);
	MATRIX[128][24]=swap(MATRIX[128][24]);

*/



