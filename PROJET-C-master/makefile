all: PROJET

affichage.o: affichage.c affichage.h librairies.h boats.h trafficlights.h vehicules.h
	gcc -c -Wall  affichage.c
boats.o: boats.c boats.h librairies.h
	gcc -c -Wall  boats.c
decision.o: decision.c decision.h librairies.h
	gcc -c -Wall  decision.c
trafficlights.o: trafficlights.c trafficlights.h librairies.h
	gcc -c -Wall  trafficlights.c
vehicules.o: vehicules.c vehicules.h librairies.h
	gcc -c -Wall  vehicules.c
main.o: main.c affichage.h boats.h decision.h trafficlights.h vehicules.h
	gcc -c -Wall  main.c
PROJET: affichage.o boats.o decision.o trafficlights.o vehicules.o main.o 
	gcc -o PROJET main.o affichage.o boats.o decision.o trafficlights.o vehicules.o
EXECUTION: 
	./PROJET
