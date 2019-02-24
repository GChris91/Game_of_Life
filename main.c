#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "monde.h"


int main(){

    int init, NB_GENERATIONS;
    char filename[50];
    char c;
    int taux_vie;
    srand(time(NULL));

    monde *m_alea = malloc(sizeof(monde *));
    monde *monde_apres = malloc(sizeof(monde *));

    printf("Initialisation via fichier?\n");
    printf("Yes [Y] / No [n]\n");

    c = getchar();

    switch (c)
        {
        case 'Y':
        case 'y':
        printf("Nom du fichier\n");
        scanf("%s", filename);

        init = initialize_world_from_file(filename, m_alea);

        if (init == -1){
            printf("Erreur, fichier manquant");
            return(-1);
        }

        (*monde_apres).lin = (*m_alea).lin;
        (*monde_apres).col = (*m_alea).col;

        initEmpty(monde_apres, (*monde_apres).lin, (*monde_apres).col);

        printf("Combien de generations?\n");
        scanf("%d", &NB_GENERATIONS);

        runSimu(m_alea, monde_apres, NB_GENERATIONS);
                break;

        case 'N':
        case 'n':

        printf("\n\nInitialisation du monde\n");


        printf("Nombre de lignes?\n");
        scanf("%d", &(*m_alea).lin);

        printf("Nombre de colonnes?\n");
        scanf("%d", &(*m_alea).col);

        (*monde_apres).col = (*m_alea).col;
        (*monde_apres).lin = (*m_alea).lin;

        initEmpty(m_alea, (*m_alea).lin, (*m_alea).col);
        initEmpty(monde_apres, (*monde_apres).lin, (*monde_apres).col);

        printf("Combien de generations?\n");
        scanf("%d", &NB_GENERATIONS);

        printf("Quel taux de vie?\n");
        scanf("%d", &taux_vie);

        initRandomWorld(m_alea, (*m_alea).lin, (*m_alea).col, taux_vie);

        runSimu(m_alea, monde_apres, NB_GENERATIONS);

        break;

        default:
            printf("Error, write Y or N");
            break;
        }


    return 1;
}
