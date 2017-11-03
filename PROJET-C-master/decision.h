#include "librairies.h"

char** MatrixInit(int NBC, int NBL); //Initialise une Matrice de taille (NBC,NBL)

void TextToMatrix(int NBC, int NBL, char** MATRIX, char* nomdufichier); //Initialise et renvoit une Matrice remplie du fichier decision.txt

void ShowMatrix(int NBC, int NBL, char** MATRIX); //Fonction affichant une Matrice de taille(NBL,NBC)

char swap(char); // ouvre ou ferme "la porte" (feu) sur le char **

void RoulementFeuxDecision(int NBC, int NBL, char ** MATRIX); // Effectue un roulement des feux sur le tableau (ferme/ouvre les portes) A appeler avec RoulementFeux qui porte sur la liste des feux

