#include "monde.h"

#define MORT 0
#define VIE 1

#define CHAR_MORT ' '
#define CHAR_VIE '*'

///#define NB_GENERATIONS 10
#define VOISINES 8

void initEmpty(monde *m, int lin, int col){       //Initialisation monde

int i, j;

(*m).lin = lin;
(*m).col = col;

    (*m).cellules=malloc(lin * sizeof(char *));

    for(i = 0; i < lin; i++){

    (*m).cellules[i] = malloc(col * sizeof(char));

        for(j = 0; j < col; j++){
            (*m).cellules[i][j] = CHAR_MORT;
        }
    }
}


void print(monde *m){

    int i, j;

    for(i=0; i<(*m).lin; i++){
            for(j=0; j<(*m).col; j++){
                    printf("|%c", (*m).cellules[i][j]);
            }
            printf("|\n");
    }
        printf("\n");
}


char getCell(monde *m, int l, int c)
{
  return (*m).cellules[l][c];
}


void setCell(monde *m, int l, int c, char state)
{
    (*m).cellules[l][c] = state;
}


int nb_voisines (monde *m, int lin, int col)
{
	int n, cellVoisines, nlin, ncol;
	int tablin[VOISINES] = {-1,-1,-1,0,0,1,1,1};
	int tabcol[VOISINES] =  {-1,0,1,-1,1,-1,0,1};

	cellVoisines = 0;

	for (n = 0; n < VOISINES; n++) {

        if(((lin + tablin[n] >= 0)) && ((lin + tablin[n]) < (*m).lin) && ((col + tabcol[n]) >= 0) && ((col + tabcol[n]) < (*m).col)){

            nlin = lin + tablin[n];
            ncol = col + tabcol[n];

		if (getCell(m, nlin, ncol) == CHAR_VIE)
			cellVoisines++;
        }
    }
	return cellVoisines;
}


void evolve(monde * monde_avant, monde * monde_apres) ///A verifier
{
    int i, j, count;

    for(i = 0 ; i < (*monde_avant).lin ; i++){

        for(j = 0 ; j < (*monde_avant).col ; j++){

            count = nb_voisines(monde_avant, i, j);

            if (getCell(monde_avant, i, j) == CHAR_VIE){

                if ((count == 2) || (count == 3)){

                    setCell(monde_apres, i, j, CHAR_VIE);
                }else{

                    setCell(monde_apres, i, j, CHAR_MORT);
                }
            }else{

                if (count == 3){

                    setCell(monde_apres, i, j, CHAR_MORT);

                }else{

                    setCell(monde_apres, i, j, CHAR_VIE);
                }
            }
        }
    }

    for(i = 0 ; i < (*monde_avant).lin; i++){

        for(j = 0 ; j < (*monde_avant).col; j++){

            (*monde_avant).cellules[i][j] = (*monde_apres).cellules[i][j];
        }
    }
}


void runSimu(monde *monde_avant, monde *monde_apres, int NB_GENERATIONS)
{
    int i;

    for(i = 1; i <= NB_GENERATIONS; i++){

        print(monde_avant);
        evolve(monde_avant, monde_apres);
       /// system("cls");
    }

    print(monde_avant);
}


int initialize_world_from_file(char *filename, monde *m) ///Dur dur
{
	int i, j;
	char strread[256];
	char *pointer;
    FILE *pfile;
	pfile = fopen(filename, "r");

	if ((pfile = fopen(filename, "r")) == NULL){
		return (-1);
	}

	fscanf(pfile, "%d %d\n", &(*m).lin, &(*m).col);
    pointer = fgets(strread, (*m).col, pfile);

    initEmpty( m, (*m).lin, (*m).col);

    for(i=0; i<(*m).lin; i++){

        pointer = fgets(strread, (*m).col, pfile);

        if (pointer == NULL){
            return(-1);
        }

        for(j=0; j<(*m).col; j++){

            if (pointer[j] == VIE){
                setCell(m, i, j, VIE);
            }
        }
        pointer = NULL;
    }

	fclose(pfile);
    return(0);
}

int save_world_to_file(char *filename, monde *m)
{
    int i, j;
    char strread[256];
    FILE * pfile;

    pfile = fopen(filename, "w");

    if ((pfile = fopen(filename, "w")) == NULL){
		return(-1);
	}

    fprintf(pfile, "%d\n%d\n",(*m).lin, (*m).col);

    for(i = 0; i < (*m).lin; i++){

        for(j = 0 ; j < (*m).col; j++){

            strread[j] = (*m).cellules[i][j];
        }

        fprintf(pfile, strread);
        fprintf(pfile, "\n");
    }

    fprintf(pfile, "%d\n%d\n",(*m).lin, (*m).col);

	fclose(pfile);
    return(0);
}


void initRandomWorld(monde *m, int lin, int col, int nbCells)
{
    srand(time(NULL));
    int i = 0, j;
    int hasard;

    nbCells = (nbCells * lin * col)/100;

    while((i < col) && (nbCells > 0)){

        j = 0;

        while((j < col) && (nbCells > 0)){

            hasard = 1+rand()%(2);

            if(hasard == 1){

                if (getCell(m, i, j) == MORT){

                    setCell(m, i, j, VIE);

                    nbCells = nbCells-1;
                }
            }
            j = j + 1;
        }

        i = i + 1;

        if((i == lin) && (nbCells > 0)){

            i = 0;
        }
    }

    /// modulo nombre col puis partie entiere = nombre de lignes
    /// ou stocker variable par groupe de 2
}

