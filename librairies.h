#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define couleur(param) printf("\033[%sm",param)

#define nombre_de_lignes 81
#define nombre_de_colonnes 194
