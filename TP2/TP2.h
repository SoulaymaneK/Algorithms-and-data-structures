//
// Created by Soulaymane  on 17/03/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

/*
 * ----Exercice 1----
 */

int fact1(int n)
{
    int fact = 1;
    for (int i = 2; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int fact2(int n)
{
    if (n==0)
        return 1;
    else
        return n* fact2(n-1);
}

int det(int n, int **mat)
{
    if (n==1)
        return 1;
    else if (n%2 == 0)
    {
        return mat[n][0]+det(n-1, mat);
    }
    else if (n%2 == 1)
    {
        return mat[n-n][0]-det(n-1, mat);
    }
}

int fibo1(int n)
{
    if (n==0)
        return 0;
    else if (n==1)
        return 1;
    else
        return fibo1(n-1)+ fibo1(n-2);
}

int fibo2(int n)
{
    if(n==0)
        return 0;
    else if (n==1)
        return 1;
    else if (n%2==0)
        return pow(fibo2(n/2),2)+2*fibo2(n/2)*fibo2((n/2)-1);
    else if (n%2==1)
        return pow(fibo2(n/2),2)+pow(fibo2((n/2)+1),2);
}
/*
    clock_t start, end;
    double elapsed;
    start = clock();
    printf("fibo1 de %d : %d", 6, fibo1(6));
    printf("\nfibo2 de %d : %d", 6, fibo2(6));
    end = clock();
    elapsed = ((double)end - start) / CLOCKS_PER_SEC;
    printf("\n%f",elapsed);
 */

typedef struct {
    int *tab;
    int ncase;
}Tableau_Entier;

typedef struct {
    char tab[20][60];
    int n;
}menu;

int longeur(menu m)
{
    if (m.n==0)
        return -1;
    int longeur = strlen(m.tab[0]);
    for (int i = 1; i < m.n; ++i) {
        if (strlen(m.tab[i])> longeur)
            longeur = strlen((m.tab[i]));
    }
    return longeur;
}

void affichage_menu(menu m)
{
    int max = longeur(m);
    printf("---------MENU------------\n");
    int nbr_espace = 0;
    for (int i = 0; i < m.n; ++i) {
        printf("%d. ",i+1);
        nbr_espace = ((max - strlen(m.tab[i]))/2)-1;
        for (int j = 0; j < nbr_espace; ++j) {
            printf(" ");
        }
        printf("%s\n",m.tab[i]);
    }
}
int ask_user_menu(menu m)
{
    char answer[longeur(m)];
    do {
        system("clear");
        affichage_menu(m);
        printf("\nVeuillez choisir votre menu (q ou Q pour quitter)\n");
        scanf("%s",answer);
        scanf("%[^\n]%*c",answer);// %[^\n] pour forcer la fonciton scanf à scaner touts les caractères sans scaner la \n
        //%*c ignorer le dernier caractère dans le résultat. On veut que le buffer d'entré soit vide mais on ne veut pas que le \n soit dans notre résultat. le * va permettre de ne pas laisserr le dernier caractère en l'occurence le \n dans le buffer d'entrée.
        for (int i = 0; i < m.n; ++i) {
            if (strcmp(answer,m.tab[i])==0)
                return i+1;
        }
    } while (strcmp(answer,"q")!=0 && strcmp(answer,"Q")!=0);
    return 0;
}

typedef struct {
    float d;
    float D;
    float L;
    char *contenance;
}tonneau;

float volume_tonneau(tonneau t)
{
    tonneau *ptr_ton = &t;
    //return pow((t.d/2)+2/3*(t.D/2 - t.d/2),2);
    //pour acceder par un pointeur on peut aussi écrire (*ptr_ton).d
    return pow((ptr_ton->d/2)+2/3*(ptr_ton->D/2 - ptr_ton->d/2),2);
}

/*
 tonneau t;
    tonneau *ptr;
    ptr = &t;
    t.d = 11;
    t.D = 13;
    t.L = 20;
    t.contenance = "vin";

    printf("Il y'a %.2f L de %s dans ce tonneau.\n", volume_tonneau(t), t.contenance);
 */

