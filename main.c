#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_PLACE 0
#define MAP_TIR 1
#define MAP_PAR_JOUEUR 2
#define MAP_VIDE 126
#define MAP_RATE 111
#define MAP_TOUCHE 120
#define NB_BATEAU 5
const int BATEAU[NB_BATEAU] = { 5, 4, 3, 3, 2};
#define PV_TOT 17
#define CHERCHE_TYPE 0
#define CHERCHE_POSX_INI 1
#define CHERCHE_POSY_INI 2
#define CHERCHE_POSX_ACTU 3
#define CHERCHE_POSY_ACTU 4
//bonjour

void waitFor (unsigned int secs)
{
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int doRand(int startVal, int endVal)
{
    waitFor(0.05);
    srand(time(NULL)*rand());

    if(startVal == 0 && endVal == 1)
    {
        return rand() % 2;
    }
    else
    {
        return (rand() % ((endVal + startVal -1)) + startVal);
    }
}

void GenereMap(int tailleX,  int tailleY, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{

    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < tailleX; j++)
        {
            for (k = 0; k < tailleY; k++)
            {
                map[i][j][k] = MAP_VIDE;
            }
        }
    }
}

void affichemap(int tailleX,  int tailleY, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int i;
    int j;
    int k;

    for (i = 0; i < 2; i++)
        {
            for (j = 0; j < tailleX; j++)
            {
                for (k = 0; k < tailleY; k++)
                {
                    printf("%c ", (char)map[i][j][k]);
                }
                 printf("\n");
            }
             printf("\n\n");
        }
        printf("\n");
}

void affichecontrole(int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int j;
    int k;


            for (j = 0; j < tailleX; j++)
            {
                for (k = 0; k < tailleY; k++)
                {
                    printf("%c ", (char)mapA[MAP_TIR][j][k]);
                }
                 printf("         ");

                for (k = 0; k < tailleY; k++)
                {
                    printf("%c ", (char)mapB[MAP_PLACE][j][k]);
                }
                 printf("\n");
            }
             printf("\n\n");

}

void affichemapjoueur(int tailleX,  int tailleY, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{
   int j = 0;
   int k = 0;

    for (j = -1; j < tailleX; j++)
    {
        for (k = -1; k < tailleY; k++)
        {
            if (j == -1 && k == -1)
            {
                printf("%c ", '/');
            }
            else if(j == -1)
            {
                printf("%c ", (char)k+1+48);
            }
            else
            {
                printf("%c ", (char)map[MAP_PLACE][j][k]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int verifplace(int xB, int yB, int indice, int position, int tailleX, int tailleY, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int k = 0;

    if (position == 0)
                {
                   for (k = 0; k < BATEAU[indice]; k++)
                        {
                           if(map[MAP_PLACE][xB + k][yB] != MAP_VIDE || xB + k >= tailleX)
                                return 0;
                       }
                }
                else
                {
                    for (k = 0; k < BATEAU [indice]; k++)
                        {
                           if(map[MAP_PLACE][xB][yB + k] != MAP_VIDE || yB + k >= tailleY)
                                return 0;
                        }

                }
    return (1);
}

void placeBateau(int tailleX,  int tailleY, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int j = 0;
    int k = 0;
    int xB = 0;
    int yB = 0;
    int valide = 0;
    int position = 0;



    for(j = 0 ; j < NB_BATEAU; j++)
    {
        do
        {
            valide = 1;
            xB = doRand(0, tailleX);
            yB = doRand(0, tailleY);
            position = doRand(0,1);

            valide = verifplace(xB, yB, j, position, tailleX, tailleY, map);

        }
        while(valide == 0);

        if (position == 0)
        {
            for (k = 0; k < BATEAU[j]; k++)
            {
                map[MAP_PLACE][xB + k][yB] = j+1+48;
            }
        }
        else
        {
            for (k = 0; k < BATEAU[j]; k++)
            {
                map[MAP_PLACE][xB][yB + k] = j+1+48;
            }

        }
    }
}

void placebateau_joueur(int tailleX, int tailleY, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int i = 0;
    int k = 0;
    int xB = 0;
    int yB = 0;
    int valide = 0;
    int position = 0;

    for(i = 0; i < NB_BATEAU; i++)
    {
        do
        {
            affichemapjoueur(tailleX, tailleY, map);
            valide = 1;
            switch(i + 1)
            {
                case 1:
                    printf("placez votre porte-avion (taille 5)\n");
                    break;
            }

            do
            {
                printf("choisir taille verticale (entre 0 et %d): ", tailleX);
                scanf("%d", &xB);
                fflush(stdin);
            }
            while (xB < 0 &&xB > tailleX);

            do
            {
                printf("choisir taille horizontale (entre 0 et %d): ", tailleY);
                scanf("%d", &yB);
                fflush(stdin);
            }
            while (yB < 0 && yB > tailleY);

            do
            {
                printf("choisir positionnement: [0]vertical [1]horizontal\n");
                scanf("%d", &position);
                fflush(stdin);
            }
            while (position < 0 && position > 1);

            valide = verifplace(xB, yB, i, position, tailleX, tailleY, map);
        }
        while(valide == 0);

        if (position == 0)
        {
            for (k = 0; k < BATEAU[i]; k++)
            {
                map[MAP_PLACE][xB + k][yB] = i+1+48;
            }
        }
        else
        {
            for (k = 0; k < BATEAU[i]; k++)
            {
                map[MAP_PLACE][xB][yB + k] = i+1+48;
            }

        }

    }
}

void attaque(int* xB, int* yB, int cherche[5], int* pv, int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{

   int joue = 0;

    while(joue == 0)
    {
        joue = 1;
        switch(cherche[CHERCHE_TYPE])
        {
            case 0:
                do
                {
                    *xB = doRand(0, tailleX + 1);
                    *yB = doRand(0, tailleY + 1);
                }
                while(mapA[MAP_TIR][*xB][*yB] == MAP_TOUCHE || mapA[MAP_TIR][*xB][*yB] == MAP_RATE);

               affichecontrole(tailleX, tailleY, mapA, mapB);

                if(mapB[MAP_PLACE][*xB][*yB] == MAP_VIDE)
                {
                    mapA[MAP_TIR][*xB][*yB] = MAP_RATE;
                }
                else
                {
                    mapA[MAP_TIR][*xB][*yB] = MAP_TOUCHE;
                    *pv = *pv - 1;
                    printf("touche\n");
                    printf("%d\n", *pv);
                    cherche[CHERCHE_TYPE] = 1;
                    cherche[CHERCHE_POSX_INI] = *xB;
                    cherche[CHERCHE_POSY_INI] = *yB;
                    cherche[CHERCHE_POSX_ACTU] = *xB;
                    cherche[CHERCHE_POSY_ACTU] = *yB;
                }
                break;

            case 1:
                printf("cas1\n");
                if (cherche[CHERCHE_POSX_ACTU] + 1 > tailleX -1 ||  mapA[MAP_TIR][cherche[CHERCHE_POSX_ACTU] + 1][cherche[CHERCHE_POSY_INI]] != MAP_VIDE)
                {
                     joue = 0;
                     cherche[CHERCHE_POSX_ACTU] = cherche[CHERCHE_POSX_INI];
                     cherche[CHERCHE_TYPE] = 2;
                }
                else if(mapB[MAP_PLACE][cherche[CHERCHE_POSX_ACTU] + 1][cherche[CHERCHE_POSY_INI]] == MAP_VIDE)
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_ACTU] + 1][cherche[CHERCHE_POSY_INI]] = MAP_RATE;
                    cherche[CHERCHE_POSX_ACTU] = cherche[CHERCHE_POSX_INI];
                    cherche[CHERCHE_TYPE] = 2;
                }
                else
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_ACTU] + 1][cherche[CHERCHE_POSY_INI]] = MAP_TOUCHE;
                    *pv = *pv - 1;
                    cherche[CHERCHE_POSX_ACTU] = cherche[CHERCHE_POSX_ACTU] + 1;
                    printf("touche\n");
                    printf("%d\n", *pv);

                }
                break;

            case 2:
                printf("cas2\n");
                if (cherche[CHERCHE_POSX_ACTU] - 1 < 0 ||  mapA[MAP_TIR][cherche[CHERCHE_POSX_ACTU] - 1 ][cherche[CHERCHE_POSY_INI]] != MAP_VIDE)
                {
                     joue = 0;
                     cherche[CHERCHE_POSX_ACTU] = cherche[CHERCHE_POSX_INI];
                     cherche[CHERCHE_TYPE] = 3;
                }
                else if(mapB[MAP_PLACE][cherche[CHERCHE_POSX_ACTU] - 1][cherche[CHERCHE_POSY_INI]] == MAP_VIDE)
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_ACTU] - 1][cherche[CHERCHE_POSY_INI]] = MAP_RATE;
                    cherche[CHERCHE_POSX_ACTU] = cherche[CHERCHE_POSX_INI];
                    cherche[CHERCHE_TYPE] = 3;
                }
                else
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_ACTU] - 1][cherche[CHERCHE_POSY_INI]] = MAP_TOUCHE;
                    *pv = *pv - 1;
                    cherche[CHERCHE_POSX_ACTU] = cherche[CHERCHE_POSX_ACTU] - 1;
                    printf("touche\n");
                    printf("%d\n", *pv);
                }
                break;

            case 3:
                printf("cas3\n");
                if (cherche[CHERCHE_POSY_ACTU]  + 1 > tailleY - 1 ||  mapA[MAP_TIR][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] + 1] != MAP_VIDE)
                {
                     joue = 0;
                     cherche[CHERCHE_POSY_ACTU] = cherche[CHERCHE_POSY_INI];
                     cherche[CHERCHE_TYPE] = 4;
                }
                else if(mapB[MAP_PLACE][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] + 1] == MAP_VIDE)
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] + 1] = MAP_RATE;
                    cherche[CHERCHE_POSY_ACTU] = cherche[CHERCHE_POSY_INI];
                    cherche[CHERCHE_TYPE] = 4;
                }
                else
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] + 1] = MAP_TOUCHE;
                    *pv = *pv - 1;
                    cherche[CHERCHE_POSY_ACTU] = cherche[CHERCHE_POSY_ACTU] + 1;
                    printf("touche\n");
                    printf("%d\n", *pv);
                }
                break;
            case 4:
                printf("cas4\n");
                if (cherche[CHERCHE_POSY_ACTU]  - 1 < 0 ||  mapA[MAP_TIR][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] - 1] != MAP_VIDE)
                {
                     joue = 0;
                     cherche[CHERCHE_POSY_ACTU] = cherche[CHERCHE_POSY_INI];
                     cherche[CHERCHE_TYPE] = 0;
                }
                else if(mapB[MAP_PLACE][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] - 1] == MAP_VIDE)
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] - 1] = MAP_RATE;
                    cherche[CHERCHE_POSY_ACTU] = cherche[CHERCHE_POSY_INI];
                    cherche[CHERCHE_TYPE] = 0;
                }
                else
                {
                    mapA[MAP_TIR][cherche[CHERCHE_POSX_INI]][cherche[CHERCHE_POSY_ACTU] - 1] = MAP_TOUCHE;
                    *pv = *pv - 1;
                    cherche[CHERCHE_POSY_ACTU] = cherche[CHERCHE_POSY_ACTU] - 1;
                    printf("touche\n");
                    printf("%d\n", *pv);
                }
                break;
        }
    }
   // printf("x:%d y:%d\n", *xB, *yB);
    printf("x:%d y:%d\n", cherche[3],cherche[4]);
    affichecontrole(tailleX, tailleY, mapA, mapB);
}

void attaque_joueur(int* xB, int* yB, int cherche[5], int* pv, int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{

}

void victoire(int pvJ1, int pvJ2)
{
    if(pvJ2 == 0)
    {
        printf("J1 a gagner\n\n");
    }
    else
    {
        printf("J2 a gagner\n\n");
    }
}

int main()
{
    int pvJ1 = PV_TOT;
    int pvJ2 = PV_TOT;
    int tailleX = 0;
    int tailleY = 0;
    int chercheJ1[5] = {0};
    int chercheJ2[5] = {0};
    int x1B = 0;
    int x2B = 0;
    int y1B = 0;
    int y2B = 0;
    int nb_joueur = 0;

    do
    {
        printf("choisir nombre de joueur: ");
        scanf("%d", &nb_joueur);
        fflush(stdin);
    }
    while (nb_joueur != 0 && nb_joueur != 1);

    do
    {
        printf("choisir taille verticale (entre 6 et 99): ");
        scanf("%d", &tailleX);
        fflush(stdin);
    }
    while (tailleX < 6 || tailleX > 99);

    do
    {
        printf("choisir taille horizontale (entre 6 et 99): ");
        scanf("%d", &tailleY);
        fflush(stdin);
    }
    while (tailleY < 6 || tailleY > 99);

    int mapJ1[MAP_PAR_JOUEUR][tailleX][tailleY];
    int mapJ2[MAP_PAR_JOUEUR][tailleX][tailleY];


    GenereMap(tailleX, tailleY, mapJ1);
    GenereMap(tailleX, tailleY, mapJ2);

    if (nb_joueur == 0)
    {
        placeBateau(tailleX, tailleY, mapJ1);
    }
    else
    {
        placebateau_joueur(tailleX, tailleY, mapJ1);
    }

    placeBateau(tailleX, tailleY, mapJ2);



    do
    {
        if (nb_joueur == 0)
        {
            printf("J1 attaque J2 en :\n");
            attaque(&x1B, &y1B, chercheJ1, &pvJ2, tailleX, tailleY, mapJ1, mapJ2);
        }
        else
        {
            attaque_joueur(&x1B, &y1B, chercheJ1, &pvJ2, tailleX, tailleY, mapJ1, mapJ2);
        }

        printf("J2 attaque J1 en :\n");
        attaque(&x2B, &y2B, chercheJ2, &pvJ1, tailleX, tailleY, mapJ2, mapJ1);
    }
    while(pvJ1 > 0 && pvJ2 > 0);

    printf("Joueur1:\n");
    affichemap(tailleX, tailleY, mapJ1);
    printf("Joueur2:\n");
    affichemap(tailleX, tailleY, mapJ2);

    victoire(pvJ1,pvJ2);

    return 0;
}
