all: PROJET

affichage.o: affichage.c affichage.h librairies.h
	gcc -c -Wall -g -ggdb affichage.c
boats.o: boats.c boats.h librairies.h
	gcc -c -Wall -g -ggdb boats.c
decision.o: decision.c decision.h librairies.h
	gcc -c -Wall -g -ggdb decision.c
helicopteres.o: helicopteres.c helicopteres.h librairies.h
	gcc -c -Wall -g -ggdb helicopteres.c
lapins.o: lapins.c lapins.h librairies.h
	gcc -c -Wall -g -ggdb lapins.c
pietons.o: pietons.c pietons.h librairies.h
	gcc -c -Wall -g -ggdb pietons.c
trafficlights.o: trafficlights.c trafficlights.h librairies.h
	gcc -c -Wall -g -ggdb trafficlights.c
tramways.o: tramways.c tramways.h librairies.h
	gcc -c -Wall -g -ggdb tramways.c	
vehicules.o: vehicules.c vehicules.h librairies.h
	gcc -c -Wall -g -ggdb vehicules.c
main.o: main.c affichage.h boats.h decision.h helicopteres.h lapins.h pietons.h trafficlights.h tramways.h vehicules.h
	gcc -c -Wall -g -ggdb main.c
PROJET: affichage.o boats.o decision.o helicopteres.o lapins.o pietons.o trafficlights.o tramways.o vehicules.o main.o 
	gcc -o PROJET main.o affichage.o boats.o decision.o helicopteres.o lapins.o pietons.o trafficlights.o tramways.o vehicules.o
EXECUTION: 
	./PROJET
