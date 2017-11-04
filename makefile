all: PROJET EXECUTION

boats.o: boats.c boats.h librairies.h
	gcc -c -Wall -g -ggdb boats.c
decision.o: decision.c decision.h
	gcc -c -Wall -g -ggdb decision.c
trafficlights.o: trafficlights.c trafficlights.h
	gcc -c -Wall -g -ggdb trafficlights.c
vehicules.o: vehicules.c vehicules.h
	gcc -c -Wall -g -ggdb vehicules.c
affichage.o: affichage.c affichage.h
	gcc -c -Wall -g -ggdb affichage.c
main.o: main.c affichage.h boats.h decision.h trafficlights.h vehicules.h
	gcc -c -Wall -g -ggdb main.c
PROJET: boats.o decision.o trafficlights.o vehicules.o affichage.o main.o 
	gcc -o PROJET main.o affichage.o boats.o decision.o trafficlights.o vehicules.o
EXECUTION: 
	./PROJET
