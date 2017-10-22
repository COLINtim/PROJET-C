#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#define couleur(param) printf("\033[%sm",param)
#define placement(a,b) printf("\33[%d;%dHâˆ¼",a,b)
#define placement1(a,b) printf("\33[%d;%dHâˆ½",a,b)
#define nombre_de_lignes 81
#define nombre_de_colonnes 194

