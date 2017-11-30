all: PROJET

affichage.o: affichage.c affichage.h librairies.h
	gcc -c -Wall -g -ggdb affichage.c
boats.o: boats.c boats.h 
	gcc -c -Wall -g -ggdb boats.c
decision.o: decision.c decision.h 
	gcc -c -Wall -g -ggdb decision.c
helicopteres.o: helicopteres.c helicopteres.h 
	gcc -c -Wall -g -ggdb helicopteres.c
lapins.o: lapins.c lapins.h 
	gcc -c -Wall -g -ggdb lapins.c
pietons.o: pietons.c pietons.h 
	gcc -c -Wall -g -ggdb pietons.c
trafficlights.o: trafficlights.c trafficlights.h 
	gcc -c -Wall -g -ggdb trafficlights.c
tramways.o: tramways.c tramways.h 
	gcc -c -Wall -g -ggdb tramways.c	
vehicules.o: vehicules.c vehicules.h 
	gcc -c -Wall -g -ggdb vehicules.c
launcher.o: launcher.c launcher.h 
	gcc -c -Wall -g -ggdb launcher.c
main.o: main.c
	gcc -c -Wall -g -ggdb main.c
PROJET: affichage.o boats.o decision.o helicopteres.o lapins.o pietons.o trafficlights.o tramways.o vehicules.o launcher.o main.o 
	gcc -o PROJET main.o affichage.o boats.o decision.o helicopteres.o lapins.o pietons.o trafficlights.o tramways.o vehicules.o launcher.o
EXECUTION: 
	./PROJET
