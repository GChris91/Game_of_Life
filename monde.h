#ifndef MONDE_H_INCLUDED
#define MONDE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
int lin, col;
char ** cellules;
} monde ;


void initEmpty(monde *m, int lin, int col);
// Initialisation du monde vide

void print(monde *m);
// Affichage du monde

char getCell(monde *m, int l, int c);


void setCell(monde *m, int l, int c, char state);


int nb_voisines (monde *m, int lin, int col);


void evolve(monde *monde_avant, monde *monde_apres);


void runSimu(monde *monde_avant, monde *monde_apres, int NB_GENERATIONS);


int initialize_world_from_file(char *filename, monde *m);


int save_world_to_file(char * filename, monde * m);


void initRandomWorld(monde *m, int lin, int col, int nbCells);


#endif // MONDE_H_INCLUDED
