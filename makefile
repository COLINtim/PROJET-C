all: PROJET EXECUTION

affichage.o: affichage.c affichage.h librairies.h
	gcc -c -Wall affichage.c
main.o: main.c affichage.h 
	gcc -c -Wall main.c
PROJET: affichage.o main.o 
	gcc -o PROJET main.o affichage.o
EXECUTION: 
	./PROJET
