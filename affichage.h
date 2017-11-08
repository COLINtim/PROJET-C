#include "librairies.h"
#include "vehicules.h"
#include "boats.h"
#include "trafficlights.h"


void attente();//permet de faire une pause a certains  moments

void Key_pressed();// recuperation de la derniere touche pressée

void affichageMap();//affiche la carte, l'arriere-plan

void affichageFeu(TrafficLight);

void affichageVoiture(Vehicule);

void affichageBoat(Boat);
/*
void affichageTramwayHaut(Tramway);

void affichageTramwayBas(Tramway);

void affichagePieton(Pieton);

void affichageComplet(Voiture,Tramway,Pieton);//affichage general de la carte (comprenant toutes les entitées en mouvement)
*/
void initVehicule(Vehicule *);

void initBoat(Boat *);
