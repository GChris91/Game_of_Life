#include <stdio.h>
#include <stdlib.h>

typedef struct {
int lin, col;
char ** cellules;
} monde ;


void initEmpty( monde *m, int lin, int col){       //Initialisation monde

int i;
int j;

(*m).lin=lin;
(*m).col=col;
(*m).cellules = malloc(  lin * sizeof( char * ) );

for(i=0; i<lin; i++){

    (*m).cellules[i]=malloc(col * sizeof(char));

    for(j=0; j<col; j++){
            (*m).cellules[i][j]=' ';
    }
}
}
