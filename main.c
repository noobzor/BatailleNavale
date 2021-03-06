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

void affichemap(int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
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
                    printf("%c ", (char)mapA[MAP_PLACE][j][k]);
                }
                 printf("\n");
            }
             printf("\n\n");

}

void affichemapjoueur(int tailleX, int tailleY,int choixmap, int map[MAP_PAR_JOUEUR][tailleX][tailleY])
{
   int j = 0;
   int k = 0;
   int a = 0;
   int b = 0;

    for (j = -1; j < tailleX; j++)
    {
        for (k = -1; k < tailleY; k++)
        {
            if (j == -1 && k == -1)
            {
                printf(" /");
            }
            else if(j == -1)
            {
                a = (k + 48 - 57)/10;
                b = (k + 1)%10;

                if(k+1+48 > 57)
                {
                    printf("%c", (char)a + 48 + 1);
                }
                else
                {
                    printf(" ");
                }
                printf("%c", (char)b + 48);
            }
            else if (k == -1)
            {
                a = (j + 48 - 57)/10;
                b = (j + 1)%10;

                if(j+1+48 > 57)
                {
                    printf("%c", (char)a + 48 + 1);

                }
                else
                {
                    printf(" ");
                }
                printf("%c", (char)b + 48);
                printf(" ");
            }
            else
            {
                printf("%c ", (char)map[choixmap][j][k]);
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
            affichemapjoueur(tailleX, tailleY, MAP_PLACE, map);
            valide = 1;
            switch(i + 1)
            {
                case 1:
                    printf("placez votre porte-avion (taille 5)\n");
                    break;
            }

            do
            {
                printf("choisir position verticale (entre 1 et %d): ", tailleX);
                scanf("%d", &xB);
                xB--;
                fflush(stdin);
            }
            while (xB < 0 &&xB > tailleX);

            do
            {
                printf("choisir position horizontale (entre 1 et %d): ", tailleY);
                scanf("%d", &yB);
                yB--;
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

void attaque_facile(int* pv, int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int xB = 0;
    int yB = 0;

    do
    {
        xB = doRand(0, tailleX + 1);
        yB = doRand(0, tailleY + 1);
    }
    while(mapA[MAP_TIR][xB][yB] == MAP_TOUCHE || mapA[MAP_TIR][xB][yB] == MAP_RATE);

    if(mapB[MAP_PLACE][xB][yB] == MAP_VIDE)
    {
        mapA[MAP_TIR][xB][yB] = MAP_RATE;
        printf("rate\n");
    }
    else
    {
        mapA[MAP_TIR][xB][yB] = MAP_TOUCHE;
        *pv = *pv - 1;
        printf("touche\n");
    }
    printf("en x:%d y:%d\n", xB, yB);
    printf("%d", *pv);
}

void attaque(int cherche[5], int* pv, int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int xB = 0;
    int yB = 0;
    int joue = 0;

    while(joue == 0)
    {
        joue = 1;
        switch(cherche[CHERCHE_TYPE])
        {
            case 0:
                do
                {
                    xB = doRand(0, tailleX + 1);
                    yB = doRand(0, tailleY + 1);
                }
                while(mapA[MAP_TIR][xB][yB] == MAP_TOUCHE || mapA[MAP_TIR][xB][yB] == MAP_RATE);

                if(mapB[MAP_PLACE][xB][yB] == MAP_VIDE)
                {
                    mapA[MAP_TIR][xB][yB] = MAP_RATE;
                    printf("rate\n");
                }
                else
                {
                    mapA[MAP_TIR][xB][yB] = MAP_TOUCHE;
                    *pv = *pv - 1;
                    printf("touche\n");
                    cherche[CHERCHE_TYPE] = 1;
                    cherche[CHERCHE_POSX_INI] = xB;
                    cherche[CHERCHE_POSY_INI] = yB;
                    cherche[CHERCHE_POSX_ACTU] = xB;
                    cherche[CHERCHE_POSY_ACTU] = yB;
                }
                break;

            case 1:
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
                }
                break;

            case 2:
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
                }
                break;

            case 3:
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
                }
                break;
            case 4:
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
                }
                break;
        }
    }
    printf("en x:%d y:%d\n", cherche[CHERCHE_POSX_ACTU],cherche[CHERCHE_POSY_ACTU]);
    printf("%d", *pv);
}

void attaque_joueur(int* pv, int tailleX,  int tailleY, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int xB = 0;
    int yB = 0;

    affichemapjoueur(tailleX, tailleY, MAP_TIR, mapA);

    do
    {
        do
        {
            printf("choisir attaque verticale (entre 1 et %d): ", tailleX);
            scanf("%d", &xB);
            xB--;
            fflush(stdin);
        }
        while (xB < 0 || xB > tailleX);

        do
        {
            printf("choisir attaque horizontale (entre 1 et %d): ", tailleY);
            scanf("%d", &yB);
            yB--;
            fflush(stdin);
        }
        while (yB < 0 || yB > tailleY);

        if (mapA[MAP_TIR][xB][yB] != MAP_VIDE)
        {
            printf("deja fait, reessayer\n");
        }
    }
    while (mapA[MAP_TIR][xB][yB] != MAP_VIDE);


    if (mapB[MAP_PLACE][xB][yB] == MAP_VIDE)
    {
        mapA[MAP_TIR][xB][yB] = MAP_RATE;
        printf("RATE\n");
    }
    else
    {
       mapA[MAP_TIR][xB][yB] = MAP_TOUCHE;
        *pv = *pv - 1;
        printf("TOUCHE\n");
    }
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
void FilerWrite(int difficulte, int tailleX, int tailleY, int pvA, int pvB, int mapA[MAP_PAR_JOUEUR][tailleX][tailleY], int mapB[MAP_PAR_JOUEUR][tailleX][tailleY])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    FILE* ftp = fopen("./sauvegarde.txt","w");

    fprintf(ftp,"%c\n",(char)difficulte);
    fprintf(ftp,"%c\n",(char)tailleX);
    fprintf(ftp,"%c\n",(char)tailleY);
    fprintf(ftp,"%c\n",(char)pvA);
    fprintf(ftp,"%c\n",(char)pvB);

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            for (k = 0; k < tailleX; k++)
            {
                for (l = 0; l < tailleY; l++)
                {
                    if (i == 0)
                    {
                        fprintf(ftp,"%c\n",(char)mapA[j][k][l]);
                    }
                    else
                    {
                        fprintf(ftp,"%c\n",(char)mapB[j][k][l]);
                    }
                }
            }
        }
    }
    fclose(ftp);
}

int main()
{
    int pvJ1 = PV_TOT;
    int pvJ2 = PV_TOT;
    int tailleX = 0;
    int tailleY = 0;
    int chercheJ1[5] = {0};
    int chercheJ2[5] = {0};
    int nb_joueur = 1;
    int partie = 0;
    int difficulte = 0;
    char c;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;


    do
    {
        printf("choisir\nNouvelle partie[0]\nCharger partie[1]\n");
        scanf("%d", &partie);
        fflush(stdin);
    }
    while (nb_joueur != 0 && nb_joueur != 1);

    if (partie == 0)
    {
        do
        {
            printf("choisir nombre de joueur(0 ou 1): ");
            scanf("%d", &nb_joueur);
            fflush(stdin);
        }
        while (nb_joueur != 0 && nb_joueur != 1);

        printf("\n");

        do
        {
            printf("choisir difficulte\nmousse [0]\ncapitaine [1]\n");
            scanf("%d", &difficulte);
            fflush(stdin);
        }
        while (difficulte != 0 && difficulte != 1);

        printf("\n");

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

    }
    else
    {
        FILE* fptr = fopen("./sauvegarde.txt","r");


        c = fgetc(fptr);
        difficulte = (int)c;
        c = fgetc(fptr);
        c = fgetc(fptr);
        tailleX = (int)c;
        c = fgetc(fptr);
        c = fgetc(fptr);
        tailleY = (int)c;
        c = fgetc(fptr);
        c = fgetc(fptr);
        pvJ1 = (int)c;
        c = fgetc(fptr);
        c = fgetc(fptr);
        pvJ2 = (int)c;

        fclose(fptr);

    }

        int mapJ1[MAP_PAR_JOUEUR][tailleX][tailleY];
        int mapJ2[MAP_PAR_JOUEUR][tailleX][tailleY];

    if (partie == 0)
    {
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

    }
    else
    {
        FILE* fptr = fopen("./sauvegarde.txt","r");

        if(fptr == NULL)
        {
        perror("Erreur aucun fichier de sauvegarde");
        return(-1);
        }

        for(i = 0; i < 10; i++)
        {
            c = fgetc(fptr);
        }

        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 2; j++)
            {
                for (k = 0; k < tailleX; k++)
                {
                    for (l = 0; l < tailleY; l++)
                    {
                        if (i == 0)
                        {
                            c = fgetc(fptr);
                            mapJ1[j][k][l] = (int)c;
                            c = fgetc(fptr);
                        }
                        else
                        {
                            c = fgetc(fptr);
                            mapJ2[j][k][l] = (int)c;
                            c = fgetc(fptr);
                        }
                    }
                }
            }
        }

        fclose(fptr);
    }

    do
    {
        if (nb_joueur == 0)
        {
            printf("J1 attaque J2\n");

            if (difficulte == 0)
            {
                attaque_facile(&pvJ2, tailleX, tailleY, mapJ1, mapJ2);
            }
            else
            {
                attaque(chercheJ1, &pvJ2, tailleX, tailleY, mapJ1, mapJ2);
            }


            printf("pv restant a J2\n");
        }
        else
        {
            attaque_joueur(&pvJ2, tailleX, tailleY, mapJ1, mapJ2);
            printf("pv restant a J2\n");

        }

        printf("\n");
        printf("J2 attaque J1\n");

        if (difficulte == 0)
            {
                attaque_facile(&pvJ1, tailleX, tailleY, mapJ2, mapJ1);
            }
            else
            {
                attaque(chercheJ2, &pvJ1, tailleX, tailleY, mapJ2, mapJ1);
            }

        printf("pv restant a J1\n");
        printf("\n");

        FilerWrite(difficulte, tailleX, tailleY, pvJ1, pvJ2, mapJ1, mapJ2);
    }
    while(pvJ1 > 0 && pvJ2 > 0);

    printf("Joueur1:\n");
    affichemap(tailleX, tailleY, mapJ1, mapJ2);
    printf("Joueur2:\n");
    affichemap(tailleX, tailleY, mapJ2, mapJ1);

    victoire(pvJ1,pvJ2);

    return 0;
}
