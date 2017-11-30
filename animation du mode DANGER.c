//animations du mode DANGER

void animation1(VehiculeList * ListeDesVehicules, Tramway * T, char *** MatriceDecision){
	//creer la voiture et le tram de sorte qu'ils se rencontre au point de coordonées
	//voiture et tram n'appartenant pas au listes, ils ont leur porpres directives (ils avances tous les deux de maniere rectiligne)
	//la voiture arrive un peu avant, le personnage sort , il est en panne !
	//le tram arrive et ne s'arrete pas.
	//collision et flammes.
	
	VehiculeList * tmp;
	tmp = * ListeDesVehicules;

	if(tmp->Vehicule->posX < 57){

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
				else if(tmp->Vehicule->CaseDecision == 'D')
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

			case '57': affichageVehicule(tmp->Vehicule);break;

			case 60: printf("\033[%d;%dH🚶", tmp->Vehicule->posX, tmp->Vehicule->posX+1);break;
			case 61: printf("\033[%d;%dH ", tmp->Vehicule->posX, tmp->Vehicule->posX+1);printf("\033[%d;%dH🚶", tmp->Vehicule->posX+1, tmp->Vehicule->posX+1);break;
			case 62: printf("\033[%d;%dH ", tmp->Vehicule->posX+1, tmp->Vehicule->posX+1);printf("\033[%d;%dH🚶", tmp->Vehicule->posX+1, tmp->Vehicule->posX);break;
			case 62: printf("\033[%d;%dH?", tmp->Vehicule->posX+1, tmp->Vehicule->posX+1);break;

			case 65: printf("\033[%d;%dH🚶", tmp->Vehicule->posX+1, tmp->Vehicule->posX+1);break;
			case 66: printf("\033[%d;%dH ", tmp->Vehicule->posX+1, tmp->Vehicule->posX+1);printf("\033[%d;%dH🚶", tmp->Vehicule->posX, tmp->Vehicule->posX+1);break;
			case 67: printf("\033[%d;%dH?", tmp->Vehicule->posX, tmp->Vehicule->posX+2);break;

			case 70: printf("\033[%d;%dH!", tmp->Vehicule->posX, tmp->Vehicule->posX+2);break;
		}
		
		if(80>tmp->Vehicule->posX>=71){

			printf("\033[%d;%dH🚘", tmp->Vehicule->posX+tmp->Vehicule->posX -70, tmp->Vehicule->posX+1);
			tmp->Vehicule->posX++;
			if(tmp->Vehicule->posX>=80)
		}

	}
}

